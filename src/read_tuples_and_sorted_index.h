/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_tuples_and_sorted_index.h
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


#ifndef READ_TUPLES_AND_SORTED_INDEX_H_
#define READ_TUPLES_AND_SORTED_INDEX_H_

#include "pair.h"
#include "span_indexed_score.h"
#include "span_var.h"
#include "var_type.h"
#include "indexed_score.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif


PAIR(SPAN_T(var_t), SPAN_T(indexed_score_t))
read_tuples_and_sorted_index(
    const char * fname,
    size_t ntuples,
    size_t tup_dim,
    int nthreads);


#ifdef __cplusplus
}
#endif

#endif /* READ_TUPLES_AND_SORTED_INDEX_H_ */
