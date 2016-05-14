/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out4.c
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
 * 2016-05-14   wm              Initial version
 *
 ******************************************************************************/

#include "span.h"
#include "indexed_score.h"
#include "span_indexed_score.h"
#include "timestamp.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

void out4(
    SPAN(indexed_score_t) indexed_scores,
    const double bucket_sz,
    int nthreads)
{
    const double max = indexed_scores.ptr[0].second;
    const double min = indexed_scores.ptr[indexed_scores.sz - 1].second;

    FILE * ofile = NULL;
    size_t * counter_p = NULL;

    const uint64_t time0 = timestamp();

    do
    {
        const char * fname = "out4.txt";
        remove(fname);
        ofile = fopen(fname, "wt");

        if (ofile == NULL)
        {
            fprintf(stderr, "[%s] Could not open file %s for writting\n", __FILE__, fname);
            break;
        }
        setvbuf(ofile, NULL, _IOFBF, 0);

        fprintf(ofile, "%.10lf\t%.10lf\n", min, max);

        if (bucket_sz == 0.)
        {
            break;
        }

        const size_t maybe_nbuckets = ceil((max - min) / bucket_sz);
        const size_t nbuckets = (maybe_nbuckets * bucket_sz) == (max - min) ? maybe_nbuckets + 1 : maybe_nbuckets;

        fprintf(stderr, "[out4] nbuckets: %zu , bucket size: %f\n", nbuckets, bucket_sz);
        fprintf(stderr, "[out4] min: %.10lf , max: %.10lf\n", min, max);

        if (nbuckets == 1)
        {
            fprintf(ofile, "%zu\n", indexed_scores.sz);
            break;
        }

        counter_p = calloc(nbuckets, sizeof (*counter_p));
        if (counter_p == NULL)
        {
            fprintf(stderr, "[%s] Could not allocate space for the counter object, needed %zu bytes\n",
                __FILE__, nbuckets * sizeof (*counter_p));
            break;
        }

        size_t ix = 0;
        for (ix = 0; ix < indexed_scores.sz; ++ix)
        {
            const size_t bix = floor((indexed_scores.ptr[ix].second - min) / bucket_sz);
            counter_p[bix]++;
        }

        for (ix = 0; ix < nbuckets; ++ix)
        {
            fprintf(ofile, "%zu\n", counter_p[ix]);
        }

    } while (0);

    if (ofile != NULL)
    {
        fclose(ofile);
    }

    if (counter_p != NULL)
    {
        free(counter_p);
    }

    fprintf(stderr, "[out4] Done, %lu msec\n", timestamp() - time0);
}
