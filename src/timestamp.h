/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: timestamp.h
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


#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


uint64_t timestamp(void);


#ifdef __cplusplus
}
#endif

#endif /* TIMESTAMP_H_ */
