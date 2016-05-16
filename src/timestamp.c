/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: timestamp.c
 *
 * Description:
 *      Retrieval of current time (in msec)
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

#include <sys/time.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
