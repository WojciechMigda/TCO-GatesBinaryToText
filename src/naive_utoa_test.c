/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: naive_utoa_test.c
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

//#pragma GCC optimize ("-O0")

#include "naive_utoa.h"
#include "cstring_uint32.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#undef NDEBUG
#include <assert.h>

int main()
{
    srand(time(NULL));

    {
        const uint32_t val = 0;

        cstring_uint32_t cstr;
        naive_utoa(val, &cstr);

        assert(strcmp(&cstr[0], "0") == 0);
    }

    {
        const uint32_t val = 1;

        cstring_uint32_t cstr;
        naive_utoa(val, &cstr);

        assert(strcmp(&cstr[0], "1") == 0);
    }

    {
        const uint32_t val = 4294967295;

        cstring_uint32_t cstr;
        naive_utoa(val, &cstr);

        assert(strcmp(&cstr[0], "4294967295") == 0);
    }

    enum {NREP = 10000000};
    size_t ix = 0;
    for (ix = 0; ix < NREP; ++ix)
    {
        const uint32_t prv = random();

        cstring_uint32_t cstr;
        naive_utoa(prv, &cstr);

        char buf[20];
        snprintf(buf, sizeof (buf), "%u", prv);

        assert(strcmp(&cstr[0], buf) == 0);
    }

    puts("OK");

    return 0;
}
