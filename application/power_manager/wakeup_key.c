#include <FreeRTOS.h>
#include<FreeRTOSConfig.h>
#include <task.h>
#include <semphr.h>

#include "Arduino.h"
#include "pm_common.h"

#define WAKEUP_KEY_PIN		(90)
#define SHORT_PRESS		    (1000)
#define long_PRESS		    (5000)
#define OFFSET_PRESS        (3500)



int	deep_sleep = 0;
int	in_suspend = 0;
void resume_by_rtc(void)
{
	RTC_REGS->rtc_ontime_set = 0x1;
	RTC_REGS->rtc_ctrl = 0x2;  // rtc irq to pmc
	RTC_REGS->rtc_clock_set = 0x0; //
}
void wakeup_shortkey()
{
	printf("short key \n");
	deep_sleep = 0;
	CM4_TO_CA55_MAILBOX->direct_transation[7]=deep_sleep;
	if(in_suspend)
	{
		printf("resume by RTC \n");
		resume_by_rtc();
	}
}

void wakeup_longkey()
{
	printf("long key \n");
	deep_sleep = 1;
	CM4_TO_CA55_MAILBOX->direct_transation[7]=deep_sleep;
}

void vWakeyupKeyTask( void *pvParameters )
{
	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;
	TickType_t xoffsetTimeout = pdMS_TO_TICKS( OFFSET_PRESS );
	TickType_t xshortTimeout = pdMS_TO_TICKS( SHORT_PRESS );
	TickType_t xlongTimeout = pdMS_TO_TICKS( long_PRESS );

	TickType_t xfirsttime,xsencondtime;
	bool xPress = false;
	for( ;; )
	{
		if((RTC_REGS->rtc_wakeupkey_int_status == 1) && !xPress)
		{
			xPress = true;
			RTC_REGS->rtc_wakeupkey_int_status = 0;
			xfirsttime = xTaskGetTickCount();
		}
		if((RTC_REGS->rtc_wakeupkey_int_status == 1) && xPress)
		{
			xsencondtime = xTaskGetTickCount();
			RTC_REGS->rtc_wakeupkey_int_status = 0;
		}
		if(xPress && (xTaskGetTickCount() - xsencondtime) > pdMS_TO_TICKS(200))
		{
			if((xsencondtime-xfirsttime) > xshortTimeout &&  (xsencondtime-xfirsttime) < (xshortTimeout + xoffsetTimeout))
			{
				wakeup_shortkey();
			}
			if((xsencondtime-xfirsttime) > xlongTimeout &&  (xsencondtime-xfirsttime) < (xlongTimeout + xoffsetTimeout))
			{
				wakeup_longkey();
			}
			xPress = false;
			xfirsttime = 0;
			xsencondtime = 0;
			RTC_REGS->rtc_wakeupkey_int_status = 0;
		}
		vTaskDelay(pdMS_TO_TICKS(20));
	}
}

void wakeup_key_init(void)
{
	pinMode(WAKEUP_KEY_PIN, INPUT);
	xTaskCreate( vWakeyupKeyTask, "wakeupkey", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
}