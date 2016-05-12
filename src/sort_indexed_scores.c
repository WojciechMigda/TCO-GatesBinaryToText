/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: sort_indexed_scores.c
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

#include "indexed_score.h"
#include "span.h"
#include "span_indexed_score.h"

#include <stdlib.h>


int cmp_indexed_score_by_score_asc(const void * vap, const void * vbp)
{
    const indexed_score_t * ap = (const indexed_score_t *)vap;
    const indexed_score_t * bp = (const indexed_score_t *)vbp;

    return
        ap->second < bp->second ?
            1 : (ap->second > bp->second ?
                -1 : ((ap->first < bp->first) - (ap->first > bp->first)));
}


SPAN(indexed_score_t) sort_indexed_scores(SPAN(indexed_score_t) span)
{
    qsort(span.ptr, span.sz, sizeof (span.ptr[0]), cmp_indexed_score_by_score_asc);

    return span;
}
