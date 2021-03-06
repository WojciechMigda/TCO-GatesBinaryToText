/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: pair.h
 *
 * Description:
 *      C version of std::pair<T>
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


#ifndef PAIR_H_
#define PAIR_H_

#include "str_concat.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define PAIR(_Tp1, _Tp2) struct STR_CONCAT5(pair_, _Tp1, _, _Tp2, _s)
#define PAIR_T(_Tp1, _Tp2) STR_CONCAT5(pair_, _Tp1, _, _Tp2, _t)

#define DEFINE_PAIR(_Tp1, _Tp2) \
PAIR(_Tp1, _Tp2) \
{ \
    _Tp1 first; \
    _Tp2 second; \
}

#define DEFINE_PAIR_T(_Tp1, _Tp2) typedef PAIR(_Tp1, _Tp2) PAIR_T(_Tp1, _Tp2) __attribute__ ((unused))

#define MAKE_PAIR(_Tp1, _Tp2, p, q) (PAIR(_Tp1, _Tp2)){p, q}


#ifdef __cplusplus
}
#endif

#endif /* PAIR_H_ */
