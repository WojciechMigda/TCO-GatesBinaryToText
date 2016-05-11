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

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <pthread.h>


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

                size_t bix = 0;
                for (bix = 1; bix < nthreads; ++bix)
                {
                    const int rc = pthread_create(&thread[bix - 1], &attr, sorting_thread, (void *)&batches[bix - 1]);
                    if (rc)
                    {
                        fprintf(stderr, "[%s] pthread_create error: %d, ignoring\n", __FILE__, rc);
                    }
                    batches[bix] = read_scored_index_batch(fname, tupdim, positions[bix], positions[bix + 1]);
                }
            }

            pthread_attr_destroy(&attr);

            /* sort last batch */
            batches[nthreads - 1] = sort_indexed_scores(batches[nthreads - 1]);

            /* join threads */
            {
                size_t bix = 0;
                for (bix = 0; bix < (nthreads - 1); ++bix)
                {
                    void * status = NULL;
                    const int rc = pthread_join(thread[bix], &status);
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
