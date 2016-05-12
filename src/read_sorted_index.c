/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_sorted_index.c
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
#include "pair.h"
#include "read_scored_index.h"
#include "sort_indexed_scores.h"
#include "span_indexed_score.h"
#include "span_var.h"
#include "read_tuples_and_scored_index.h"


#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <pthread.h>


#include <string.h>

typedef SPAN(indexed_score_t) span_indexed_score_t;
DEFINE_SPAN(span_indexed_score_t);

SPAN(indexed_score_t)
naive_merge_sorted_scores_batches(SPAN(span_indexed_score_t) batches)
{
    size_t total_sz = 0;
    size_t ix = 0;
    for (ix = 0; ix < batches.sz; ++ix)
    {
        total_sz += batches.ptr[ix].sz;
    }

    const size_t item_sz = sizeof (batches.ptr[0].ptr[0]);

    indexed_score_t * combined_p = malloc(total_sz * item_sz);

    size_t nwritten = 0;
    for (ix = 0; ix < batches.sz; ++ix)
    {
        memcpy(&combined_p[nwritten], batches.ptr[ix].ptr, batches.ptr[ix].sz * item_sz);
        free(batches.ptr[ix].ptr);
        batches.ptr[ix].ptr = NULL;
        nwritten += batches.ptr[ix].sz;
    }

    qsort(combined_p, total_sz, sizeof (batches.ptr[0].ptr[0]), cmp_indexed_score_by_score_asc);
//    void _quicksort (void *const pbase, size_t total_elems, size_t size, int (*cmp)(const void *, const void *), void *arg);
//    _quicksort(combined_p, total_sz, sizeof (batches.ptr[0].ptr[0]), cmp_indexed_score_by_score_asc, NULL);

    return MAKE_SPAN(indexed_score_t, combined_p, total_sz);
}


static
void * sorting_thread(void * p)
{
    SPAN(indexed_score_t) * span_p = (SPAN(indexed_score_t) *)p;

    sort_indexed_scores(*span_p);

    fprintf(stderr, "Sorted scores: %p [%zu]\n", (void *)(span_p->ptr), span_p->sz);

    pthread_exit(NULL);
    return NULL;
}


SPAN(indexed_score_t) read_sorted_index(
    const char * fname,
    size_t ntuples,
    size_t tupdim,
    int nthreads)
{
    SPAN(indexed_score_t) batches[nthreads];
    SPAN(indexed_score_t) retspan = NULL_SPAN(indexed_score_t);

    do
    {
        /* construct tuples ranges */
        size_t positions[nthreads + 1];
        positions[0] = 0;

        {
            size_t ix = 0;
            const float delta = (float)ntuples / nthreads;
            for (ix = 1; ix <= nthreads; ++ix)
            {
                positions[ix] = round(delta * ix);
            }
        }

        /* read first batch */
        batches[0] = read_scored_index_batch(fname, tupdim, positions[0], positions[1]);

        if (nthreads > 1)
        {
            pthread_t thread[nthreads - 1];
            pthread_attr_t attr;
            /* loop: dispatch sort, read next batch */
            {
                pthread_attr_init(&attr);
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

                size_t tid = 0;
                for (tid = 1; tid < nthreads; ++tid)
                {
                    const int rc = pthread_create(&thread[tid - 1], &attr, sorting_thread, (void *)&batches[tid - 1]);
                    if (rc)
                    {
                        fprintf(stderr, "[%s] pthread_create error: %d, ignoring\n", __FILE__, rc);
                    }
                    batches[tid] = read_scored_index_batch(fname, tupdim, positions[tid], positions[tid + 1]);
                }
            }

            pthread_attr_destroy(&attr);

            /* sort last batch */
            batches[nthreads - 1] = sort_indexed_scores(batches[nthreads - 1]);

            /* join threads */
            {
                size_t tid = 0;
                for (tid = 0; tid < (nthreads - 1); ++tid)
                {
                    void * status = NULL;
                    const int rc = pthread_join(thread[tid], &status);
                    if (rc)
                    {
                        fprintf(stderr, "[%s] pthread_join error: %d, ignoring\n", __FILE__, rc);
                    }
                }
            }
        }
        else
        {
            batches[0] = sort_indexed_scores(batches[0]);
        }

        /// TEST
//        {
//            size_t ix = 0;
//            for (ix = 0; ix < nthreads; ++ix)
//            {
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[0].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[1].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[2].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[batches[ix].sz - 3].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[batches[ix].sz - 2].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[batches[ix].sz - 1].second);
//                fprintf(stderr, "\n");
//            }
//        }
        if (nthreads > 1)
        {
            // http://www.geeksforgeeks.org/merge-k-sorted-arrays/
            // http://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/

#warning TODO: naive_merge_sorted_scores_batches
            retspan = naive_merge_sorted_scores_batches(MAKE_SPAN(span_indexed_score_t, batches, nthreads));
        }
        else
        {
            retspan = batches[0];
            batches[0].ptr = NULL;
        }

//        fprintf(stderr, "batch     %lf\n", retspan.ptr[0].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[1].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[2].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[retspan.sz - 3].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[retspan.sz - 2].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[retspan.sz - 1].second);

    } while (0);

    {
        size_t ix = 0;

        for (ix = 0; ix < nthreads; ++ix)
        {
            if (batches[ix].ptr != NULL)
            {
                free(batches[ix].ptr);
            }
        }
    }

    return retspan;
}

