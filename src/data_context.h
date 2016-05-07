/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: data_context.h
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


#ifndef DATA_CONTEXT_H_
#define DATA_CONTEXT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct __attribute__ ((__packed__)) data_context_s
{
    uint32_t dummy;
    uint32_t d; /* tuple dimension */
    uint32_t n_vars;
    uint64_t n_tuples;
    double average;
} data_context_t;


#ifdef __cplusplus
}
#endif

#endif /* DATA_CONTEXT_H_ */
