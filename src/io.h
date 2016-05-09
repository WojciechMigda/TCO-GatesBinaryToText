/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: io.h
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


#ifndef IO_H_
#define IO_H_

#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif


size_t fsize(FILE * ifile);


#ifdef __cplusplus
}
#endif

#endif /* IO_H_ */
