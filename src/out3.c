/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out3.c
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
 * 2016-05-15   wm              Initial version
 *
 ******************************************************************************/

#include "span_indexed_score.h"
#include "span_var.h"
#include "span_deque.h"
#include "min_max.h"
#include "span_tuple_ix.h"
#include "deque.h"
#include "timestamp.h"
#include "var_type.h"
#include "cstring_score.h"
#include "score_as_cstring.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void build_var_to_tupix(
    SPAN(deque_t) var_to_tupix,
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    const size_t tup_dim
    )
{
    const uint64_t time0 = timestamp();

    size_t six = 0;

    for (six = 0; six < indexed_scores.sz; ++six)
    {
        const size_t tix = indexed_scores.ptr[six].first;

        size_t vix = 0;
        for (vix = 0; vix < tup_dim; ++vix)
        {
            const var_t v = tuples.ptr[vix + tix * tup_dim];

            /* mapping is from value to index in sorted scores !!! */
            deque_push_back(&var_to_tupix.ptr[v], six);
        }
    }

    fprintf(stderr, "var-to-tuple-ix was built in %zu msec\n", timestamp() - time0);
}


typedef void (*out_scored_tuple_fn)(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p);

/* lame, should go to a header shared with out_scored.c */
extern out_scored_tuple_fn out_scored_tuple_fns[];

void out3(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    SPAN(deque_t) var_to_tupix,
    const size_t tup_dim,
    const size_t k,
    int nthreads)
{
    FILE * ofile = NULL;

    const uint64_t time0 = timestamp();

    const out_scored_tuple_fn out_scored_tuple = out_scored_tuple_fns[tup_dim - 2];

    do
    {
        const char * fname = "out3.txt";
        remove(fname);
        ofile = fopen(fname, "wt");

        if (ofile == NULL)
        {
            fprintf(stderr, "[%s] Could not open file %s for writting\n", __FILE__, fname);
            break;
        }
        setvbuf(ofile, NULL, _IOFBF, 0);

        if (indexed_scores.sz == 0)
        {
            fprintf(stderr, "[out5] there is no data to process\n");
            break;
        }

        var_t var = 0;
        for (var = 0; var < var_to_tupix.sz; ++var)
        {
            if (var_to_tupix.ptr[var].nelem == 0)
            {
                continue;
            }

            const size_t real_k = MIN(k, var_to_tupix.ptr[var].nelem);

            SPAN(tuple_ix_t) tupix = deque_as_span(&var_to_tupix.ptr[var]);

            double sum = 0.;
            size_t spix = 0;

            for (spix = 0; spix < tupix.sz; ++spix)
            {
                const size_t ssix = tupix.ptr[spix];
                sum += indexed_scores.ptr[ssix].second;
            }

            /* variable | average score */
            fprintf(ofile, "%u\t%.10lf\n", var, sum / tupix.sz);

            for (spix = 0; spix < real_k; ++spix)
            {
                const size_t ssix = tupix.ptr[spix];
                const double score = indexed_scores.ptr[ssix].second;
                const size_t tix = indexed_scores.ptr[ssix].first;

                cstring_score_t cscore;
                score_as_cstring(score, &cscore);
                out_scored_tuple(ofile, tuples.ptr, tix, &(cscore[0]));
            }

            for (spix = 0; spix < real_k; ++spix)
            {
                const size_t ssix = tupix.ptr[tupix.sz - 1 - spix];
                const double score = indexed_scores.ptr[ssix].second;
                const size_t tix = indexed_scores.ptr[ssix].first;

                cstring_score_t cscore;
                score_as_cstring(score, &cscore);
                out_scored_tuple(ofile, tuples.ptr, tix, &(cscore[0]));
            }

            if (tupix.ptr)
            {
                free(tupix.ptr);
            }
        }

    } while (0);

    if (ofile != NULL)
    {
        fclose(ofile);
    }

    fprintf(stderr, "[out3] Done, %lu msec\n", timestamp() - time0);
}
