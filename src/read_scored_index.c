/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_scored_index.c
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
 * 2016-05-10   wm              Initial version
 *
 ******************************************************************************/

#include "indexed_score.h"
#include "span.h"
#include "io.h"
#include "scored_tuple_types.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


DEFINE_SPAN(indexed_score_t);


#define TUPLE_DIM 2
#include "read_scored_index_sub_gen.h"

#define TUPLE_DIM 3
#include "read_scored_index_sub_gen.h"

#define TUPLE_DIM 4
#include "read_scored_index_sub_gen.h"

#define TUPLE_DIM 5
#include "read_scored_index_sub_gen.h"

#define TUPLE_DIM 6
#include "read_scored_index_sub_gen.h"

#define TUPLE_DIM 7
#include "read_scored_index_sub_gen.h"

#define TUPLE_DIM 8
#include "read_scored_index_sub_gen.h"


typedef void (*read_scored_index_sub_t)(
    indexed_score_t * dst_p,
    FILE * ifile,
    size_t begin,
    size_t end);

const read_scored_index_sub_t read_scored_index_sub[] =
{
    read_scored_index_sub_d2,
    read_scored_index_sub_d3,
    read_scored_index_sub_d4,
    read_scored_index_sub_d5,
    read_scored_index_sub_d6,
    read_scored_index_sub_d7,
    read_scored_index_sub_d8,
};


SPAN(indexed_score_t) read_scored_index_batch(
    const char * fname,
    const size_t tup_dim,
    const size_t begin,
    const size_t end
    )
{
    enum { CHUNK = 100 };

    FILE * ifile = NULL;
    void * data_p = NULL;

    SPAN(indexed_score_t) span = NULL_SPAN(indexed_score_t);

    const size_t tupsz = sizeof (uint32_t) * tup_dim + sizeof (double);

    do
    {
        ifile = fopen(fname, "rb");

        const size_t fsz = fsize(ifile);

        if (fsz < end * tupsz)
        {
            fprintf(stderr, "[%s] Trying to read beyond the end of file, end: %zu, file size: %zu\n", __FILE__,
                end * tupsz, fsz);
            break;
        }

        data_p = malloc((end - begin) * sizeof (indexed_score_t));
        if (data_p == NULL)
        {
            fprintf(stderr, "[%s] Coudn't allocate memory for batch of scored indices, needed %zu bytes\n", __FILE__,
                (end - begin) * sizeof (indexed_score_t));
            break;
        }


        read_scored_index_sub[tup_dim - 2](data_p, ifile, begin, end);


        span = MAKE_SPAN(indexed_score_t, data_p, end - begin);
        data_p = NULL;

    } while (0);

    if (ifile != NULL)
    {
        fclose(ifile);
        ifile = NULL;
    }

    if (data_p != NULL)
    {
        free(data_p);
        data_p = NULL;
    }

    return span;
}
