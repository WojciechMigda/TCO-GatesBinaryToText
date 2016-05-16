/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: sort_indexed_scores.h
 *
 * Description:
 *      Sorting of pairs of tuple-index/score array, sorting is done over
 *      score, descending
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


#ifndef SORT_INDEXED_SCORES_H_
#define SORT_INDEXED_SCORES_H_

#include "indexed_score.h"
#include "span.h"
#include "span_indexed_score.h"

#ifdef __cplusplus
extern "C"
{
#endif


int cmp_indexed_score_by_score_asc(const void * vap, const void * vbp);

SPAN(indexed_score_t) sort_indexed_scores(SPAN(indexed_score_t) span);


#ifdef __cplusplus
}
#endif

#endif /* SORT_INDEXED_SCORES_H_ */
