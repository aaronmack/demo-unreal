/*
 * Copyright (c) 2020
 *	Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 */


#include <CMD/CMD_Args.h>
#include <UT/UT_Assert.h>
#include <UT/UT_IStream.h>
#include <UT/UT_OFStream.h>
#include <UT/UT_NetMessage.h>

#include <ostream>
#include <iostream>
#include <stdio.h>


static void
usage(const char *program)
{
    std::cerr << "Usage: " << program << " tracker port thisslicenumber numslice\n";
}

#define DATA_LEN	80000
#define PIPE_ATTEMPTS	10


// Transfer data between peers using a UT_NetMessagePipe
//
// Build using:
//	hcustom -s msgpipe.C
//
// Example usage:
//	python simtracker.py 8000 9000
//	msgpipe localhost 8000 0 2
//	msgpipe localhost 8000 1 2
//
int
main(int argc, char *argv[])
{
    CMD_Args		 args;

    args.initialize(argc, argv);

    if (args.argc() != 5)
    {
	usage(argv[0]);
	return 1;
    }

    const char		*tracker = args.argv(1);
    int			port = SYSatoi(args.argv(2));
    int			thisslice = SYSatoi(args.argv(3));
    int			numslice = SYSatoi(args.argv(4));

    std::cerr << "Building connection to tracker " << tracker << ":" << port << std::endl;
    std::cerr << "I am slice " << thisslice << " out of " << numslice << std::endl;

    // Use a net exchange to send some data between the slices.
    {
	std::cerr << "Simple Exchange Test" << std::endl;
	UT_NetExchange		netxchg(tracker, port, thisslice, numslice, "normalexchange");

	for (int peer = 0; peer < numslice; peer++)
	{
	    UT_NetMessage		*msg = new UT_NetMessage();
	    msg->setWriteDataLength(8 + DATA_LEN * sizeof(int32));

	    for (int i = 0; i < DATA_LEN; i++)
	    {
		msg->overwriteInt32(8 + i * sizeof(int32), i + peer);
	    }
	    netxchg.sendData(peer, msg);
	}

	UT_ValArray<UT_NetMessage *>	completed;
	if (!netxchg.receiveDataLoop(completed, numslice))
	{
	    std::cerr << "Failure to do traditional data exchange, got " << completed.entries() << std::endl;
	    return -1;
	}

	// Now verify our messages are legit.  They should all be encoded
	// with our peer infor.
	for (int i = 0; i < completed.entries(); i++)
	{
	    UT_NetMessage		*msg = completed(i);

	    for (int i = 0; i < DATA_LEN; i++)
	    {
		int32		val;
		int32		goalval;
		goalval = i + thisslice;

		val = msg->extractInt32(8 + i * sizeof(int32));

		if (val != goalval)
		{
		    std::cerr << "Error, got " << val << " at integer index " << i << " rather than expected " << goalval << ", source slice was " << msg->extractInt16(6) << std::endl;
		    return -1;
		}
	    }

	    delete msg;
	}
    }

    // Use a net message pipe to repeatedly pump data along the same
    // socket.
    {
	std::cerr << "Message Pipe Tests" << std::endl;
	UT_NetMessagePipe	pipe(tracker, port, thisslice, numslice, "messagepipe");

	// pipe.setCompressionThreshold(-1);

	if (!pipe.openPipes())
	{
	    std::cerr << "Failed to open message pipes" << std::endl;
	    return -1;
	}

	for (int j = 0; j < PIPE_ATTEMPTS; j++)
	{
	    exint datalen = DATA_LEN;
	    std::cerr << "Starting pass " << j << std::endl;
	    for (int peer = 0; peer < numslice; peer++)
	    {
		UT_NetMessage	*msg = pipe.readPipe(peer);

		msg->resetLength(UT_NetMessage::STATE_READPIPE, datalen * sizeof(int32));

		msg = pipe.writePipe(peer);
		msg->resetLength(UT_NetMessage::STATE_WRITEPIPE, datalen * sizeof(int32));

		for (int i = 0; i < datalen; i++)
		{
		    // NOTE: No header here!
		    msg->overwriteInt32(i * sizeof(int32), i + peer + j);
		}
	    }

	    // Now do the transfer.
	    if (!pipe.transferData())
	    {
		std::cerr << "Failed to push data across pipes!" << std::endl;
		return -1;
	    }

	    // Now see if it came through alright!
	    // Again, all the data sent to ourselves should be our own
	    // peer number.
	    for (int peer = 0; peer < numslice; peer++)
	    {
		UT_NetMessage	*msg = pipe.readPipe(peer);

		for (int i = 0; i < datalen; i++)
		{
		    int32		goalval = i + thisslice + j;
		    int32		val;
		    val = msg->extractInt32(i * sizeof(int32));
		    if (val != goalval)
		    {
			std::cerr << "Error, got " << val << " at integer index " << i << " rather than expected " << goalval << ", source slice was " << peer << " and this was pipe pass " << j << std::endl;
			return -1;
		    }
		}
	    }
	}

	for (int peer = 0; peer < numslice; peer++)
	{
	    UT_NetMessage	*msg = pipe.readPipe(peer);
	    msg->resetLength(UT_NetMessage::STATE_READPIPE, 0);

	    msg = pipe.writePipe(peer);
	    msg->resetLength(UT_NetMessage::STATE_WRITEPIPE, 0);
	}

	if (!pipe.closePipes())
	{
	    std::cerr << "Failed to close message pipes." << std::endl;
	    return -1;
	}

    }

    std::cerr << "All transferred successfully!" << std::endl;

    return 0;
}
