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
#include <CMD/CMD_Args.h>
#include <IMG/IMG_DeepShadow.h>
#include <IMG3D/IMG3D_Manager.h>
#include <UT/UT_Vector3.h>
#include <UT/UT_DMatrix4.h>
#include <UT/UT_DMatrix3.h>
#include <UT/UT_Assert.h>
#include <UT/UT_WorkArgs.h>
#include <UT/UT_String.h>

using std::cerr;

static void
usage(const char *program)
{
    cerr << "Usage: " << program << "\n\t-t <light transform> \n";
    cerr << "\t-x <x resolution> -y <y resolution>\n";
    cerr << "\t-l <projection type> <focal length> <aperture> <ortho width>\n";
    cerr << "\t-i <I3D file>\n";
    cerr << "\t-f <DSM file>\n";
    cerr << "\t[-s <Step size>]\n";
    cerr << "\t[-d <Max Depth>]\n";
}

static void
fillPixel(IMG_DeepPixelWriter &writer, IMG3D_Manager &i3d, 
	  const UT_Vector3 &orig, const UT_Vector3 &dir,
	  float dist, float step, float tau)
{
    float	pixel[3];
    float	den, pden, zval, zinc;
    int		i, nsteps;
    UT_Vector3	p0, p1;
    UT_Vector3	i1;

    // Find the interval we need to sample
    p0 = orig;
    p1 = orig + dist*dir;
    i3d.integrate(p0, p1, pixel, 0.001F, 1, 0);
    i3d.integrate(p1, p0, pixel, 0.001F, 1, 0);

    // Make sure there are cells to integrate
    if (dot(p1-p0, dir) <= 0)
	return;

    nsteps = (int)((p1-p0).length() / step);
#if 0
    fprintf(stderr, "Integrating %d steps (from %f %f %f to %f %f %f)\n",
	    nsteps, p0[0], p0[1], p0[2], p1[0], p1[1], p1[2]);
#endif

    pden = 0;
    zinc = step*dir.length();
    zval = (p0-orig).length();
    for (i = 0; i < nsteps; i++)
    {
	den = 0;
	i1 = p0 + (float)i*step*dir;
	i3d.sample(i1, &den);
	den *= tau*step;
	if (den > 0)
	{
	    pden = den + (1-den)*pden;
	    pixel[0] = pixel[1] = pixel[2] = pden;
#if 0
	    fprintf(stderr, "Storing pixel data: %f %f %f %f\n",
		    pixel[0], pixel[1], pixel[2], pixel[3]);
#endif
	    writer.writeOrdered(zval, pixel, 3, 0, -1, 0);
	}
	zval += zinc;
    }
}

int
main(int argc, char *argv[])
{
    CMD_Args		 args;
    IMG_DeepShadow	 dsm;
    IMG3D_Manager	 i3d;
    UT_DMatrix4		 trans;
    UT_Vector3		 orig;
    UT_Vector3		 dir;
    float		 dist, step, zoom, xwin, ywin, tau, orthow;
    const char		*fname;
    const char		*iname;
    int			 xres, yres;
    int			 i, j;
    bool		 ortho = true;

    args.initialize(argc, argv);
    args.stripOptions("t:f:x:y:l::::i:s:d:");

    dist = 1000;
    tau = 1;
    step = 0.05;
    orthow = 1;
    fname = iname = 0;
    if (args.found('f'))
	fname = args.argp('f');
    if (args.found('i'))
	iname = args.argp('i');
    if (args.found('s'))
	step = args.fargp('s');
    if (args.found('d'))
	dist = args.fargp('d');

    if (args.found('t'))
    {
	UT_String	str = args.argp('t');
	UT_WorkArgs	argv;

	str.tokenize(argv, "[],");
	if (argv.getArgc() != 16)
	{
	    cerr << "Invalid transform parameters "
		"(example: [1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1])\n";
	    return 1;
	}

	for (i = 0; i < 4; i++)
	    for (j = 0; j < 4; j++)
		trans(i, j) = atof(argv[i*4+j]);
    }
    else
    {
	cerr << "Must specify global transformation (-t)\n";
	usage(argv[0]);
	return 1;
    }

    if (args.found('l') && args.found('x') && args.found('y'))
    {
	xres = args.iargp('x', 0);
	yres = args.iargp('y', 0);
	ortho = args.iargp('l', 0) == 1;
	if (ortho)
	{
	    orthow = args.fargp('l', 3);
	    zoom = 1;
	}
	else
	{
	    if (args.fargp('l', 2) == 0)
	    {
		cerr << "Must specify non-zero light aperture\n";
		usage(argv[0]);
		return 1;
	    }
	    zoom = args.fargp('l', 1) / args.fargp('l', 2);
	}
    }
    else
    {
	cerr << "Must specify light parameters\n";
	usage(argv[0]);
	return 1;
    }

    if (!fname || !iname)
    {
	cerr << "Must specify DSM and I3D file names\n";
	usage(argv[0]);
	return 1;
    }

    if (!i3d.openTexture(iname))
    {
	cerr << "Could not open I3D texture " << iname << "\n";
	usage(argv[0]);
	return 1;
    }
    if (!i3d.openChannel("density"))
    {
	cerr << "Could not open density channel of " << iname << "\n";
	usage(argv[0]);
	return 1;
    }

    std::cout << "Creating DSM " << fname << " from i3d " << iname << "\n";

    xwin = orthow * 0.5F / zoom;
    ywin = xwin * (yres / (float)xres);

    dsm.setOption("compression", "5");
    dsm.setOption("zbias", "0.05");
    dsm.setOption("depth_planes", "zfront,zback");
    dsm.create(fname, xres, yres, 1, 1);

    IMG_DeepPixelWriter writer(dsm);
    if (!ortho)
    {
	trans.getTranslates(orig);
	for (j = 0; j < yres; j++)
	{
	    for (i = 0; i < xres; i++)
	    {
		dir = UT_Vector3(xwin*2*(i+0.5F)/(float)xres-xwin,
				 ywin*2*(j+0.5F)/(float)yres-ywin, -1);
		dir *= UT_DMatrix3(trans);

		writer.open(i, j);
		fillPixel(writer, i3d, orig, dir, dist, step, tau);
		writer.close();
	    }
	}
    }
    else
    {
	dir = UT_Vector3(0, 0, -1);
	dir.rowVecMult3(trans);
	for (j = 0; j < yres; j++)
	{
	    for (i = 0; i < xres; i++)
	    {
		orig = UT_Vector3(xwin*2*(i+0.5F)/(float)xres-xwin,
				  ywin*2*(j+0.5F)/(float)yres-ywin, 0);
		orig *= trans;

		writer.open(i, j);
		fillPixel(writer, i3d, orig, dir, dist, step, tau);
		writer.close();
	    }
	}
    }
    dsm.close();
    
    return 0;
}
