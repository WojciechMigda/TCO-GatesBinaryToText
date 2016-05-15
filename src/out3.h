/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out3.h
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


#ifndef OUT3_H_
#define OUT3_H_

#include "span_indexed_score.h"
#include "span_var.h"
#include "span_deque.h"

#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif


void build_var_to_tupix(
    SPAN(deque_t) var_to_tupix,
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    const size_t tup_dim
    );

void out3(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    SPAN(deque_t) var_to_tupix,
    const size_t tup_dim,
    const size_t k,
    int nthreads);


#ifdef __cplusplus
}
#endif

#endif /* OUT3_H_ */
