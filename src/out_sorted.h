/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out_sorted.h
 *
 * Description:
 *      Calculate and output contents of files out1.txt and out2.txt
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2016-05-14   wm              Initial version
 *
 ******************************************************************************/


#ifndef OUT_SORTED_H_
#define OUT_SORTED_H_

#include "indexed_score.h"
#include "span_indexed_score.h"
#include "var_type.h"
#include "span_var.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif


void out1(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    size_t tup_dim,
    size_t n_tup,
    int nthreads);


void out2(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    size_t tup_dim,
    size_t n_tup,
    int nthreads);


#ifdef __cplusplus
}
#endif

#endif /* OUT_SORTED_H_ */
