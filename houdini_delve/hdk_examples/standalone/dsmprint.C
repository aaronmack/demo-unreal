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

#include <stdio.h>
#include <iostream>
#include <IMG/IMG_DeepShadow.h>
#include <UT/UT_Exit.h>
#include <UT/UT_Options.h>
#include <UT/UT_WorkBuffer.h>

namespace HDK_Sample {

static void
usage(const char *program)
{
    std::cerr << "Usage: " << program << " dsmfile\n";
    std::cerr << "Prints out information about a deep camera/shadow image\n";
    UT_Exit::exit( UT_Exit::EXIT_GENERIC_ERROR );
}

template <typename FTYPE> static void
printTuple(const FTYPE *pixel, int vsize)
{
    int		i;
    printf("(%g", pixel[0]);
    for (i = 1; i < vsize; i++)
	printf(",%g", pixel[i]);
    printf(")");
}

static void
printPixel(IMG_DeepShadow &fp, int x, int y)
{
    int				 i, d, depth;
    const IMG_DeepShadowChannel	*chp;
    IMG_DeepPixelReader		 pixel(fp);

    // Open the pixel
    if (!pixel.open(x, y))
    {
	printf("\tUnable to open pixel [%d,%d]!\n", x, y);
	return;
    }

    // Get the number of z-records for the pixel
    depth = pixel.getDepth();
    printf("Pixel[%d,%d][%d]\n", x, y, depth);

    // Iterate over all channels in the DCM
    for (i = 0; i < fp.getChannelCount(); i++)
    {
	chp = fp.getChannel(i);
	printf(" %5s = [", chp->getName());
	if (depth)
	{
	    // Print first depth record
	    printTuple<float>(pixel.getData(*chp, 0), chp->getTupleSize());
	    // And the remaining depth records
	    for (d = 1; d < depth; d++)
	    {
		printf(", ");
		printTuple<float>(pixel.getData(*chp, d), chp->getTupleSize());
	    }
	}
	printf("]\n");
    }
}

static void
dumpOptions(IMG_DeepShadow &fp)
{
    UT_SharedPtr<UT_Options>	opt;
    UT_WorkBuffer	 wbuf;
    opt = fp.getTextureOptions();
    if (opt)
    {
	wbuf.strcpy("DSM Options: ");
	opt->appendPyDictionary(wbuf);
	printf("%s\n", wbuf.buffer());
    }
}

}
using namespace HDK_Sample;

int
main(int argc, char *argv[])
{
    IMG_DeepShadow	fp;
    int			xres, yres;

    if (!fp.open(argv[1]))
	usage(argv[0]);

    // Read the texture options in the file
    dumpOptions(fp);

    // Query the resolution
    fp.resolution(xres, yres);
    printf("%s[%d,%d] (%d channels)\n",
		argv[1], xres, yres, fp.getChannelCount());

    // Print the raw pixel data
    printPixel(fp, 0, 0);
    printPixel(fp, xres>>1, 0);
    printPixel(fp, xres-1,  0);
    printPixel(fp, 0, yres>>1);
    printPixel(fp, xres>>1, yres>>1);
    printPixel(fp, xres-1,  yres>>1);
    printPixel(fp, 0, yres-1);
    printPixel(fp, xres>>1, yres-1);
    printPixel(fp, xres-1,  yres-1);

    return 0;
}
