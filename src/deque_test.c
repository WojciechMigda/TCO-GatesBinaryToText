/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: deque_test.c
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

#include "deque.h"
#include "deque_type.h"
#include "tuple_ix_type.h"
#include "span_tuple_ix.h"

#include <stddef.h>

#undef NDEBUG
#include <assert.h>

int main()
{
    {
        deque_t d = new_deque();

        SPAN(tuple_ix_t) span = deque_as_span(&d);
        assert(span.ptr == NULL);
        assert(span.sz == 0);

        deque_free(&d);
    }

    {
        deque_t d = new_deque();

        deque_push_back(&d, 1234);

        SPAN(tuple_ix_t) span = deque_as_span(&d);
        assert(span.ptr != NULL);
        assert(span.sz == 1);
        assert(span.ptr[0] == 1234);

        deque_free(&d);
        free(span.ptr);
    }

    {
        deque_t d = new_deque();
        enum {NREP = 40000};

        size_t ix = 0;
        for (ix = 0; ix < NREP; ++ix)
        {
            deque_push_back(&d, ix + 1234);
        }

        SPAN(tuple_ix_t) span = deque_as_span(&d);
        assert(span.ptr != NULL);
        assert(span.sz == NREP);
        for (ix = 0; ix < NREP; ++ix)
        {
            assert(span.ptr[ix] == (ix + 1234));
        }

        deque_free(&d);
        free(span.ptr);
    }

    {
        deque_t d = new_deque();
        enum {NREP = 40000000};

        size_t ix = 0;
        for (ix = 0; ix < NREP; ++ix)
        {
            deque_push_back(&d, ix + 1234);
        }

        SPAN(tuple_ix_t) span = deque_as_span(&d);
        assert(span.ptr != NULL);
        assert(span.sz == NREP);
        for (ix = 0; ix < NREP; ++ix)
        {
            assert(span.ptr[ix] == (ix + 1234));
        }

        deque_free(&d);
        free(span.ptr);
    }


    return 0;
}
