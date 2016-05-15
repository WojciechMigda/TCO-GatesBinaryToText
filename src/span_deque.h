/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: span_deque.h
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


#ifndef SPAN_DEQUE_H_
#define SPAN_DEQUE_H_

#include "span.h"
#include "deque.h"

#ifdef __cplusplus
extern "C"
{
#endif


DEFINE_SPAN(deque_t);
DEFINE_SPAN_T(deque_t);


#ifdef __cplusplus
}
#endif

#endif /* SPAN_DEQUE_H_ */
