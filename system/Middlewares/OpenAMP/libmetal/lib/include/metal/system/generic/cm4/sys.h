/*
 * Copyright (c) 2015, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	generic/cm4/sys.h
 * @brief	generic cm4 system primitives for libmetal.
 */

#ifndef __METAL_GENERIC_SYS__H__
#error "Include metal/sys.h instead of metal/generic/cm4/sys.h"
#endif

#ifndef __METAL_GENERIC_CM4_SYS__H__
#define __METAL_GENERIC_CM4_SYS__H__

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MAX_IRQS)
#define MAX_IRQS	8          /**< maximum number of irqs */
#endif

static inline void sys_irq_enable(unsigned int vector)
{
	(void)vector;
}

static inline void sys_irq_disable(unsigned int vector)
{
	(void)vector;
}

#ifdef __cplusplus
}
#endif

#endif /* __METAL_GENERIC_CM4_SYS__H__ */
