/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: cstring_pdouble_test.c
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
 * 2016-05-16   wm              Initial version
 *
 ******************************************************************************/

#include "cstring_pdouble.h"
#include "pdouble_as_cstring.h"

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
        const double v = 123456.0123456789;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "123456.0123456789") == 0);
    }

    {
        const double v = 12345.0123456789;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "12345.0123456789") == 0);
    }

    {
        const double v = 2345.0123456789;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "2345.0123456789") == 0);
    }

    {
        const double v = 789.0123456789;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "789.0123456789") == 0);
    }

    {
        const double v = 54.0123456789;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "54.0123456789") == 0);
    }

    {
        const double v = 3.0123456789;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "3.0123456789") == 0);
    }

    {
        const double v = 0.0;
        cstring_pdouble_t cstr;
        pdouble_as_cstring(v, &cstr);
        assert(strcmp(&cstr[0], "0.0000000000") == 0);
    }

    enum {NREP = 1000000};
    size_t ix = 0;
    for (ix = 0; ix < NREP; ++ix)
    {
        const uint64_t priv = ((uint64_t)random() << (49 - 32)) ^ random();
        //const uint64_t priv = ((uint64_t)RAND_MAX << (49 - 32)) ^ random();
        const double prv = priv / (double)RAND_MAX;

        cstring_pdouble_t cstr;
        pdouble_as_cstring(prv, &cstr);

        char buf[30];
        snprintf(buf, sizeof (buf), "%.10lf", prv);

        if (strcmp(&cstr[0], buf) != 0)
        {
            printf("%s vs. %s\n", &cstr[0], buf);
        }
        assert(strcmp(&cstr[0], buf) == 0);
    }

    for (ix = 0; ix < NREP; ++ix)
    {
        const uint64_t priv = ((uint64_t)random() << (45 - 32)) ^ random();
        const double prv = priv / (double)RAND_MAX;

        cstring_pdouble_t cstr;
        pdouble_as_cstring(prv, &cstr);

        char buf[30];
        snprintf(buf, sizeof (buf), "%.10lf", prv);

        if (strcmp(&cstr[0], buf) != 0)
        {
            printf("%s vs. %s\n", &cstr[0], buf);
        }
        assert(strcmp(&cstr[0], buf) == 0);
    }

    for (ix = 0; ix < NREP; ++ix)
    {
        const uint64_t priv = ((uint64_t)random() << (41 - 32)) ^ random();
        const double prv = priv / (double)RAND_MAX;

        cstring_pdouble_t cstr;
        pdouble_as_cstring(prv, &cstr);

        char buf[30];
        snprintf(buf, sizeof (buf), "%.10lf", prv);

        if (strcmp(&cstr[0], buf) != 0)
        {
            printf("%s vs. %s\n", &cstr[0], buf);
        }
        assert(strcmp(&cstr[0], buf) == 0);
    }

    puts("OK");

    return 0;
}
