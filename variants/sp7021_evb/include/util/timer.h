/********************************************************
 * Copyright (c) 2018 by Sunplus Technology Co., Ltd.
 *    ____               __
 *   / __/_ _____  ___  / /_ _____
 *  _\ \/ // / _ \/ _ \/ / // (_-<
 * /___/\_,_/_//_/ .__/_/\_,_/___/
 *              /_/
 * Sunplus Technology Co. 19, Innovation First Road,
 * Science-Based Industrial Park, Hsin-Chu, Taiwan, R.O.C.
 * ------------------------------------------------------
 *
 * Description :  simple cbdma driver
 * ------------------------------------------------------
 * Rev  Date          Author(s)      Status & Comments
 * ======================================================
 * 0.1  2018/06/28    nz.lu          initial version
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

// for test
void timer_test_init();
void timer_test();

void SP_start_timer2(void (*)(int));
void SP_start_timer3(void (*)(int));

#ifdef __cplusplus
}
#endif

#endif // __TIMER_H__
