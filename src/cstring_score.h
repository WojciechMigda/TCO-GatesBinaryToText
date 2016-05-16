/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: cstring_score.h
 *
 * Description:
 *      Convert double float in range[-1.0, 1.0] to ascii representation.
 *      Used mainly for tuple scores (hence the name)
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


#ifndef CSTRING_SCORE_H_
#define CSTRING_SCORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


typedef char (cstring_score_t)[sizeof ("--1.0123456789")];


#ifdef __cplusplus
}
#endif

#endif /* CSTRING_SCORE_H_ */
