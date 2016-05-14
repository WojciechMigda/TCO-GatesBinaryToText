/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: out4.h
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


#ifndef OUT4_H_
#define OUT4_H_

#include "span.h"
#include "indexed_score.h"
#include "span_indexed_score.h"

#ifdef __cplusplus
extern "C"
{
#endif


void out4(
    SPAN(indexed_score_t) indexed_scores,
    const double bucket_sz,
    int nthreads);


#ifdef __cplusplus
}
#endif

#endif /* OUT4_H_ */
