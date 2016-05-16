/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_data_context.c
 *
 * Description:
 *      Read data context from specified binary file
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2016-05-10   wm              Initial version
 *
 ******************************************************************************/

#include "read_data_context.h"
#include "data_context.h"
#include "io.h"

#include <stdio.h>
#include <stddef.h>


/**
 * Read contents of the data context file.
 *
 * On failure the dummy field will be set to BAD_CONTEXT_MARKER.
 */
data_context_t read_data_context(const char * fname)
{
    data_context_t ctx = {BAD_CONTEXT_MARKER};

    FILE * ifile = NULL;

    do
    {
        ifile = fopen(fname, "rb");
        if (ifile == NULL)
        {
            fprintf(stderr, "Error: couldn't open data context file %s.\n", fname);
            break;
        }

        const size_t fsz = fsize(ifile);

        if (fsz == 0)
        {
            fprintf(stderr, "Error: empty data context file %s\n", fname);
            break;
        }

        if (fsz != 28)
        {
            fprintf(stderr, "Error: bad data context file size: %zu\n", fsz);
            break;
        }

        const size_t nread = fread(&ctx, 1, sizeof (ctx), ifile);
        if (nread != 28)
        {
            fprintf(stderr, "Error: couldn't read from data context file, got %zu bytes\n", nread);
            ctx.dummy = BAD_CONTEXT_MARKER;
            break;
        }

    } while (0);


    if (ifile != NULL)
    {
        fclose(ifile);
        ifile = NULL;
    }

    return ctx;

}
