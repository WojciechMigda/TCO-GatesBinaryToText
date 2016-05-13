/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: fbstp.h
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
 * 2016-05-13   wm              Initial version
 *
 ******************************************************************************/


#ifndef FBSTP_H_
#define FBSTP_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


static inline
void fbstp(const double what, uint8_t (*bcd_p)[10])
{
    asm("fbstp %0" : "=m" (bcd_p[0]) : "t" (what) : "st");
}


#ifdef __cplusplus
}
#endif

#endif /* FBSTP_H_ */
