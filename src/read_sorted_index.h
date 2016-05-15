/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_sorted_index.h
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
 * 2016-05-11   wm              Initial version
 *
 ******************************************************************************/


#ifndef READ_SORTED_INDEX_H_
#define READ_SORTED_INDEX_H_

#include "span.h"
#include "indexed_score.h"
#include "span_indexed_score.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

SPAN(indexed_score_t) read_sorted_index(
    const char * fname,
    size_t ntuples,
    size_t tupdim,
    int nthreads);

#ifdef __cplusplus
}
#endif

#endif /* READ_SORTED_INDEX_H_ */
