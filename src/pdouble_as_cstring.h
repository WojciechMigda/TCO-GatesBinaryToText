/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: pdouble_as_cstring.h
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
 * 2016-05-16   wm              Initial version
 *
 ******************************************************************************/


#ifndef PDOUBLE_AS_CSTRING_H_
#define PDOUBLE_AS_CSTRING_H_

#include "cstring_score.h"
#include "likely.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif


static inline
size_t naive_ultoa_padded17(uint64_t v, char * p)
{
    p[sizeof (cstring_pdouble_t) - 1] = 0;

    if (UNLIKELY(v == 0))
    {
        memset(p, '0', sizeof (cstring_pdouble_t) - 1);
    }
    else
    {
        char * wp = p + sizeof (cstring_pdouble_t) - 2;

        do
        {
            const int64_t rem = v % 10;
            v /= 10;
            *wp-- = '0' + rem;
        } while (v != 0 && wp != p);
        while (wp != p)
        {
            *wp-- = '0';
        }
        p[0] = '0';
    }

    return sizeof (cstring_pdouble_t) - 1;
}


static inline
void pdouble_as_cstring(const double dbl, cstring_pdouble_t * out_p)
{
    union
    {
        double d;
        uint64_t l;
    } magic;

    const double dbl10 = dbl * 1e10;

    magic.d = dbl10 + 6755399441055744.0;
    magic.l <<= 13;
    magic.l >>= 13;
    const double frac = dbl10 - magic.l;

    char * p = &(*out_p)[0];
    if (UNLIKELY(frac == 0.5 || frac == -0.5))
    {
        /* this is the case where rounding rules differ between *printf
         * and the rest of the world*/
        snprintf(p, sizeof (*out_p), "%.10lf", dbl);
    }
    else
    {
memset(p, '#', 18);
        naive_ultoa_padded17(magic.l, p);

        char * wp = p + 1;
        size_t ix = 0;
        for (ix = 0; ix < 6; ++ix, ++wp)
        {
            if (*wp != '0')
            {
                break;
            }
        }
        wp -= (ix == 6);
        ix -= (ix == 6);

        while (ix != 6)
        {
            *p++ = *wp++;
            ++ix;
        }
        *p++ = '.';
        if (LIKELY(p != wp))
        {
            for (ix = 0; ix < 10; ++ix)
            {
                *p++ = *wp++;
            }
            *p = 0;
        }
    }
}


#ifdef __cplusplus
}
#endif

#endif /* PDOUBLE_AS_CSTRING_H_ */
