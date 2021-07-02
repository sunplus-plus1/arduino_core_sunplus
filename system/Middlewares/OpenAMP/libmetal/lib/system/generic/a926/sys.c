/*
 * Copyright (c) 2016, Xilinx Inc. and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	generic/a926/sys.c
 * @brief	machine specific system primitives implementation.
 */


#include "metal/io.h"
#include "metal/sys.h"
#include <metal/irq_controller.h>
#include <metal/log.h>
#include <cache.h>
#include <irq_ctrl.h>

static void metal_a926_irq_set_enable(struct metal_irq_controller *irq_cntr,
				      int irq, unsigned int state)
{
	if (irq < irq_cntr->irq_base ||
	    irq >= irq_cntr->irq_base + irq_cntr->irq_num) {
		metal_log(METAL_LOG_ERROR, "%s: invalid irq %d\n",
			  __func__, irq);
		return;
	} else if (state == METAL_IRQ_ENABLE) {
		IRQ_Enable(irq);
	} else {
		IRQ_Disable(irq);
	}
}

static int metal_a926_irq_register(struct metal_irq_controller *irq_cntr,
					int irq, metal_irq_handler hd, void *arg)
{
	//TODO: FIXME
	printf(">>>>>> %s:%d @ %p\n", __FUNCTION__, irq, hd);
}

static METAL_IRQ_CONTROLLER_DECLARE(a926_irq_cntr,
				    0, 224,
				    NULL,
				    metal_a926_irq_set_enable,
					metal_a926_irq_register,
				    NULL)

int metal_a926_irq_init(void)
{
	int ret;

	ret =  metal_irq_register_controller(&a926_irq_cntr);
	if (ret < 0) {
		metal_log(METAL_LOG_ERROR, "%s: register irq controller failed.\n",
			  __func__);
		return ret;
	}
	return 0;
}

void sys_irq_restore_enable(unsigned int flags)
{
	(void)flags;
}

unsigned int sys_irq_save_disable(void)
{
  return 0;
}

void metal_machine_cache_flush(void *addr, unsigned int len)
{
	HAL_DCACHE_FLUSH(addr, len);
}

void metal_machine_cache_invalidate(void *addr, unsigned int len)
{
	HAL_DCACHE_INVALIDATE(addr, len);
}

/**
 * @brief poll function until some event happens
 */
void __attribute__((weak)) metal_generic_default_poll(void)
{
}

void *metal_machine_io_mem_map(void *va, metal_phys_addr_t pa,
			       size_t size, unsigned int flags)
{
	(void)size;
	(void)flags;

	return (va = (void *)pa);
}