DEFINE_PAIR(SPAN_T(var_t), SPAN_T(indexed_score_t));

PAIR(SPAN_T(var_t), SPAN_T(indexed_score_t))
read_tuples_and_sorted_index(
    const char * fname,
    size_t ntuples,
    size_t tup_dim,
    int nthreads)
{
    SPAN(indexed_score_t) batches[nthreads];
    SPAN(indexed_score_t) xspan = NULL_SPAN(indexed_score_t);
    SPAN(var_t) vspan = NULL_SPAN(var_t);

    void * vars_p = NULL;

    do
    {
        /* allocate space for tuples */
        vars_p = malloc(tup_dim * sizeof (var_t) * ntuples);
        if (vars_p == NULL)
        {
            fprintf(stderr, "[%s] Failed to allocate memory for tuples, needed %zu bytes\n",
                __FILE__, tup_dim * sizeof (var_t) * ntuples);
            break;
        }

        /* construct tuples ranges */
        size_t positions[nthreads + 1];
        positions[0] = 0;

        {
            size_t ix = 0;
            const float delta = (float)ntuples / nthreads;
            for (ix = 1; ix <= nthreads; ++ix)
            {
                positions[ix] = round(delta * ix);
            }
        }

        /* read first batch */
        batches[0] = read_tuples_and_scored_index_batch(fname, tup_dim, positions[0], positions[1],
            MAKE_SPAN(var_t, (var_t *)vars_p + positions[0] * tup_dim, (positions[1] - positions[0]) * tup_dim));

        if (nthreads > 1)
        {
            pthread_t thread[nthreads - 1];
            pthread_attr_t attr;
            /* loop: dispatch sort, read next batch */
            {
                pthread_attr_init(&attr);
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

                size_t tid = 0;
                for (tid = 1; tid < nthreads; ++tid)
                {
                    const int rc = pthread_create(&thread[tid - 1], &attr, sorting_thread, (void *)&batches[tid - 1]);
                    if (rc)
                    {
                        fprintf(stderr, "[%s] pthread_create error: %d, ignoring\n", __FILE__, rc);
                    }
                    batches[tid] = read_tuples_and_scored_index_batch(fname, tup_dim, positions[tid], positions[tid + 1],
                        MAKE_SPAN(var_t, (var_t *)vars_p + positions[tid] * tup_dim, (positions[tid + 1] - positions[tid]) * tup_dim));
                }
            }

            pthread_attr_destroy(&attr);

            /* sort last batch */
            batches[nthreads - 1] = sort_indexed_scores(batches[nthreads - 1]);

            /* join threads */
            {
                size_t tid = 0;
                for (tid = 0; tid < (nthreads - 1); ++tid)
                {
                    void * status = NULL;
                    const int rc = pthread_join(thread[tid], &status);
                    if (rc)
                    {
                        fprintf(stderr, "[%s] pthread_join error: %d, ignoring\n", __FILE__, rc);
                    }
                }
            }
        }
        else
        {
            batches[0] = sort_indexed_scores(batches[0]);
        }

        /// TEST
//        {
//            size_t ix = 0;
//            for (ix = 0; ix < nthreads; ++ix)
//            {
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[0].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[1].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[2].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[batches[ix].sz - 3].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[batches[ix].sz - 2].second);
//                fprintf(stderr, "batch %zu    %lf\n", ix, batches[ix].ptr[batches[ix].sz - 1].second);
//                fprintf(stderr, "\n");
//            }
//        }
        if (nthreads > 1)
        {
            // http://www.geeksforgeeks.org/merge-k-sorted-arrays/
            // http://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/

#warning TODO: naive_merge_sorted_scores_batches
            /* it frees pointers in batches */
            xspan = naive_merge_sorted_scores_batches(MAKE_SPAN(span_indexed_score_t, batches, nthreads));
        }
        else
        {
            xspan = batches[0];
            batches[0].ptr = NULL;
        }

//        fprintf(stderr, "batch     %lf\n", retspan.ptr[0].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[1].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[2].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[retspan.sz - 3].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[retspan.sz - 2].second);
//        fprintf(stderr, "batch     %lf\n", retspan.ptr[retspan.sz - 1].second);

        vspan = MAKE_SPAN(var_t, vars_p, ntuples * tup_dim);
        vars_p = NULL;

    } while (0);

    if (vars_p != NULL)
    {
        free(vars_p);
        vars_p = NULL;
    }

    {
        size_t ix = 0;

        for (ix = 0; ix < nthreads; ++ix)
        {
            if (batches[ix].ptr != NULL)
            {
                free(batches[ix].ptr);
            }
        }
    }

    return MAKE_PAIR(SPAN_T(var_t), SPAN_T(indexed_score_t), vspan, xspan);
}
