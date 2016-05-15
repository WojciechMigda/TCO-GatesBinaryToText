/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out_sorted.c
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

#include "indexed_score.h"
#include "var_type.h"
#include "span_indexed_score.h"
#include "span_var.h"
#include "min_max.h"
#include "cstring_score.h"
#include "score_as_cstring.h"
#include "timestamp.h"
#include "cstring_uint32.h"
#include "naive_utoa.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#define USE_PRINTF

static inline
void fast_out_scored_tuple(
    const size_t DIM,
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
    const size_t vix = tix * DIM;
    char buf[sizeof ("4294967295") * DIM + sizeof ("-1.1234567890")];

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
    *p++ = '\n';
    *p = 0;

    fputs(buf, ofile);
}


static
void out_scored_tuple2(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 2;
    // https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
    //__builtin_prefetch(&base_p[vix], 0, 0);

    fprintf(ofile, "%u\t%u\t%s\n",
        base_p[vix],
        base_p[vix + 1],
        alpha_score_p);

    // for benchmarks
    //sprintf(foo, "%u\t%u\t%s\n", base_p[vix], base_p[vix + 1], alpha_score_p);
    //fputs("1234\t4567\t1.0000000000\n", ofile);
#else
    fast_out_scored_tuple(2,
        ofile, base_p, tix, alpha_score_p);
#endif
}


static
void out_scored_tuple3(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 3;
        fprintf(ofile, "%u\t%u\t%u\t%s\n",
            base_p[vix],
            base_p[vix + 1],
            base_p[vix + 2],
            alpha_score_p);
#else
    fast_out_scored_tuple(3,
        ofile, base_p, tix, alpha_score_p);
#endif
}


static
void out_scored_tuple4(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 4;
    fprintf(ofile, "%u\t%u\t%u\t%u\t%s\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        alpha_score_p);
#else
    fast_out_scored_tuple(4,
        ofile, base_p, tix, alpha_score_p);
#endif
}


static
void out_scored_tuple5(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 5;
    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%s\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        alpha_score_p);
#else
    fast_out_scored_tuple(5,
        ofile, base_p, tix, alpha_score_p);
#endif
}


static
void out_scored_tuple6(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 6;
    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%u\t%s\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        base_p[vix + 5],
        alpha_score_p);
#else
    fast_out_scored_tuple(6,
        ofile, base_p, tix, alpha_score_p);
#endif
}


static
void out_scored_tuple7(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 7;
    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%u\t%u\t%s\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        base_p[vix + 5],
        base_p[vix + 6],
        alpha_score_p);
#else
    fast_out_scored_tuple(7,
        ofile, base_p, tix, alpha_score_p);
#endif
}


static
void out_scored_tuple8(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p)
{
#ifdef USE_PRINTF
    const size_t vix = tix * 8;
    fprintf(ofile, "%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%s\n",
        base_p[vix],
        base_p[vix + 1],
        base_p[vix + 2],
        base_p[vix + 3],
        base_p[vix + 4],
        base_p[vix + 5],
        base_p[vix + 6],
        base_p[vix + 7],
        alpha_score_p);
#else
    fast_out_scored_tuple(8,
        ofile, base_p, tix, alpha_score_p);
#endif
}


typedef void (*out_scored_tuple_fn)(
    FILE * ofile,
    const var_t * base_p,
    const size_t tix,
    const char * alpha_score_p);


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


void out2(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    size_t tup_dim,
    size_t n_tup,
    int nthreads)
{
    const size_t total_ntup = tuples.sz / tup_dim;
    n_tup = MIN(n_tup, total_ntup);

    const out_scored_tuple_fn out_scored_tuple = out_scored_tuple_fns[tup_dim - 2];

    FILE * ofile = NULL;

    uint64_t time0 = timestamp();

    do
    {
        const char * fname = "out2.txt";
        remove(fname);
        ofile = fopen(fname, "wt");

        if (ofile == NULL)
        {
            fprintf(stderr, "[%s] Could not open file %s for writting\n", __FILE__, fname);
            break;
        }
        setvbuf(ofile, NULL, _IOFBF, 0);

        if (indexed_scores.ptr == NULL || tuples.ptr == NULL)
        {
            fprintf(stderr, "[%s] NULL pointer in indexed_scores [%p] or tuples [%p]\n",
                __FILE__, (void *)indexed_scores.ptr, (void *)tuples.ptr);
            break;
        }

        // fully sequential
        //if (0)
        {
            size_t ix = 0;

            for (ix = 0; ix < n_tup; ++ix)
            {
                const size_t six = total_ntup - 1 - ix;
                const double score = indexed_scores.ptr[six].second;
                const size_t tix = indexed_scores.ptr[six].first;

                cstring_score_t cscore;
                score_as_cstring(score, &cscore);
                out_scored_tuple(ofile, tuples.ptr, tix, &(cscore[0]));
            }
        }

    } while(0);

    if (ofile != NULL)
    {
        fclose(ofile);
    }

    fprintf(stderr, "[out2] Done, %lu msec\n", timestamp() - time0);
}


void out1(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    size_t tup_dim,
    size_t n_tup,
    int nthreads)
{
    const size_t total_ntup = tuples.sz / tup_dim;
    n_tup = MIN(n_tup, total_ntup);

    const out_scored_tuple_fn out_scored_tuple = out_scored_tuple_fns[tup_dim - 2];

    FILE * ofile = NULL;

    uint64_t time0 = timestamp();

    do
    {
        const char * fname = "out1.txt";
        remove(fname);
        ofile = fopen(fname, "wt");

        if (ofile == NULL)
        {
            fprintf(stderr, "[%s] Could not open file %s for writting\n", __FILE__, fname);
            break;
        }
        setvbuf(ofile, NULL, _IOFBF, 0);

        if (indexed_scores.ptr == NULL || tuples.ptr == NULL)
        {
            fprintf(stderr, "[%s] NULL pointer in indexed_scores [%p] or tuples [%p]\n",
                __FILE__, (void *)indexed_scores.ptr, (void *)tuples.ptr);
            break;
        }

        // fully sequential
        //if (0)
        {
            size_t ix = 0;

            for (ix = 0; ix < n_tup; ++ix)
            {
                const size_t six = ix;
                const double score = indexed_scores.ptr[six].second;
                const size_t tix = indexed_scores.ptr[six].first;

                cstring_score_t cscore;
                score_as_cstring(score, &cscore);
                out_scored_tuple(ofile, tuples.ptr, tix, &(cscore[0]));
            }
        }

    } while(0);

    if (ofile != NULL)
    {
        fclose(ofile);
    }

    fprintf(stderr, "[out1] Done, %lu msec\n", timestamp() - time0);
}
