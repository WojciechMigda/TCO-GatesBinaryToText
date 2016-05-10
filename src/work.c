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

#include "quicksort.h"
#include "threaded_sort.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>



int check_file_descriptors(FILE * f_data)
{
    if (fsize(f_data) == 0)
    {
        fprintf(stderr, "Error: empty binary file\n");
        return -1;
    }

    return 0;
}



int index_cmp(const void * va_p, const void * vb_p)
{
    DEFINE_PAIR(uint32_t, double);
    typedef PAIR(uint32_t, double) index_entry_t;

    const index_entry_t * a_p = (const index_entry_t *)va_p;
    const index_entry_t * b_p = (const index_entry_t *)vb_p;

    return a_p->second < b_p->second ?
        1 : (a_p->second > b_p->second ? -1 :
            a_p->first < b_p->first ?
                1 : (a_p->first > b_p->first ? - 1 : 0)
            );
}


int index_cmp_r(const void * va_p, const void * vb_p, void * vc_p)
{
    typedef uint32_t index_entry_t;

    const index_entry_t * a_p = (const index_entry_t *)va_p;
    const index_entry_t * b_p = (const index_entry_t *)vb_p;

    typedef struct
    {
        const uint8_t * data_p;
        uint32_t d;
    } ctx_t;
    const ctx_t * c_p = (const ctx_t *)vc_p;

    const uint32_t ia = *a_p;
    const uint32_t ib = *b_p;
    const double da = *(double *)(c_p->data_p + ia * (c_p->d * sizeof (uint32_t) + sizeof (double)) + c_p->d * sizeof (uint32_t));
    const double db = *(double *)(c_p->data_p + ib * (c_p->d * sizeof (uint32_t) + sizeof (double)) + c_p->d * sizeof (uint32_t));

    return da < db ?
        1 : (da > db ? -1 :
            ia < ib ?
                1 : (ia > ib ? - 1 : 0)
            );
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



    const SPAN(void) scored_tuples = program_options_p->scored_tuples_reader(program_options_p->in_file2);


    // build index
    {
        DEFINE_PAIR(uint32_t, double);
        typedef PAIR(uint32_t, double) index_entry_t;
        DEFINE_SPAN(index_entry_t);

        SPAN(index_entry_t) foo[2];

        {
            void * p = malloc(data_ctx.n_tuples * sizeof (index_entry_t));
            SPAN(index_entry_t) index = MAKE_SPAN(index_entry_t, p, data_ctx.n_tuples);
            size_t ix = 0;
            for (ix = 0; ix < data_ctx.n_tuples; ++ix)
            {
                const uint8_t * data_p = (const uint8_t *)scored_tuples.ptr;
                data_p += ix * (data_ctx.d * sizeof (uint32_t) + sizeof (double));
                index.ptr[ix].first = ix;
                index.ptr[ix].second = *((double *)(data_p + data_ctx.d * sizeof (uint32_t)));
            }

            qsort(index.ptr, index.sz, sizeof (index_entry_t), index_cmp);

            foo[0] = index;
        }
        {
            void * p = malloc(data_ctx.n_tuples * sizeof (index_entry_t));
            SPAN(index_entry_t) index = MAKE_SPAN(index_entry_t, p, data_ctx.n_tuples);
            size_t ix = 0;
            for (ix = 0; ix < data_ctx.n_tuples; ++ix)
            {
                const uint8_t * data_p = (const uint8_t *)scored_tuples.ptr;
                data_p += ix * (data_ctx.d * sizeof (uint32_t) + sizeof (double));
                index.ptr[ix].first = ix;
                index.ptr[ix].second = *((double *)(data_p + data_ctx.d * sizeof (uint32_t)));
            }

            QUICK_SORT(index.ptr, index.sz);
            foo[1] = index;

            threaded_sort();
        }

        size_t ix;
        for (ix = 0; ix < data_ctx.n_tuples; ++ix)
        {
            if (foo[0].ptr[ix].first != foo[1].ptr[ix].first)
            {
                printf("%zu %lf %lf\n", ix, foo[0].ptr[ix].second, foo[1].ptr[ix].second);
            }
        }

        free(foo[0].ptr);
        free(foo[1].ptr);
    }
//    {
//        typedef uint32_t index_entry_t;
//        void * p = malloc(data_ctx.n_tuples * sizeof (index_entry_t));
//        DEFINE_SPAN(index_entry_t);
//        SPAN(index_entry_t) index = MAKE_SPAN(index_entry_t, p, data_ctx.n_tuples);
//        size_t ix = 0;
//        for (ix = 0; ix < data_ctx.n_tuples; ++ix)
//        {
//            const uint8_t * data_p = (const uint8_t *)scored_tuples.ptr;
//            data_p += ix * (data_ctx.d * sizeof (uint32_t) + sizeof (double));
//            index.ptr[ix] = ix;
//        }
//
//        struct ctx_s
//        {
//            const uint8_t * data_p;
//            uint32_t d;
//        } ctx = {/*(const uint8_t *)*/scored_tuples.ptr, data_ctx.d};
//        qsort_r(index.ptr, index.sz, sizeof (index_entry_t), index_cmp_r, &ctx);
//    }


    if (program_options_p->scored_tuples_deleter(scored_tuples) < 0)
    {
        return -1;
    }

    return 0;
}
