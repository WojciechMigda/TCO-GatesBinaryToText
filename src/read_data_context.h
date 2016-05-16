/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: read_data_context.h
 *
 * Description:
 *      Read data context from specified binary file
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2016-05-10   wm              Initial version
 *
 ******************************************************************************/


#ifndef READ_DATA_CONTEXT_H_
#define READ_DATA_CONTEXT_H_

#include "data_context.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { BAD_CONTEXT_MARKER = 1 };

data_context_t read_data_context(const char * fname);


#ifdef __cplusplus
}
#endif

#endif /* READ_DATA_CONTEXT_H_ */
