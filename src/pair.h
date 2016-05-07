/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pair.h
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


#ifndef PAIR_H_
#define PAIR_H_

#ifdef __cplusplus
extern "C"
{
#endif


#define DEFINE_PAIR(_Tp1, _Tp2) \
typedef struct pair_##_Tp1##_##_Tp2##_s \
{ \
    _Tp1 first; \
    _Tp2 second; \
} pair_##_Tp1##_##_Tp2##_t


#define PAIR(_Tp1, _Tp2) struct pair_##_Tp1##_##_Tp2##_s

#define MAKE_PAIR(_Tp1, _Tp2, p, q) (PAIR(_Tp1, _Tp2)){p, q}


#ifdef __cplusplus
}
#endif

#endif /* PAIR_H_ */
