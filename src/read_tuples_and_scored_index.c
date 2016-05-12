/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_tuples_and_scored_index.c
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
 * 2016-05-12   wm              Initial version
 *
 ******************************************************************************/

#include "indexed_score.h"
#include "span.h"
#include "io.h"
#include "scored_tuple_types.h"
#include "span_indexed_score.h"
#include "var_type.h"
#include "read_tuples_and_scored_index.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


#define TUPLE_DIM 2
#include "read_tuples_and_scored_index_sub_gen.h"

#define TUPLE_DIM 3
#include "read_tuples_and_scored_index_sub_gen.h"

#define TUPLE_DIM 4
#include "read_tuples_and_scored_index_sub_gen.h"

#define TUPLE_DIM 5
#include "read_tuples_and_scored_index_sub_gen.h"

#define TUPLE_DIM 6
#include "read_tuples_and_scored_index_sub_gen.h"

#define TUPLE_DIM 7
#include "read_tuples_and_scored_index_sub_gen.h"

#define TUPLE_DIM 8
#include "read_tuples_and_scored_index_sub_gen.h"


typedef void (*read_tuples_and_scored_index_sub_t)(
    indexed_score_t * __restrict__ score_p,
    var_t * __restrict__ var_p,
    FILE * __restrict__ ifile,
    const size_t begin,
    const size_t end);

const read_tuples_and_scored_index_sub_t read_tuples_and_scored_index_sub[] =
{
    read_tuples_and_scored_index_sub_d2,
    read_tuples_and_scored_index_sub_d3,
    read_tuples_and_scored_index_sub_d4,
    read_tuples_and_scored_index_sub_d5,
    read_tuples_and_scored_index_sub_d6,
    read_tuples_and_scored_index_sub_d7,
    read_tuples_and_scored_index_sub_d8,
};


SPAN_T(indexed_score_t)
read_tuples_and_scored_index_batch(
    const char * fname,
    const size_t tup_dim,
    const size_t begin,
    const size_t end,
    SPAN(var_t) vspan
    )
{
    FILE * ifile = NULL;
    void * scores_p = NULL;

    SPAN(indexed_score_t) xspan = NULL_SPAN(indexed_score_t);

    const size_t tupsz = sizeof (var_t) * tup_dim + sizeof (double);

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

        scores_p = malloc((end - begin) * sizeof (indexed_score_t));
        if (scores_p == NULL)
        {
            fprintf(stderr, "[%s] Coudn't allocate memory for batch of scored indices, needed %zu bytes\n", __FILE__,
                (end - begin) * sizeof (indexed_score_t));
            break;
        }


        read_tuples_and_scored_index_sub[tup_dim - 2](scores_p, vspan.ptr, ifile, begin, end);


        xspan = MAKE_SPAN(indexed_score_t, scores_p, end - begin);
        scores_p = NULL;

    } while (0);

    if (ifile != NULL)
    {
        fclose(ifile);
        ifile = NULL;
    }

    if (scores_p != NULL)
    {
        free(scores_p);
        scores_p = NULL;
    }

    return xspan;
}
