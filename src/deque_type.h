/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: deque_type.h
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


#ifndef DEQUE_TYPE_H_
#define DEQUE_TYPE_H_

#include "tuple_ix_type.h"

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum {DEQUE_PIECE_NELEM = 512};

typedef struct deque_piece_s
{
    struct deque_piece_s * next_p;
    tuple_ix_t data[DEQUE_PIECE_NELEM];
} deque_piece_t;

typedef struct deque_s
{
    size_t nelem;
    struct deque_piece_s * head_p;
    struct deque_piece_s * tail_p;
} deque_t;


#ifdef __cplusplus
}
#endif

#endif /* DEQUE_TYPE_H_ */
