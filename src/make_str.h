/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: make_str.h
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
 * 2016-05-10   wm              Initial version
 *
 ******************************************************************************/


#ifndef MAKE_STR_H_
#define MAKE_STR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define MAKE_STR2(p, q)         p ## q
#define MAKE_STR3(p, q, r)      p ## q ## r
#define MAKE_STR4(p, q, r, s)   p ## q ## r ## s

#ifdef __cplusplus
}
#endif

#endif /* MAKE_STR_H_ */
