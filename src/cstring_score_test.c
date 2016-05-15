/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: cstring_score_test.c
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

#include "cstring_score.h"
#include "score_as_cstring.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#undef NDEBUG
#include <assert.h>

int main()
{
    srand(time(NULL));

    {
        const double v = 0.0;
        cstring_score_t cstr;
        score_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "0.0000000000") == 0);
    }

    {
        const double v = -0.0;
        cstring_score_t cstr;
        score_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "-0.0000000000") == 0);
    }

    {
        const double v = 1.0;
        cstring_score_t cstr;
        score_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "1.0000000000") == 0);
    }

    {
        const double v = -1.0;
        cstring_score_t cstr;
        score_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "-1.0000000000") == 0);
    }

    enum {NREP = 10000000};
    size_t ix = 0;
    for (ix = 0; ix < NREP; ++ix)
    {
        const double prv = ((double)random() / RAND_MAX) * 2.0 - 1.0;

        cstring_score_t cstr;
        score_as_cstring(prv, &cstr);

        char buf[20];
        snprintf(buf, sizeof (buf), "%.10lf", prv);

        assert(strcmp(&cstr[0], buf) == 0);
    }

    puts("OK");

    return 0;
}
