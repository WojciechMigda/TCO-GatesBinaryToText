/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: option_type.h
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


#ifndef OPTION_TYPE_H_
#define OPTION_TYPE_H_

#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define DEFINE_OPTION_TYPE(_Tp) \
typedef struct optional_##_Tp##_s \
{ \
    bool_t _maybe; \
    _Tp value; \
} optional_##_Tp##_t

#define OPTION_TYPE(_Tp) struct optional_##_Tp##_s

#define OPTION_TYPE_IS_SOME(what) (what._maybe == True)

#define OPTION_TYPE_VALUE(what) (what.value)

#define OPTION_TYPE_NONE(_Tp) (OPTION_TYPE(_Tp)){False}

#define OPTION_TYPE_SOME(_Tp, Value) (OPTION_TYPE(_Tp)){True, Value}

#ifdef __cplusplus
}
#endif

#endif /* OPTION_TYPE_H_ */
