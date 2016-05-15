/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_tuples_and_scored_index.h
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
 * 2016-05-12   wm              Initial version
 *
 ******************************************************************************/


#ifndef READ_TUPLES_AND_SCORED_INDEX_H_
#define READ_TUPLES_AND_SCORED_INDEX_H_

#include "pair.h"
#include "span.h"
#include "indexed_score.h"
#include "span_indexed_score.h"
#include "span_var.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

SPAN_T(indexed_score_t)
read_tuples_and_scored_index_batch(
    const char * fname,
    const size_t tup_dim,
    const size_t begin,
    const size_t end,
    SPAN(var_t) vspan,
    double * sum_sq,
    const double mean
    );

#ifdef __cplusplus
}
#endif

#endif /* READ_TUPLES_AND_SCORED_INDEX_H_ */
