/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: naive_utoa.h
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
 * 2016-05-15   wm              Initial version
 *
 ******************************************************************************/


#ifndef NAIVE_UTOA_H_
#define NAIVE_UTOA_H_

#include "cstring_uint32.h"
#include "likely.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


static inline
char * naive_utoa(uint32_t val, cstring_uint32_t * out_p)
{
    if (UNLIKELY(val == 0))
    {
        (*out_p)[0] = '0';
        (*out_p)[1] = 0;
        return &(*out_p)[1];
    }

    char buf[sizeof ("4294967295")];

    char * p = &buf[sizeof (buf) - 1];

    do
    {
        uint32_t rem = val % 10;
        val /= 10;
        *p-- = '0' + rem;
    } while (val != 0);

    char * wp = &(*out_p)[0];
    while (++p != &buf[sizeof (buf)])
    {
        *wp++ = *p;
    }
    *wp = 0;

    return wp;
}


#ifdef __cplusplus
}
#endif

#endif /* NAIVE_UTOA_H_ */
