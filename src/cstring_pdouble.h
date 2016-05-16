/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: cstring_pdouble.h
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
 * 2016-05-16   wm              Initial version
 *
 ******************************************************************************/


#ifndef CSTRING_PDOUBLE_H_
#define CSTRING_PDOUBLE_H_

#ifdef __cplusplus
extern "C"
{
#endif

static const double MAX_PDOUBLE = 100000.;

typedef char (cstring_pdouble_t)[sizeof ("123456.0123456789")];

#ifdef __cplusplus
}
#endif

#endif /* CSTRING_PDOUBLE_H_ */
