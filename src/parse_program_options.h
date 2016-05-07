/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: parse_program_options.h
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
 * 2016-05-07   wm              Initial version
 *
 ******************************************************************************/


#ifndef PARSE_PROGRAM_OPTIONS_H_
#define PARSE_PROGRAM_OPTIONS_H_

#include "program_options.h"
#include "pair.h"

#ifdef __cplusplus
extern "C"
{
#endif


DEFINE_PAIR(int, program_options_t);

PAIR(int, program_options_t) parse_program_options(
    int argc,
    char const * argv[]);


#ifdef __cplusplus
}
#endif

#endif /* PARSE_PROGRAM_OPTIONS_H_ */
