/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out5.h
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
 * 2016-05-14   wm              Initial version
 *
 ******************************************************************************/


#ifndef OUT5_H_
#define OUT5_H_

#include "span.h"
#include "indexed_score.h"
#include "span_indexed_score.h"
#include "var_type.h"
#include "span_var.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif


void out5(
    SPAN(indexed_score_t) indexed_scores,
    SPAN(var_t) tuples,
    const size_t tup_dim,
    const double mean,
    const double sum_sq,
    const double s,
    int nthreads);


#ifdef __cplusplus
}
#endif

#endif /* OUT5_H_ */
