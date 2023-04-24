/*
 *	Test i2c on a temperature sensor(SHT3X).
 *	The transmission of Arduino layer(twi.c) is implemented as burst_irq transmit.
 *	if want to use other mode. Please select the mode in twi.h.
 *	e.x.
 *		//#define BURST_MODE
 *		#define IT_MODE
 *		//#define DMA_MODE
 *		//#define DMA_IT_MODE
 */

#include "Arduino.h"
#include "Wire.h"

#define SLAVE_ADDR 0x44

static uint8_t tx_buff[32];
static uint8_t rx_buff[32];

TwoWire *i2cm_test;

#ifndef SP7350
void setup()
{
	printf("i2c example %s\n", __TIME__);

	memset(&tx_buff, 0x0, 32);
	memset(&rx_buff, 0x0, 32);

	i2cm_test = new TwoWire(SP_I2CM3);
	i2cm_test->begin();
}

void loop()
{
	int i = 0;

	tx_buff[0] = 0x24;//24
	tx_buff[1] = 0x00;//00

	i2cm_test->beginTransmission(SLAVE_ADDR);
	i2cm_test->write(tx_buff, 2);

	uint8_t ret = i2cm_test->endTransmission();
	if (ret) {
		printf("Transmit error code %d\n", ret);
	}

	i2cm_test->requestFrom(SLAVE_ADDR, 6);

	while(i2cm_test->available())
	{
		rx_buff[i] = i2cm_test->read();
		i++;
	}

	int temp = (rx_buff[0] << 8) | rx_buff[1];
	temp = temp * 17500 / 65536;
	int temp_L = temp % 100;
	int temp_H = temp / 100 - 45;

	int RH = (rx_buff[3] << 8) | rx_buff[4];
	RH = RH * 10000 / 65536;
	int RH_L = RH % 100;
	int RH_H = RH / 100;

	printf("\n temp=%d.%d   %d.%d    \n", temp_H, temp_L, RH_H, RH_L);

	delay(2000);
}
#else
#define SLAVE_ADDR_ZEBU		0x02

void setup()
{
	printf("i2c example %s\n", __TIME__);
#if 0
	HAL_I2C_SLAVE_TEST();
#else
	uint32_t i;
	uint8_t ret;

	memset(&tx_buff, 0x55, 32);
	memset(&rx_buff, 0x0, 32);

	i2cm_test = new TwoWire(SP_I2CM0);
	i2cm_test->begin();//init the hardware

	tx_buff[0] = 0x11;
	tx_buff[1] = 0x22;

	/* Init buffer(Wire.cpp) point and save slave address */
	i2cm_test->beginTransmission(SLAVE_ADDR_ZEBU);

	/* Put the data in buffer(Wire.cpp) */
	i2cm_test->write(tx_buff, 4);

	/* Hardware run, write */
	ret = i2cm_test->endTransmission();
	if (ret)
		printf("Transmit error code %d\n", ret);

	/* Hardware run, read */
	i2cm_test->requestFrom(SLAVE_ADDR_ZEBU, 1);

	/* Check if there is data in buffer(Wire.cpp) */
	while(i2cm_test->available()) {

		/* get the data from buffer(Wire.cpp) */
		rx_buff[i++] = i2cm_test->read();
	}

	if(rx_buff[0] == 0x82) {
		tx_buff[0] = 0x33;
		tx_buff[1] = 0x44;
		i2cm_test->beginTransmission(SLAVE_ADDR_ZEBU);
		i2cm_test->write(tx_buff, 4);
		ret = i2cm_test->endTransmission();
		if (ret)
			printf("Transmit error code %d\n", ret);
	}
#endif
}

void loop()
{

}
#endif
