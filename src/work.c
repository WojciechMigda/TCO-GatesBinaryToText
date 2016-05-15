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
#include <pthread.h>


typedef void * (*thread_fn)(void *);

typedef struct
{
    SPAN(indexed_score_t) indexed_scores;
    SPAN(var_t) tuples;
    size_t tup_dim;
    size_t n_tup;
} thread_out12_ctx_t;


static
void * thread_out1(void * p)
{
    thread_out12_ctx_t * ctx = (thread_out12_ctx_t *)p;

    out1(
        ctx->indexed_scores,
        ctx->tuples,
        ctx->tup_dim,
        ctx->n_tup,
        0);

    pthread_exit(NULL);
    return NULL;
}


static
void * thread_out2(void * p)
{
    thread_out12_ctx_t * ctx = (thread_out12_ctx_t *)p;

    out2(
        ctx->indexed_scores,
        ctx->tuples,
        ctx->tup_dim,
        ctx->n_tup,
        0);

    pthread_exit(NULL);
    return NULL;
}


typedef struct
{
    SPAN(indexed_score_t) indexed_scores;
    SPAN(var_t) tuples;
    SPAN(deque_t) var_to_tupix;
    size_t tup_dim;
    uint32_t k;
} thread_out3_ctx_t;

static
void * thread_out3(void * p)
{
    thread_out3_ctx_t * ctx = (thread_out3_ctx_t *)p;

    build_var_to_tupix(
        ctx->var_to_tupix,
        ctx->indexed_scores,
        ctx->tuples,
        ctx->tup_dim);

    out3(
        ctx->indexed_scores,
        ctx->tuples,
        ctx->var_to_tupix,
        ctx->tup_dim,
        ctx->k,
        0);

    pthread_exit(NULL);
    return NULL;
}


typedef struct
{
    SPAN(indexed_score_t) indexed_scores;
    double b;
} thread_out4_ctx_t;

static
void * thread_out4(void * p)
{
    thread_out4_ctx_t * ctx = (thread_out4_ctx_t *)p;

    out4(ctx->indexed_scores, ctx->b, 0);

    pthread_exit(NULL);
    return NULL;
}


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




    pthread_t thread[4];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    thread_out12_ctx_t thread_out12_ctx =
    {
        tuples_and_indexed_score.second,
        tuples_and_indexed_score.first,
        data_ctx.d,
        program_options_p->n
    };

    thread_out3_ctx_t thread_out3_ctx =
    {
        tuples_and_indexed_score.second,
        tuples_and_indexed_score.first,
        var_to_tupix,
        data_ctx.d,
        program_options_p->k
    };

    thread_out4_ctx_t thread_out4_ctx =
    {
        tuples_and_indexed_score.second,
        program_options_p->b
    };

    thread_fn thread_fns[] =
    {
        thread_out1,
        thread_out2,
        thread_out3,
        thread_out4
    };
    void * thread_cxts[] =
    {
        &thread_out12_ctx,
        &thread_out12_ctx,
        &thread_out3_ctx,
        &thread_out4_ctx
    };

    size_t thix = 0;
    for (thix = 0; thix < sizeof (thread_fns) / sizeof (thread_fns[0]); ++thix)
    {
        const int rc = pthread_create(&thread[thix], &attr, thread_fns[thix], thread_cxts[thix]);
        if (rc)
        {
            fprintf(stderr, "[work] pthread_create error: %d, ignoring\n", rc);
        }
    }



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


    for (thix = 0; thix < sizeof (thread_fns) / sizeof (thread_fns[0]); ++thix)
    {
        void * status = NULL;

        const int rc = pthread_join(thread[thix], &status);
        if (rc)
        {
            fprintf(stderr, "[work] pthread_join error: %d, ignoring\n",rc);
        }
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
