/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: str_concat.h
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


#ifndef STR_CONCAT_H_
#define STR_CONCAT_H_

#include "make_str.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define STR_CONCAT2(p, q)           MAKE_STR2(p, q)
#define STR_CONCAT3(p, q, r)        MAKE_STR3(p, q, r)
#define STR_CONCAT4(p, q, r, s)     MAKE_STR4(p, q, r, s)


#ifdef __cplusplus
}
#endif

#endif /* STR_CONCAT_H_ */
