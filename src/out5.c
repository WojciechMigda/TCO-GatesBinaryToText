/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out5.c
 *
 * Description:
 *      Compute and output out5.txt file
 *
 *      Algorithm is almost an exact copy of the provided template, except
 *      that it works on data already in memory and that the standard deviation
 *      is passed to it instead of being calculated in place.
 *      The reason for not calculating std dev here is that here out tuple
 *      scores are already sorted, and this the numerical instability at the
 *      10-digit printf format is sufficient to cause rounding errors.
 *      Value of summed squared deviations passed to this function is calculated
 *      on unsorted data and leads to results exactly the same as in the
 *      reference files.
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
#include "var_type.h"
#include "span_var.h"
#include "timestamp.h"
#include "cstring_score.h"
#include "score_as_cstring.h"
#include "cstring_pdouble.h"
#include "pdouble_as_cstring.h"
#include "cstring_uint32.h"
#include "naive_utoa.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

//#define USE_PRINTF


/*
 * optimized function which outputs scored tuple with distance
 *
 * DIM - tuple dimension
 * ofile - output stream
 * base_p - array of variables
 * tix - index of tuple
 * alpha_score_p - pointer to ascii representation of tuple score
 * dist - tuple score distance from mean
 */
static inline
void fast_out_scored_tuple(
    const size_t DIM,
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
    const size_t vix = tix * DIM;
    char buf[sizeof ("4294967295") * DIM + sizeof ("-1.1234567890") /*+ sizeof ("-12345678901234567890.1234567890")*/];

    size_t ix = 0;
    char * p = buf;
    for (ix = 0; ix < DIM; ++ix)
    {
        cstring_uint32_t * cstrp = (cstring_uint32_t *)p;
        p = naive_utoa(base_p[vix + ix], cstrp);
        *p++ = '\t';
    }
    memcpy(p, alpha_score_p, sizeof (cstring_score_t));
    p += sizeof ("-1.1234567890") - 1;
    p -= (*alpha_score_p != '-');

    *p++ = '\t';

    if (UNLIKELY(dist > MAX_PDOUBLE))
    {
        /* case which cannot be handled by pdouble_as_cstring */
        *p = 0;

        fputs(buf, ofile);
        fprintf(ofile, "%.10lf\n", dist);
    }
    else
    {
        if (LIKELY(dist < 1.0))
        {
            /* we'll reuse score conversion function for dist smaller than 1.0 */
            cstring_score_t cstr;
            score_as_cstring(dist, &cstr);

            /* append the string */
            memcpy(p, &cstr[0], sizeof (cstr));

            p[12] = '\n';
            p[13] = 0;
            fputs(buf, ofile);
        }
        else
        {
            /* default conversion for positive double float */
            cstring_pdouble_t cstr;
            pdouble_as_cstring(dist, &cstr);

            /* append the string */
            memcpy(p, &cstr[0], sizeof (cstr));

            /* find terminating position after the least number of digits */
            char * wp = memchr(p + 12, 0x00, 7);
            *wp++ = '\n';
            *wp = 0;
            fputs(buf, ofile);
        }
    }
}


/*
 * functions to output lines with scored tuples + distance tailored for
 * specific tuple sizes
 */

static
void out_scored_tuple2(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 2;

    fprintf(ofile, "%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(2,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


static
void out_scored_tuple3(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 3;

    fprintf(ofile, "%u\t%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(3,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


static
void out_scored_tuple4(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 4;

    fprintf(ofile, "%u\t%u\t%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(4,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


static
void out_scored_tuple5(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 5;

    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(5,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


static
void out_scored_tuple6(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 6;

    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        base_p[vix + 5],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(6,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


static
void out_scored_tuple7(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 7;

    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        base_p[vix + 5],
        base_p[vix + 6],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(7,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


static
void out_scored_tuple8(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 8;

    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%s\t%.10lf\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        base_p[vix + 5],
        base_p[vix + 6],
        base_p[vix + 7],
        alpha_score_p,
        dist);
#else
    fast_out_scored_tuple(8,
        ofile, base_p, tix, alpha_score_p, dist);
#endif
}


typedef void (*out_scored_tuple_fn)(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p,
    const double dist);


static
out_scored_tuple_fn out_scored_tuple_fns[] =
{
    out_scored_tuple2,
    out_scored_tuple3,
    out_scored_tuple4,
    out_scored_tuple5,
    out_scored_tuple6,
    out_scored_tuple7,
    out_scored_tuple8,
};



/*
 * compute contents and output out5.txt file
 *
 * indexed_scores - array of sorted pairs (tuple index, score)
 * tuples - unsorted tuples (only variable part)
 * tup_dim - tuple dimension
 * mean - average score value for all tuples
 * sum_sq - sum of squared deviations for all tuples
 * s - number of standard deviations
 * nthreads - unused
 */
void out5(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    const size_t tup_dim,
    const double mean,
    const double sum_sq,
    const double s,
    int nthreads)
{

    FILE * ofile = NULL;

    const uint64_t time0 = timestamp();

    const out_scored_tuple_fn out_scored_tuple = out_scored_tuple_fns[tup_dim - 2];

    do
    {
        const char * fname = "out5.txt";
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

        //const double std_dev = std(indexed_scores, mean);
        const double std_dev = sqrt(sum_sq / indexed_scores.sz);

        const int is_odd = tup_dim % 2;
        const double cutoff = is_odd ? mean - s * std_dev : mean + s * std_dev;

        size_t ix = 0;
        for (ix = 0; ix < indexed_scores.sz; ++ix)
        {
            const size_t six = ix;
            const double score = indexed_scores.ptr[six].second;
            const size_t tix = indexed_scores.ptr[six].first;

            if ((!is_odd && (score >= cutoff)) || (is_odd && (score <= cutoff)))
            {
                cstring_score_t cscore;
                score_as_cstring(score, &cscore);

                const double dist = fabs(score - mean) / std_dev;
                out_scored_tuple(ofile, tuples.ptr, tix, &(cscore[0]), dist);
            }
        }

    } while (0);

    if (ofile != NULL)
    {
        fclose(ofile);
    }

    fprintf(stderr, "[out5] Done, %lu msec\n", timestamp() - time0);
}
