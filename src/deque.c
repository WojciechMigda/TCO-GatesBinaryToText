/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: deque.c
 *
 * Description:
 *      Deque operations
 *      "Deque" is a singly linked list of arrays of indices of sorted scored
 *      tuples.
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

#include "deque_type.h"
#include "span.h"
#include "bool.h"
#include "tuple_ix_type.h"
#include "span_tuple_ix.h"
#include "min_max.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * check if deque is empty
 */
static bool_t deque_is_empty(const struct deque_s * self)
{
    return (self->head_p == NULL) && (self->tail_p == NULL) ? True : False;
}


/*
 * allocate new deque element
 */
deque_piece_t * deque_new_piece(void)
{
    deque_piece_t * piece_p = malloc(sizeof (deque_piece_t));

    if (piece_p == NULL)
    {
        fprintf(stderr, "[DEQUE] piece allocation error\n");
        return NULL;
    }

    piece_p->next_p = NULL;
    return piece_p;
}


/*
 * extend deque with new element to fit another value
 */
static void deque_extend(struct deque_s * self)
{
    deque_piece_t * piece_p = deque_new_piece();

    if (piece_p != NULL)
    {
        if (deque_is_empty(self) == True)
        {
            self->head_p = piece_p;
            self->tail_p = piece_p;
        }
        else
        {
            self->tail_p->next_p = piece_p;
            self->tail_p = piece_p;
        }
    }
}


/*
 * add new value to the deque
 */
void deque_push_back(struct deque_s * self, const tuple_ix_t what)
{
    const size_t tail_nelem = self->nelem % DEQUE_PIECE_NELEM;

    if (tail_nelem == 0)
    {
        deque_extend(self);
    }

    self->tail_p->data[tail_nelem] = what;
    self->nelem++;
}


/*
 * convert deque to continuous array of values, caller owns the allocated
 * pointer
 */
SPAN(tuple_ix_t)
deque_as_span(const struct deque_s * self)
{
    if (self->nelem == 0)
    {
        return NULL_SPAN(tuple_ix_t);
    }

    tuple_ix_t * data_p = malloc(self->nelem * sizeof (tuple_ix_t));
    if (data_p == NULL)
    {
        fprintf(stderr, "[DEQUE] span allocation error\n");
        return NULL_SPAN(tuple_ix_t);
    }
    else
    {
        deque_piece_t * this_p = self->head_p;

        size_t to_copy = self->nelem;

        while (this_p != NULL)
        {
            deque_piece_t * next_p = this_p->next_p;

            const size_t batch_sz = MIN(DEQUE_PIECE_NELEM, to_copy);

            memcpy(&data_p[self->nelem - to_copy], this_p->data, batch_sz * sizeof (tuple_ix_t));

            to_copy -= batch_sz;

            this_p = next_p;
        };
    }

    return MAKE_SPAN(tuple_ix_t, data_p, self->nelem);
}


/*
 * free deque and all resources which belong to it
 */
void deque_free(struct deque_s * self)
{
    deque_piece_t * this_p = self->head_p;

    while (this_p != NULL)
    {
        deque_piece_t * next_p = this_p->next_p;
        free(this_p);
        this_p = next_p;
    };

    self->nelem = 0u;
    self->head_p = NULL;
    self->tail_p = NULL;
}
