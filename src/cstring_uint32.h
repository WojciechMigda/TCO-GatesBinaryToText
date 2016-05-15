/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: cstring_uint32.h
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
 * 2016-05-15   wm              Initial version
 *
 ******************************************************************************/


#ifndef CSTRING_UINT32_H_
#define CSTRING_UINT32_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef char (cstring_uint32_t)[1 + sizeof ("4294967295")];

#ifdef __cplusplus
}
#endif

#endif /* CSTRING_UINT32_H_ */
