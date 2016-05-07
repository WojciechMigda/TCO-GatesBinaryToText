/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: read_scored_tuples.h
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
 * 2016-05-08   wm              Initial version
 *
 ******************************************************************************/


#ifndef READ_SCORED_TUPLES_H_
#define READ_SCORED_TUPLES_H_

#include "span.h"

#ifdef __cplusplus
extern "C"
{
#endif


DEFINE_SPAN(void);

SPAN(void) read_scored_tuples(const char * fname);
int release_scored_tuples(SPAN(void) span);


#ifdef __cplusplus
}
#endif

#endif /* READ_SCORED_TUPLES_H_ */
