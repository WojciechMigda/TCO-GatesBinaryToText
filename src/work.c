/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: work.c
 *
 * Description:
 *      description
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2016-05-07   wm              Initial version
 *
 ******************************************************************************/

#include "read_scored_tuples.h"
#include "program_options.h"
#include "data_context.h"
#include "owner.h"
#include "io.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


#define USE_MMAP 1


int check_file_descriptors(FILE * f_ctx, FILE * f_data)
{
    const size_t f_ctx_sz = fsize(f_ctx);

    if (f_ctx_sz == 0)
    {
        fprintf(stderr, "Error: empty header file\n");
        return -1;
    }
    if (f_ctx_sz != 28)
    {
        fprintf(stderr, "Error: bad header file size: %zu\n", f_ctx_sz);
        return -1;
    }

    if (fsize(f_data) == 0)
    {
        fprintf(stderr, "Error: empty binary file\n");
        return -1;
    }

    return 0;
}


data_context_t read_data_context(FILE * f_ctx)
{
    data_context_t ctx;

    const size_t nread = fread(&ctx, 1, sizeof (ctx), f_ctx);
    if (nread != 28)
    {
        fprintf(stderr, "Error: couldn't read context from file, got %zu bytes\n", nread);
        ctx.dummy = 1;
    }

    return ctx;
}



int work(const struct program_options_s * program_options_p)
{
    FILE * f_ctx = fopen(program_options_p->in_file1, "rb");
    if (!f_ctx)
    {
        fprintf(stderr, "Error: couldn't open header file \"%s\".\n", program_options_p->in_file1);
        return -1;
    }

    FILE * f_data = fopen(program_options_p->in_file2, "rb");
    if (!f_data)
    {
        fprintf(stderr, "Error: couldn't open binary data file \"%s\".\n", program_options_p->in_file2);
        return -1;
    }

    if (check_file_descriptors(f_ctx, f_data) < 0)
    {
        fclose(f_ctx);
        return -1;
    }
    fclose(f_data);


    const data_context_t data_ctx = read_data_context(f_ctx);
    fclose(f_ctx);
    f_ctx = NULL;

    if (data_ctx.dummy != 0)
    {
        return -1;
    }


    fprintf(stderr, "Dimension:\t\t%d\n", data_ctx.d);
    fprintf(stderr, "Number of Variables:\t%d\n", data_ctx.n_vars);
    fprintf(stderr, "Number of Tuples:\t%ld\n", data_ctx.n_tuples);
    fprintf(stderr, "Average:\t\t%.10f\n", data_ctx.average);



    const SPAN(void) scored_tuples = program_options_p->scored_tuples_reader(program_options_p->in_file2);


    // build index


    if (program_options_p->scored_tuples_deleter(scored_tuples) < 0)
    {
        return -1;
    }

    return 0;
}
