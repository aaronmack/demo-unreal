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
 * This sample program traverses the whole heirarchy printing out
 * information about the nodes in the file.
 */


#include <UT/UT_NTStreamUtil.h>
#include <UT/UT_String.h>
#include <CMD/CMD_Args.h>
#include <PI/PI_ResourceManager.h>
#include <MOT/MOT_Director.h>
#include <iostream>

static bool verbose = false;

using std::cout;

static void
printIndent(int indent)
{
    while (indent > 0)
    {
	cout << " ";
	indent--;
    }
}

static void
printNode(OP_Node *node, OP_Node *input, int indent)
{
    printIndent(indent);
    cout << node->getName();
    if (input)
	cout << " is wired to " << input->getName();
    cout << "\n";

    // Now, we print out the nodes which have this node as an input
    for (auto &&out : OP_OutputIterator(*node))
	printNode(out, node, indent+1);
}

static void
printNetwork(OP_Network *net, int indent = 0)
{
    int		 i, nkids;
    OP_Node	*node;
    OP_Network	*kidnet;

    // Here, we find all the nodes which don't have inputs.  These are the
    // "root" nodes.  We follow the outputs down for each node printing out the
    // information.
    nkids = net->getNchildren();
    for (i = 0; i < nkids; i++)
    {
	node = net->getChild(i);

	// If we have no inputs, then print us out, otherwise, the node
	// printing will print us out...
	if (node->nInputs() == 0)
	    printNode(node, 0, indent);
    }

    // Now, if any of the nodes are networks themselves, let's print out them
    // and their contents.

    for (i = 0; i < nkids; i++)
    {
	node = net->getChild(i);
	if (node->isNetwork())
	{
	    // Here, this is a safe cast.
	    kidnet = (OP_Network *)node;
	    if (kidnet->getNchildren())
	    {
		printIndent(indent+1);
		cout << kidnet->getName() << " contains:\n";
		printNetwork(kidnet, indent+2);
	    }
	}
    }
}

int
main(int argc, char *argv[])
{
    MOT_Director *boss = new MOT_Director("traverse");
    OPsetDirector(boss);
    PIcreateResourceManager();

    CMD_Args args;
    args.initialize(argc, argv);
    args.stripOptions("v");
    if (args.found('v'))
        verbose = true;

    // Load the arguments
    for (int i = 1; i < args.argc(); i++)
    {
        const char *filename = args(i);
        UT_String warnings_or_errors;
        // Merge in all the arguments
        if (verbose)
            cout << "Loading: " << filename << "\n";
        bool success = boss->loadOrMergeHipFile(
            filename,
            true,   // merge into existing scene (false means to clear existing scene)
            nullptr,// pattern for which nodes to load
            false,  // overwrite existing nodes
            warnings_or_errors);
        if (!success)
        {
            std::cerr << "Error loading network for " << filename << ":\n";
            std::cerr << warnings_or_errors.c_str() << "\n";
        }
        else if (verbose && warnings_or_errors.isstring())
        {
            std::cerr << "Warnings loading network for " << filename << ":\n";
            std::cerr << warnings_or_errors.c_str() << "\n";
        }
    }

    if (verbose)
	cout << "Traversing the HIP file(s)\n";

    printNetwork(boss);

    return 0;
}
