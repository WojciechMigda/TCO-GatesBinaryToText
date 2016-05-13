/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: deque.h
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
 * 2016-05-13   wm              Initial version
 *
 ******************************************************************************/


#ifndef DEQUE_H_
#define DEQUE_H_

#include "deque_type.h"
#include "span.h"
#include "tuple_ix_type.h"
#include "span_tuple_ix.h"

#include <libio.h>

#ifdef __cplusplus
extern "C"
{
#endif

static const NULL_DEQUE = {0u, NULL, NULL}

static inline
deque_t new_deque(void)
{
    return NULL_DEQUE;
}


void deque_push_back(struct deque_s * self, const tuple_ix_t what);

SPAN(tuple_ix_t) deque_as_span(const struct deque_s * self);

void deque_free(struct deque_s * self);


#ifdef __cplusplus
}
#endif

#endif /* DEQUE_H_ */
