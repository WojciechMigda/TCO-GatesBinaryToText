/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: indexed_score.h
 *
 * Description:
 *      Pair of tuple index and corresponding score
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


#ifndef INDEXED_SCORE_H_
#define INDEXED_SCORE_H_

#include "pair.h"
#include "tuple_ix_type.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


DEFINE_PAIR(tuple_ix_t, double) __attribute__ ((packed));

typedef PAIR(tuple_ix_t, double) indexed_score_t;


#ifdef __cplusplus
}
#endif

#endif /* INDEXED_SCORE_H_ */
