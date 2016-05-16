/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: owner.h
 *
 * Description:
 *      Macro to mimic owner<T> template from C++ core guidelines
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


#ifndef OWNER_H_
#define OWNER_H_

#ifdef __cplusplus
extern "C"
{
#endif


#define owner(P) P


#ifdef __cplusplus
}
#endif

#endif /* OWNER_H_ */
