/*******************************************************************************
 * Copyright (c) 2016 Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the MIT License
 *******************************************************************************
 *
 * Filename: span_var.h
 *
 * Description:
 *      Definition of span of variables
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2016-05-12   wm              Initial version
 *
 ******************************************************************************/


#ifndef SPAN_VAR_H_
#define SPAN_VAR_H_

#include "var_type.h"
#include "span.h"

#ifdef __cplusplus
extern "C"
{
#endif

DEFINE_SPAN(var_t);
DEFINE_SPAN_T(var_t);

#ifdef __cplusplus
}
#endif

#endif /* SPAN_VAR_H_ */
