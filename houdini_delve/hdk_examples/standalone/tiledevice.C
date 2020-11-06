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
 * Sample application showing how to use IMG_TileDevice by writing constant
 * image planes (like $HH/public/deepmplay.C). IMG_TileDevice is the
 * interface used by imdisplay and by mantra to write tiles to mplay and
 * the IPR, so it is faster to use IMG_TileDevice directly rather than
 * using imdisplay.
 *
 * To send images to the IPR, you can specify the port number using the -s
 * option. This can be retrieved in soho by evaluating the
 * vm_image_mplay_socketport property.
 */


#include <UT/UT_Args.h>
#include <UT/UT_WorkBuffer.h>
#include <IMG/IMG_TileDevice.h>
#include <IMG/IMG_TileOptions.h>
#include <TIL/TIL_TileMPlay.h>

#define XRES	320	// Image X resolution
#define YRES	240	// Image Y resolution
#define TXRES	16	// Tile X resolution
#define TYRES	16	// Tile Y resolution

struct PlaneDef {
    const char		*myName;
    IMG_DataType	 myFormat;
    IMG_ColorModel	 myColorModel;
};

PlaneDef thePlanes[] = {
    { "C",	IMG_UCHAR, IMG_RGBA },	// C plane is unsigned char, RGBA
    { "s",	IMG_FLOAT, IMG_1CHAN },	// s plane is float, single channel
    { "Normal",	IMG_FLOAT, IMG_RGB },	// N plane is float, RGB data
};

#define NPLANES (sizeof(thePlanes)/sizeof(PlaneDef))

static void *
buildTiles()
{
    int		pixels = TXRES * TYRES;
    size_t	bytes = 0;
    for (int i = 0; i < NPLANES; i++)
    {
	int	words = pixels * IMGvectorSize(thePlanes[i].myColorModel);
	bytes += words * IMGbyteSize(thePlanes[i].myFormat);
    }

    void	*tdata = ::malloc(bytes);
    char	*ptr = (char *)tdata;
    for (int i = 0; i < NPLANES; i++)
    {
	unsigned short	*sdata;
	unsigned char	*cdata;
	unsigned int	*idata;
	float		*fdata;

	int	words = pixels * IMGvectorSize(thePlanes[i].myColorModel);

	cdata = (unsigned char *)ptr;
	sdata = (unsigned short *)ptr; 
	idata = (unsigned int *)ptr; 
	fdata = (float *)ptr;

	// Just fill in with some constant values.
	for (int c = 0; c < words; c++)
	{
	    switch (thePlanes[i].myFormat)
	    {
		case IMG_UCHAR:		*cdata++ = 0x85; break;
		case IMG_USHORT:	*sdata++ = 0x8512; break;
		case IMG_UINT:		*idata++ = 0x84123456; break;
		default:		*fdata++ = 0.763;
	    }
	}

	ptr += words*IMGbyteSize(thePlanes[i].myFormat);
    }

    return tdata;
}

static void
splitHostPort(UT_String &host, UT_String &port, const char *hostname)
{
    const char	*colon = strchr(hostname, ':');
    if (colon)
    {
	int	len = colon - hostname;
	host.harden(colon, len);
	colon++;	// Move past the colon
    }
    else
    {
	colon = hostname;
    }
    port.harden(colon);
}

static void
sendPlaneDefinitions(IMG_TileDevice *dev,
		     const UT_String &host,
		     const UT_String &port)
{
    IMG_TileOptionList	flist;

    for (int i = 0; i < NPLANES; i++)
    {
	IMG_TileOptions	*finfo = new IMG_TileOptions();

	finfo->setPlaneInfo("ip", thePlanes[i].myName,
		0, thePlanes[i].myFormat, thePlanes[i].myColorModel);

	// These format options allow sending tiles to an existing tile
	// device (such as the IPR) rather than opening a new one. They
	// only need to be set for plane 0 but it's harmless to send them
	// for all planes.

	if (host) finfo->setFormatOption("sockethost", host);
	if (port) finfo->setFormatOption("socketport", port);

	flist.append(finfo);
    }

    if (!dev->openMulti(flist, XRES, YRES, TXRES, TYRES, 1.0))
    {
	::fprintf(stderr, "Error opening tile device\n");
	::exit(1);
    }
}

static void
writeTile(IMG_TileDevice *dev, void *tdata, int tx0, int tx1, int ty0, int ty1)
{
    if (!dev->writeTile(tdata, tx0, tx1, ty0, ty1))
    {
	::fprintf(stderr, "Error writing data: %d %d %d %d\n",
			tx0, tx1, ty0, ty1);
	::exit(1);
    }
    dev->flush();
}

int
main(int argc, char *argv[])
{
    UT_Args	args;
    UT_String	host, port;

#ifdef _WIN32
    struct local {
	static IMG_TileDevice *
	creator(int middle)
	{
	    return new TIL_TileMPlay(middle, 0);
	}
    };
    IMG_TileDevice::setMPlayDevCreator(local::creator);
#endif

    args.initialize(argc, argv);
    args.stripOptions("s:");

    if (args.found('s'))
	splitHostPort(host, port, args.argp('s'));

    IMG_TileDevice	*dev = IMG_TileDevice::newDevice("ip");

    sendPlaneDefinitions(dev, host, port);

    void *tdata = buildTiles();
    for (int ty = 0; ty < YRES; ty += TYRES)
	for (int tx = 0; tx < XRES; tx += TXRES)
	    ::writeTile(dev, tdata,
		    tx, SYSmin(tx+TXRES, XRES)-1,
		    ty, SYSmin(ty+TYRES, YRES)-1);

    free(tdata);
}
