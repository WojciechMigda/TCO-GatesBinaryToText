/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: score_as_cstring.h
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


#ifndef SCORE_AS_CSTRING_H_
#define SCORE_AS_CSTRING_H_

#include "cstring_score.h"
#include "likely.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>

#ifdef __cplusplus
extern "C"
{
#endif

static inline
void score_as_cstring(const double score, cstring_score_t * out_p)
{
    union
    {
        double d;
        int64_t l;
    } magic;

    const double score10 = score * 1e10;

    magic.d = score10 + 6755399441055744.0;
    magic.l <<= 13;
    magic.l >>= 13;
    const double frac = score10 - magic.l;

    char * p = &(*out_p)[0];
    if (UNLIKELY(frac == 0.5 || frac == -0.5))
    {
        snprintf(p, sizeof (*out_p), "%.10lf", score);
    }
    else
    {
        p[0] = '-';
        p += !!signbit(score);
        const size_t sz = snprintf(p, sizeof (*out_p), "%012ld", magic.l);

        p[sz - 12] = p[sz - 11]; /* leading digit */
        p[sz - 11] = '.';
    }
}


#ifdef __cplusplus
}
#endif

#endif /* SCORE_AS_CSTRING_H_ */
