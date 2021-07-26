/* This is a sample demonstration application that showcases usage of virt_uart
This application is meant to run on the remote CPU running baremetal code.
This application echoes back data that was sent to it by the master core. */
#include "virt_uart.h"

int openamp_test_main(void)
{
	int ret;

	virt_uart_open();

	while (1) {
		static char s[256];
		ret = virt_uart_read(s, sizeof(s));
		if (ret > 0) {
			virt_uart_write(s, ret); // write back
		}
	}

	virt_uart_close();

	return ret;
}
