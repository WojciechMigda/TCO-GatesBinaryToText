/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: num_procs.h
 *
 * Description:
 *      Query number of available processors,
 *      `man get_nprocs`
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


#ifndef NUM_PROCS_H_
#define NUM_PROCS_H_

#ifdef __cplusplus
extern "C"
{
#endif


int num_procs(void);


#ifdef __cplusplus
}
#endif

#endif /* NUM_PROCS_H_ */
