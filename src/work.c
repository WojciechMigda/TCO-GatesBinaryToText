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

#include "read_data_context.h"
#include "read_scored_tuples.h"
#include "program_options.h"
#include "data_context.h"
#include "owner.h"
#include "io.h"
#include "out_sorted.h"
#include "out3.h"
#include "out4.h"
#include "out5.h"

#include "read_sorted_index.h"

#include "span_var.h"
#include "span_indexed_score.h"
DEFINE_PAIR(SPAN_T(var_t), SPAN_T(indexed_score_t));
#include "read_tuples_and_sorted_index.h"

#include "deque.h"
#include "span_deque.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>


int work(const struct program_options_s * program_options_p)
{
    const data_context_t data_ctx = read_data_context(program_options_p->in_file1);

    if (data_ctx.dummy == BAD_CONTEXT_MARKER)
    {
        return -1;
    }


    fprintf(stderr, "Dimension:\t\t%d\n", data_ctx.d);
    fprintf(stderr, "Number of Variables:\t%d\n", data_ctx.n_vars);
    fprintf(stderr, "Number of Tuples:\t%ld\n", data_ctx.n_tuples);
    fprintf(stderr, "Average:\t\t%.10f\n", data_ctx.average);


    double sum_sq = 0.;

    SPAN(deque_t) var_to_tupix = NULL_SPAN(deque_t);
    {
        deque_t * data_p = malloc(sizeof (deque_t) * data_ctx.n_vars);
        if (data_p == NULL)
        {
            fprintf(stderr, "Could not allocate space for var-to-tuple-index mapping, needed %zu bytes\n", sizeof (deque_t) * data_ctx.n_vars);
            return -1;
        }

        size_t ix = 0;
        for (ix = 0; ix < data_ctx.n_vars; ++ix)
        {
            data_p[ix] = new_deque();
        }
        var_to_tupix = MAKE_SPAN(deque_t, data_p, data_ctx.n_vars);
    }


    PAIR(SPAN_T(var_t), SPAN_T(indexed_score_t)) tuples_and_indexed_score =
        read_tuples_and_sorted_index(
            program_options_p->in_file2,
            data_ctx.n_tuples,
            data_ctx.d,
            program_options_p->nthreads,
            data_ctx.average,
            &sum_sq
            //, var_to_tupix
            );

    /* we need this for average scores per variable */
    build_var_to_tupix(
        var_to_tupix,
        tuples_and_indexed_score.second,
        tuples_and_indexed_score.first,
        data_ctx.d);

    out1(
        tuples_and_indexed_score.second,
        tuples_and_indexed_score.first,
        data_ctx.d,
        program_options_p->n,
        program_options_p->nthreads);

    out2(
        tuples_and_indexed_score.second,
        tuples_and_indexed_score.first,
        data_ctx.d,
        program_options_p->n,
        program_options_p->nthreads);

    out3(
        tuples_and_indexed_score.second,
        tuples_and_indexed_score.first,
        var_to_tupix,
        data_ctx.d,
        program_options_p->k,
        program_options_p->nthreads);

    out4(tuples_and_indexed_score.second, program_options_p->b, program_options_p->nthreads);

    if (OPTION_TYPE_IS_SOME(program_options_p->maybe_s))
    {
        out5(
            tuples_and_indexed_score.second,
            tuples_and_indexed_score.first,
            data_ctx.d,
            data_ctx.average,
            sum_sq,
            OPTION_TYPE_VALUE(program_options_p->maybe_s),
            program_options_p->nthreads);
    }

    free(tuples_and_indexed_score.first.ptr);
    free(tuples_and_indexed_score.second.ptr);

    if (var_to_tupix.ptr != NULL)
    {
        size_t ix = 0;
        for (ix = 0; ix < var_to_tupix.sz; ++ix)
        {
//            fprintf(stdout, "var %zu in %zu tuples\n", ix, var_to_tupix.ptr[ix].nelem);
            deque_free(&var_to_tupix.ptr[ix]);
        }
        free(var_to_tupix.ptr);
    }

    return 0;
}
