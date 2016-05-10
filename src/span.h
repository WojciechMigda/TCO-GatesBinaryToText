/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: span.h
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


#ifndef SPAN_H_
#define SPAN_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define DEFINE_SPAN(_Tp) \
struct span_##_Tp##_s \
{ \
    _Tp * ptr; \
    size_t sz; /* number of elements, may be different that number of bytes */ \
}


#define SPAN(_Tp) struct span_##_Tp##_s

#define MAKE_SPAN(_Tp, ptr, sz) (SPAN(_Tp)){ptr, sz}

#define NULL_SPAN(_Tp) MAKE_SPAN(_Tp, NULL, 0)

#ifdef __cplusplus
}
#endif

#endif /* SPAN_H_ */
