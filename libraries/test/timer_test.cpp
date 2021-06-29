#include "HardwareTimer.h"


#ifdef __cplusplus
extern "C" {
#endif
volatile  uint64_t start = 0;


void tim0_callback(void)
{
	
	//printf("@@@@@@@timer0 callback @@@@@@@, tick= %lu, %lu:%lu\n", HAL_GetTick()-start,HAL_GetTick(), start );
	printf("@@@@@@@timer0 callback @@@@@@@, tick= %lu\n", HAL_GetTick());
	start = HAL_GetTick();
	//printf("start:%lu\n", start);



}

void tim1_callback(void)
{
	printf("@@@@@@@timer1 callback @@@@@@@\n");

}


void loop(void)
{
	uint32_t u32Prescal = 0xFFFF;
 	HAL_Init();
 	HardwareTimer *timer0 = new HardwareTimer(TIM0);
	timer0->setPrescaleFactor(20200);
	//timer0->setPrescaleFactor(1000);
	u32Prescal = timer0->getPrescaleFactor();
	printf("u32Prescal= 0x%x\n", u32Prescal);
	printf("freq = %d\n", timer0->getTimerClkFreq());
	timer0->setCount(10000-1, TICK_FORMAT);
	timer0->setOverflow(10000-1, TICK_FORMAT);
	//timer0->setCount(999, TICK_FORMAT);
	printf("counter = %d\n", timer0->getCount(TICK_FORMAT));
#if 1
	timer0->attachInterrupt(tim0_callback);
	start = (uint32_t)HAL_GetTick();
	timer0->resume();
 	//HAL_lreg(12);
#else // openamp echo test
	extern int rpmsg_echo_main(int argc, char *argv[]);
	rpmsg_echo_main(0, NULL);
#endif
}







#ifdef __cplusplus
}
#endif

