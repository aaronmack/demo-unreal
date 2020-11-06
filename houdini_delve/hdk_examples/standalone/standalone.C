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
 * Sample stand alone application.
 */

#include <getopt.h>
#include <stdlib.h>
#include <PI/PI_ResourceManager.h>
#include <MOT/MOT_Director.h>
#include <UT/UT_StringStream.h>
#include <iostream>

#define LINE_SIZE	1024

static void
usage(const char *program)
{
    std::cerr << "Usage: " << program << " [-h]\n";
    std::cerr << "Stand alone houdini application\n";
    exit(1);
}

int
main(int argc, char *argv[])
{
    int			 opt, i;
    MOT_Director	*boss;
    CMD_Manager		*cmd;

    // Do argument parsing
    while ((opt = getopt(argc, argv, "h")) != -1)
    {
	switch (opt)
	{
	    case 'h':
	    default:	usage(argv[0]);
	}
    }

    // Initialize the whole heirarchy of operators
    boss = new MOT_Director("standalone");
    OPsetDirector(boss);
    PIcreateResourceManager();

    cmd = boss->getCommandManager();
    if (argc == optind)
    {
	// If we have no arguments, source 123.cmd
	cmd->sendInput("source -q 123.cmd");
    }
    else
    {
	for (i = optind; i < argc; i++)
	{
	    // Merge in using the mread command.
	    UT_OStringStream ts;
	    ts << "mread -m * " << argv[i] << std::ends;
	    cmd->sendInput(ts.str().buffer());
	}
    }

    // Now, enter the main loop
    do {
	char	line[LINE_SIZE];
	cmd->doPrompt();
	if (!std::cin.getline(line, LINE_SIZE))
	    break;
	cmd->sendInput(line);
    } while (std::cin);

    return 0;
}
