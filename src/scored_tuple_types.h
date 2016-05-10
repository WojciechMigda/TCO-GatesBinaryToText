/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: scored_tuple_types.h
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


#ifndef SCORED_TUPLE_TYPES_H_
#define SCORED_TUPLE_TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef TUPLE_DIM
#error "Name conflict: TUPLE_DIM"
#endif

#define TUPLE_DIM 2
#include "scored_tuple_type_gen.h"

#define TUPLE_DIM 3
#include "scored_tuple_type_gen.h"

#define TUPLE_DIM 4
#include "scored_tuple_type_gen.h"

#define TUPLE_DIM 5
#include "scored_tuple_type_gen.h"

#define TUPLE_DIM 6
#include "scored_tuple_type_gen.h"

#define TUPLE_DIM 7
#include "scored_tuple_type_gen.h"

#define TUPLE_DIM 8
#include "scored_tuple_type_gen.h"

#ifdef __cplusplus
}
#endif

#endif /* SCORED_TUPLE_TYPES_H_ */
