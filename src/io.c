/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: io.c
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
 * 2016-05-09   wm              Initial version
 *
 ******************************************************************************/

#include <stddef.h>
#include <stdio.h>


size_t fsize(FILE * ifile)
{
    const size_t prior_pos = ftell(ifile);

    fseek(ifile, 0L, SEEK_END);

    const size_t sz = ftell(ifile);

    fseek(ifile, prior_pos, SEEK_SET);

    return sz;
}
