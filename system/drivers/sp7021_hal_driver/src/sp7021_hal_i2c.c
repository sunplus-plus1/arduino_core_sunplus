#include "sp7021_hal_i2c.h"

static void i2c_interrupt_control_mask(int i2c_no, int enable);
static HAL_StatusTypeDef i2c_timeout(I2C_HandleTypeDef * hi2c, uint32_t Timeout,
				     uint32_t Tickstart);

static void _i2c_status_clear(I2C_HandleTypeDef * hi2c, uint32_t flag);
static void _i2c_dma_int_flag_clear(I2C_HandleTypeDef * hi2c, uint32_t flag);
static void _i2c_reset(I2C_HandleTypeDef * hi2c);
static void _i2c_data0_set(I2C_HandleTypeDef * hi2c, uint32_t * wdata);
static void _i2c_int_en0_disable(I2C_HandleTypeDef * hi2c, uint32_t int0);
static void _i2c_rdata_flag_get(I2C_HandleTypeDef * hi2c, uint32_t * flag);
static void _i2c_data_get(I2C_HandleTypeDef * hi2c, int index, uint32_t * rdata);
static void _i2c_rdata_flag_clear(I2C_HandleTypeDef * hi2c, uint32_t flag);
static void _i2c_clock_freq_set(I2C_HandleTypeDef * hi2c, uint32_t freq);
static void _i2c_slave_addr_set(I2C_HandleTypeDef * hi2c, uint16_t slave_addr);
static void _i2c_scl_delay_set(I2C_HandleTypeDef * hi2c, uint32_t delay);
static void _i2c_trans_cnt_set(I2C_HandleTypeDef * hi2c, uint16_t write_cnt, uint16_t read_cnt);
static void _i2c_active_mode_set(I2C_HandleTypeDef * hi2c, I2C_Active_Mode_e mode);
static void _i2c_data_set(I2C_HandleTypeDef * hi2c, uint32_t * wdata);
static void _i2c_rw_mode_set(I2C_HandleTypeDef * hi2c, I2C_RW_Mode_e rw_mode);
static void _i2c_int_en0_set(I2C_HandleTypeDef * hi2c, uint32_t int0);
static void _i2c_int_en1_set(I2C_HandleTypeDef * hi2c, uint32_t int1);
static void _i2c_int_en2_set(I2C_HandleTypeDef * hi2c, uint32_t int2);
static void _i2c_enable(I2C_HandleTypeDef * hi2c);
static void _i2c_manual_trigger(I2C_HandleTypeDef * hi2c);
static void _i2c_int_en0_with_thershold_set(I2C_HandleTypeDef * hi2c,
					    uint32_t int0, uint8_t threshold);
static void _i2c_dma_mode_enable(I2C_HandleTypeDef * hi2c);
static void _i2c_dma_addr_set(I2C_HandleTypeDef * hi2c, uint32_t addr);
static void _i2c_dma_length_set(I2C_HandleTypeDef * hi2c, uint32_t len);
static void _i2c_dma_rw_mode_set(I2C_HandleTypeDef * hi2c, I2C_DMA_RW_Mode_e mode);
static void _i2c_dma_int_en_set(I2C_HandleTypeDef * hi2c, uint32_t int0);
static void _i2c_dma_go_set(I2C_HandleTypeDef * hi2c);

static void i2c_reset(I2C_HandleTypeDef * hi2c)
{
	_i2c_reset(hi2c);	// reset

	_i2c_int_en0_set(hi2c, 0);
	_i2c_int_en1_set(hi2c, 0);
	_i2c_int_en2_set(hi2c, 0);

	_i2c_dma_int_en_set(hi2c, 0);
}

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef * hi2c)
{
	if (hi2c == NULL) {
		return HAL_ERROR;
	}

	hi2c->ErrorCode = HAL_I2C_ERR_NONE;

	i2c_reset(hi2c);
	hi2c->State = HAL_I2C_STATE_READY;
	return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef * hi2c)
{
	if (hi2c == NULL) {
		return HAL_ERROR;
	}
	i2c_reset(hi2c);
	return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef * hi2c,
					  uint16_t DevAddress, uint8_t * pData,
					  uint32_t Size, uint32_t Timeout)
{
	uint32_t i, j;
	uint32_t int0 = 0;
	uint8_t w_data[32] = { 0 };
	uint32_t tickstart = 0;

	if (hi2c->State != HAL_I2C_STATE_READY)
		return HAL_BUSY;

	__HAL_LOCK(hi2c);
	_i2c_reset(hi2c);	// reset

	hi2c->State = HAL_I2C_STATE_BUSY_TX;
	hi2c->pBuffPtr = pData;
	hi2c->XferCount = 0;
	hi2c->BurstCount = 0;

	/* WRCOUNT 15:0 */
	if (Size > 0xFFFF) {
		printf("I2C write count is invalid !! Size=%d\n", Size);
		return HAL_ERROR;
	}
	/*
	 * handle first 32 byte data and the remaining bytes
	 * every 4 bytes count as a burst, calculate the hi2c->BurstCount.
	 */
	if (Size > I2C_DATA_REG_TOTAL_SIZE) {
		hi2c->BurstCount = (Size - I2C_DATA_REG_TOTAL_SIZE) / 4;
		if ((Size - I2C_DATA_REG_TOTAL_SIZE) % 4) {
			hi2c->BurstCount += 1;
		}

		for (i = 0; i < 32; i++) {
			w_data[i] = hi2c->pBuffPtr[i];
		}
	} else {
		for (i = 0; i < Size; i++) {
			w_data[i] = hi2c->pBuffPtr[i];
		}
	}
	hi2c->XferCount = i;

	int0 =
	    (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
	     I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	if (hi2c->BurstCount)
		int0 |= I2C_EN0_EMPTY_THRESHOLD_INT;

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);
	_i2c_slave_addr_set(hi2c, DevAddress);

	_i2c_trans_cnt_set(hi2c, Size, 0);
	_i2c_active_mode_set(hi2c, I2C_TRIGGER);
	_i2c_rw_mode_set(hi2c, I2C_WRITE_MODE);
	/* Store first 32 byte to i2c sram. */
	_i2c_data_set(hi2c, (uint32_t *) w_data);
	_i2c_int_en0_set(hi2c, int0);
	/* Burst write use */
	_i2c_int_en0_with_thershold_set(hi2c, int0, I2C_EMPTY_THRESHOLD_VALUE);
	_i2c_manual_trigger(hi2c);

	tickstart = HAL_GetTick();
	/* INT_DONE = 0 */
	while (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == RESET) {
		if (i2c_timeout(hi2c, Timeout, tickstart) != HAL_OK) {
			printf("Timeout!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_TIMEOUT;
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_ADDRESS_NACK_FLAG)
		    == SET) {
			printf("I2C slave address NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_ADDRESS_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DATA_NACK_FLAG)
			   == SET) {
			printf("read I2C slave data NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_RECEIVE_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_SCL_HOLD_TOO_LONG_FLAG) == SET) {
			printf("I2C SCL hold too long occur !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_SCL_HOLD_TOO_LONG;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		}

		if (__HAL_I2C_GET_FLAG
		    (hi2c, I2C_INT_EMPTY_THRESHOLD_FLAG) == SET && (hi2c->BurstCount > 0)) {
			for (i = 0; i < I2C_EMPTY_THRESHOLD_VALUE; i++) {
				for (j = 0; j < 4; j++) {
					/* write_cnt <= 32, DataIndex = DataTotalLen = write_cnt */
					if (hi2c->XferCount >= Size) {
						w_data[j] = 0;
					} else {
						w_data[j] = hi2c->pBuffPtr[hi2c->XferCount];
					}
					hi2c->XferCount++;
				}
				/* unsigned char *->unsigned int *, 4 bytes, so using data00_03 is enough */
				_i2c_data0_set(hi2c, (uint32_t *) w_data);
				hi2c->BurstCount--;

				if (hi2c->BurstCount == 0) {
					_i2c_int_en0_disable(hi2c, (I2C_EN0_EMPTY_THRESHOLD_INT |
								    I2C_EN0_EMPTY_INT));
					break;
				}
			}
			_i2c_status_clear(hi2c, I2C_CTL1_EMPTY_THRESHOLD_CLR);
		}
	}
	/* Reset */
	_i2c_reset(hi2c);
	hi2c->State = HAL_I2C_STATE_READY;

	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef * hi2c,
					 uint16_t DevAddress, uint8_t * pData,
					 uint32_t Size, uint32_t Timeout)
{
	uint32_t i, j, loop;
	uint32_t status3, bit_index;
	uint32_t int0 = 0, int1 = 0, int2 = 0;
	uint32_t tickstart = 0;

	if (hi2c->State != HAL_I2C_STATE_READY)
		return HAL_BUSY;

	/* Process Locked */
	__HAL_LOCK(hi2c);
	_i2c_reset(hi2c);	// reset

	hi2c->State = HAL_I2C_STATE_BUSY_RX;
	hi2c->pBuffPtr = pData;
	hi2c->XferSize = Size;
	hi2c->XferCount = 0;
	hi2c->RegDataIndex = 0;
	hi2c->BurstCount = Size / I2C_BURST_RDATA_BYTES;
	hi2c->BurstRemainder = Size % I2C_BURST_RDATA_BYTES;

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
		I2C_EN0_DATA_NACK_INT |I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);
	int1 = I2C_BURST_RDATA_FLAG;
	int2 = I2C_BURST_RDATA_ALL_FLAG;

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);
	/* set slave address */
	_i2c_slave_addr_set(hi2c, DevAddress);

	/* set write/read count */
	_i2c_trans_cnt_set(hi2c, 0, Size);
	/* Trigger mode */
	_i2c_active_mode_set(hi2c, I2C_TRIGGER);
	/* set read mode */
	_i2c_rw_mode_set(hi2c, I2C_READ_MODE);

	_i2c_int_en0_set(hi2c, int0);
	_i2c_int_en1_set(hi2c, int1);
	_i2c_int_en2_set(hi2c, int2);

	/* start Trigger */
	_i2c_manual_trigger(hi2c);

	tickstart = HAL_GetTick();
	while (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == RESET) {
		if (i2c_timeout(hi2c, Timeout, tickstart) != HAL_OK) {
			printf("Timeout!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_TIMEOUT;
			return HAL_ERROR;
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_ADDRESS_NACK_FLAG) == SET) {
			printf("I2C slave address NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_ADDRESS_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DATA_NACK_FLAG) == SET) {
			printf("read I2C slave data NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_RECEIVE_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_SCL_HOLD_TOO_LONG_FLAG) == SET) {
			printf("I2C SCL hold too long occur !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_SCL_HOLD_TOO_LONG;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		}

		if (hi2c->BurstCount == 0)
			continue;

		/* Get the bytes postion in data register */
		_i2c_rdata_flag_get(hi2c, (uint32_t *)&status3);
		for (i = 0; i < (I2C_DATA_REG_TOTAL_SIZE / I2C_BURST_RDATA_BYTES); i++) {
			bit_index = (I2C_BURST_RDATA_BYTES - 1) + (I2C_BURST_RDATA_BYTES * i);
			if (status3 & (1 << bit_index)) {
				for (j = 0; j < (I2C_BURST_RDATA_BYTES / I2C_DATA_REG_SIZE); j++) {
					_i2c_data_get(hi2c, hi2c->RegDataIndex,
						      (uint32_t *)(&hi2c->pBuffPtr[hi2c->XferCount]));
					hi2c->RegDataIndex = (hi2c->RegDataIndex + 1) % I2C_DATA_REG_NUMS;
					hi2c->XferCount += 4;
				}
				_i2c_rdata_flag_clear(hi2c, (((1 << I2C_BURST_RDATA_BYTES) - 1) << (I2C_BURST_RDATA_BYTES * i)));
				hi2c->BurstCount--;
			}
		}
	}

	if ((hi2c->State == HAL_I2C_STATE_BUSY_RX) && (hi2c->BurstRemainder) &&
	    (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == SET)) {
		loop = hi2c->BurstRemainder / I2C_DATA_REG_SIZE;
		if (hi2c->BurstRemainder % I2C_DATA_REG_SIZE)
			loop ++;

		for (j = 0; j < loop; j++) {
			_i2c_data_get(hi2c, hi2c->RegDataIndex,
				      (uint32_t *)(&hi2c->pBuffPtr[hi2c->XferCount]));
			hi2c->RegDataIndex = (hi2c->RegDataIndex + 1) % I2C_DATA_REG_NUMS;
			/* Dont care the last XferCount. Not use. */
			hi2c->XferCount += I2C_DATA_REG_SIZE;
		}
	}
	/* reset */
	_i2c_reset(hi2c);
	hi2c->State = HAL_I2C_STATE_READY;

	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef * hi2c,
					      uint16_t DevAddress, uint8_t * pData, uint32_t Size)
{
	uint32_t int0 = 0;

	if ((hi2c->State != HAL_I2C_STATE_READY) ||
	    (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_BUSY_FLAG) == SET)) {
		return HAL_BUSY;
	}

	/* Process Locked */
	__HAL_LOCK(hi2c);

	hi2c->State = HAL_I2C_STATE_BUSY_DMA_TX;
	hi2c->pBuffPtr = pData;
	hi2c->XferCount = 0;

	_i2c_reset(hi2c);

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
		I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	_i2c_dma_mode_enable(hi2c);

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);
	/* set slave address */
	_i2c_slave_addr_set(hi2c, DevAddress);
	/* Auto mode */
	_i2c_active_mode_set(hi2c, I2C_AUTO);
	/* set write mode */
	_i2c_rw_mode_set(hi2c, I2C_WRITE_MODE);

	_i2c_int_en0_set(hi2c, int0);
	/* cache data map to dram */
	HAL_DCACHE_FLUSH(hi2c->pBuffPtr, Size);

	if (Size < 4)
		_i2c_dma_length_set(hi2c, 4);
	else
		_i2c_dma_length_set(hi2c, Size);

	_i2c_dma_addr_set(hi2c, (uint32_t) hi2c->pBuffPtr);
	_i2c_dma_rw_mode_set(hi2c, I2C_DMA_READ_MODE);
	_i2c_dma_int_en_set(hi2c, I2C_DMA_EN_DMA_DONE_INT);
	_i2c_dma_go_set(hi2c);

	while ((__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == RESET)
	       && (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_DMA_DONE_FLAG)
		   == RESET)) {
		if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_WCNT_ERROR_FLAG) == SET) {
			printf("I2C DMA WCNT ERR !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_WB_EN_ERROR_FLAG) == SET) {
			printf("I2C DMA WB EN ERR !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_GDMA_TIMEOUT_FLAG) == SET) {
			printf("I2C DMA timeout !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_IP_TIMEOUT_FLAG) == SET) {
			printf("I2C IP timeout !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_THRESHOLD_FLAG) == SET) {
			printf("I2C Length is zero !!\n");
			break;
		}
	}

	while ((hi2c->Instance->control5 & I2C_CTL5_SIFBUSY) == I2C_CTL5_SIFBUSY) {
		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_ADDRESS_NACK_FLAG)
		    == SET) {
			printf("I2C slave address NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_ADDRESS_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DATA_NACK_FLAG)
			   == SET) {
			printf("I2C slave data NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_RECEIVE_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_SCL_HOLD_TOO_LONG_FLAG) == SET) {
			printf("I2C SCL hold too long occur !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_SCL_HOLD_TOO_LONG;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		}

	}

	_i2c_reset(hi2c);	// reset
	hi2c->State = HAL_I2C_STATE_READY;

	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with DMA
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef * hi2c,
					     uint16_t DevAddress, uint8_t * pData, uint32_t Size)
{
	uint32_t int0 = 0, int1 = 0, int2 = 0;

	if ((hi2c->State != HAL_I2C_STATE_READY) ||
	    (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_BUSY_FLAG) == SET)) {
		return HAL_BUSY;
	}

	/* Process Locked */
	__HAL_LOCK(hi2c);

	_i2c_reset(hi2c);	// reset

	hi2c->State = HAL_I2C_STATE_BUSY_DMA_RX;
	hi2c->pBuffPtr = pData;

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
	     	I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	int1 = I2C_BURST_RDATA_FLAG;
	int2 = I2C_BURST_RDATA_ALL_FLAG;

	_i2c_dma_mode_enable(hi2c);	// enable DMA

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);	// 27M/270 =  100k hz

	_i2c_scl_delay_set(hi2c, 0x01);

	_i2c_slave_addr_set(hi2c, DevAddress);	// set slave address

	_i2c_active_mode_set(hi2c, I2C_AUTO);	//set AUTO mode

	_i2c_rw_mode_set(hi2c, I2C_READ_MODE);	// set read mode

	_i2c_int_en0_set(hi2c, int0);
	_i2c_int_en1_set(hi2c, int1);
	_i2c_int_en2_set(hi2c, int2);

	HAL_DCACHE_INVALIDATE(hi2c->pBuffPtr, Size);	// cache data map to dram

	if (Size < 4)
		_i2c_dma_length_set(hi2c, 4);
	else
		_i2c_dma_length_set(hi2c, Size);

	_i2c_dma_addr_set(hi2c, (uint32_t) hi2c->pBuffPtr);
	_i2c_dma_rw_mode_set(hi2c, I2C_DMA_WRITE_MODE);
	_i2c_dma_int_en_set(hi2c, I2C_DMA_EN_DMA_DONE_INT);
	_i2c_dma_go_set(hi2c);

	while ((hi2c->Instance->control5 & I2C_CTL5_SIFBUSY) == I2C_CTL5_SIFBUSY) {
		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_ADDRESS_NACK_FLAG) == SET) {
			printf("I2C slave address NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_ADDRESS_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DATA_NACK_FLAG) == SET) {
			printf("I2C slave data NACK !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_RECEIVE_NACK;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_SCL_HOLD_TOO_LONG_FLAG) == SET) {
			printf("I2C SCL hold too long occur !!\n");
			hi2c->ErrorCode |= HAL_I2C_ERR_SCL_HOLD_TOO_LONG;
			i2c_reset(hi2c);
			hi2c->State = HAL_I2C_STATE_READY;
			break;
		}

	}

	while ((__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == RESET)
	       && (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_DMA_DONE_FLAG) == RESET)) {
		if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_WCNT_ERROR_FLAG) == SET) {
			printf("I2C DMA WCNT ERR !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_WB_EN_ERROR_FLAG) == SET) {
			printf("I2C DMA WB EN ERR !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_GDMA_TIMEOUT_FLAG) == SET) {
			printf("I2C DMA timeout !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_IP_TIMEOUT_FLAG) == SET) {
			printf("I2C IP timeout !!\n");
			break;
		} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_THRESHOLD_FLAG) == SET) {
			printf("I2C Length is zero !!\n");
			break;
		}
	}

	_i2c_reset(hi2c);	// reset
	hi2c->State = HAL_I2C_STATE_READY;

	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef * hi2c,
					     uint16_t DevAddress, uint8_t * pData, uint32_t Size)
{
	uint32_t i;
	uint32_t int0 = 0;
	uint8_t w_data[32] = { 0 };

	if (hi2c->State != HAL_I2C_STATE_READY)
		return HAL_BUSY;

	i2c_interrupt_control_mask(hi2c->Index, 0);

	__HAL_LOCK(hi2c);
	_i2c_reset(hi2c);

	hi2c->State = HAL_I2C_STATE_BUSY_TX;
	hi2c->pBuffPtr = pData;
	hi2c->XferCount = 0;
	hi2c->BurstCount = 0;

	if (Size > 0xFFFF) {
		printf("I2C write count is invalid !! Size=%d\n", Size);
		return HAL_ERROR;
	}

	if (Size > I2C_DATA_REG_TOTAL_SIZE) {
		hi2c->BurstCount = (Size - I2C_DATA_REG_TOTAL_SIZE) / 4;
		if ((Size - I2C_DATA_REG_TOTAL_SIZE) % 4) {
			hi2c->BurstCount += 1;
		}

		for (i = 0; i < 32; i++) {
			w_data[i] = hi2c->pBuffPtr[i];
		}
	} else {
		for (i = 0; i < Size; i++) {
			w_data[i] = hi2c->pBuffPtr[i];
		}
	}
	hi2c->XferCount = i;

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
	     	I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	if (hi2c->BurstCount)
		int0 |= I2C_EN0_EMPTY_THRESHOLD_INT;

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);
	_i2c_slave_addr_set(hi2c, DevAddress);

	/* set write/read count */
	_i2c_trans_cnt_set(hi2c, Size, 0);
	/* Trigger mode */
	_i2c_active_mode_set(hi2c, I2C_TRIGGER);
	/* set read mode */
	_i2c_rw_mode_set(hi2c, I2C_WRITE_MODE);
	_i2c_data_set(hi2c, (uint32_t *) w_data);

	/* start Trigger */
	_i2c_manual_trigger(hi2c);

	_i2c_int_en0_set(hi2c, int0 | I2C_EN0_CTL_EMPTY_THRESHOLD(I2C_EMPTY_THRESHOLD_VALUE));

	i2c_interrupt_control_mask(hi2c->Index, 1);

	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with Interrupt
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef * hi2c,
					    uint16_t DevAddress, uint8_t * pData, uint32_t Size)
{
	unsigned int int0 = 0, int1 = 0, int2 = 0;

	if (hi2c->State != HAL_I2C_STATE_READY)
		return HAL_BUSY;

	i2c_interrupt_control_mask(hi2c->Index, 0);

	__HAL_LOCK(hi2c);

	hi2c->State = HAL_I2C_STATE_BUSY_RX;
	hi2c->pBuffPtr = pData;
	hi2c->XferSize = Size;
	hi2c->XferCount = 0;
	hi2c->RegDataIndex = 0;
	hi2c->BurstCount = Size / I2C_BURST_RDATA_BYTES;
	hi2c->BurstRemainder = Size % I2C_BURST_RDATA_BYTES;

	_i2c_reset(hi2c);	// reset

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
		I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	int1 = I2C_BURST_RDATA_FLAG;
	int2 = I2C_BURST_RDATA_ALL_FLAG;

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);
	/* set slave address */
	_i2c_slave_addr_set(hi2c, DevAddress);

	/* set write/read count */
	_i2c_trans_cnt_set(hi2c, 0, Size);
	/* Trigger mode */
	_i2c_active_mode_set(hi2c, I2C_TRIGGER);
	/* set read mode */
	_i2c_rw_mode_set(hi2c, I2C_READ_MODE);

	_i2c_manual_trigger(hi2c);

	_i2c_int_en0_set(hi2c, int0);
	/* Generate the interrupt when receive the specific size of data */
	_i2c_int_en1_set(hi2c, int1);
	_i2c_int_en2_set(hi2c, int2);

	i2c_interrupt_control_mask(hi2c->Index, 1);

	__HAL_UNLOCK(hi2c);
	return HAL_OK;

}

/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA_IT(I2C_HandleTypeDef * hi2c,
						 uint16_t DevAddress,
						 uint8_t * pData, uint16_t Size)
{
	uint32_t int0 = 0;

	if (hi2c->State != HAL_I2C_STATE_READY)
		return HAL_BUSY;

	i2c_interrupt_control_mask(hi2c->Index, 0);

	__HAL_LOCK(hi2c);

	hi2c->State = HAL_I2C_STATE_BUSY_DMA_TX;
	hi2c->pBuffPtr = pData;
	hi2c->XferCount = 0;

	_i2c_reset(hi2c);	// reset

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
	     	I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	_i2c_dma_mode_enable(hi2c);	// enable DMA

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);	// 27M/270 =  100k hz
	_i2c_slave_addr_set(hi2c, DevAddress);	// set slave address

	_i2c_active_mode_set(hi2c, I2C_AUTO);	// Auto mode
	_i2c_rw_mode_set(hi2c, I2C_WRITE_MODE);	// i2c write mode
	_i2c_int_en0_set(hi2c, int0);

	HAL_DCACHE_FLUSH(hi2c->pBuffPtr, Size);	// cache data map to dram

	if (Size < 4)
		_i2c_dma_length_set(hi2c, 4);
	else
		_i2c_dma_length_set(hi2c, Size);

	_i2c_dma_addr_set(hi2c, (uint32_t)hi2c->pBuffPtr);
	_i2c_dma_rw_mode_set(hi2c, I2C_DMA_READ_MODE);
	_i2c_dma_int_en_set(hi2c, I2C_DMA_EN_DMA_DONE_INT);
	_i2c_dma_go_set(hi2c);

	i2c_interrupt_control_mask(hi2c->Index, 1);
	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with DMA
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA_IT(I2C_HandleTypeDef * hi2c,
						uint16_t DevAddress, uint8_t * pData, uint16_t Size)
{
	uint32_t int0 = 0, int1 = 0, int2 = 0;

	if (hi2c->State != HAL_I2C_STATE_READY)
		return HAL_BUSY;

	i2c_interrupt_control_mask(hi2c->Index, 0);

	__HAL_LOCK(hi2c);

	hi2c->State = HAL_I2C_STATE_BUSY_DMA_RX;
	hi2c->pBuffPtr = pData;
	hi2c->XferCount = 0;

	_i2c_reset(hi2c);	// reset

	int0 = (I2C_EN0_SCL_HOLD_TOO_LONG_INT | I2C_EN0_EMPTY_INT |
	     	I2C_EN0_DATA_NACK_INT | I2C_EN0_ADDRESS_NACK_INT | I2C_EN0_DONE_INT);

	int1 = I2C_BURST_RDATA_FLAG;
	int2 = I2C_BURST_RDATA_ALL_FLAG;

	_i2c_dma_mode_enable(hi2c);	// enable DMA

	_i2c_clock_freq_set(hi2c, hi2c->Init.Timing);	// 25M/250 =  100k hz
	_i2c_scl_delay_set(hi2c, 0x01);
	_i2c_slave_addr_set(hi2c, DevAddress);	// set slave address
	_i2c_active_mode_set(hi2c, I2C_AUTO);	// set AUTO mode
	_i2c_rw_mode_set(hi2c, I2C_READ_MODE);	// set read mode

	_i2c_int_en0_set(hi2c, int0);
	_i2c_int_en1_set(hi2c, int1);
	_i2c_int_en2_set(hi2c, int2);

	if (Size < 4)
		_i2c_dma_length_set(hi2c, 4);
	else
		_i2c_dma_length_set(hi2c, Size);

	HAL_DCACHE_INVALIDATE(hi2c->pBuffPtr, Size);	// cache data map to dram

	_i2c_dma_addr_set(hi2c, (uint32_t) hi2c->pBuffPtr);
	_i2c_dma_rw_mode_set(hi2c, I2C_DMA_WRITE_MODE);
	_i2c_dma_int_en_set(hi2c, I2C_DMA_EN_DMA_DONE_INT);
	_i2c_dma_go_set(hi2c);

	i2c_interrupt_control_mask(hi2c->Index, 1);

	__HAL_UNLOCK(hi2c);
	return HAL_OK;
}

HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef * hi2c)
{
	/* Return I2C handle state */
	return hi2c->State;
}

uint32_t HAL_I2C_GetError(I2C_HandleTypeDef * hi2c)
{
	return hi2c->ErrorCode;
}

void HAL_I2C_ClearError(I2C_HandleTypeDef * hi2c)
{
	hi2c->ErrorCode = HAL_I2C_ERR_NONE;
}

static HAL_StatusTypeDef i2c_timeout(I2C_HandleTypeDef * hi2c, uint32_t Timeout, uint32_t Tickstart)
{

	if (((HAL_GetTick() - Tickstart) > Timeout) && (Timeout != 0U)) {
		hi2c->State = HAL_I2C_STATE_READY;
		/* Process Unlocked */
		__HAL_UNLOCK(hi2c);

		return HAL_ERROR;
	}

	return HAL_OK;
}

/* private function */
static void i2c_interrupt_control_mask(int i2c_no, int enable)
{

	switch (i2c_no) {
	case 0:
		if (enable != 0) {
			/* enable timer0 interrupt */
			IRQ_Enable(I2C_MASTER0_IRQ);
		} else {
			IRQ_Disable(I2C_MASTER0_IRQ);
		}
		break;
	case 1:
		if (enable != 0) {
			/* enable timer0 interrupt */
			IRQ_Enable(I2C_MASTER1_IRQ);
		} else {
			IRQ_Disable(I2C_MASTER1_IRQ);
		}
		break;
	case 2:
		if (enable != 0) {
			/* enable timer0 interrupt */
			IRQ_Enable(I2C_MASTER2_IRQ);
		} else {
			IRQ_Disable(I2C_MASTER2_IRQ);
		}
		break;
	case 3:
		if (enable != 0) {
			/* enable timer0 interrupt */
			IRQ_Enable(I2C_MASTER3_IRQ);
		} else {
			IRQ_Disable(I2C_MASTER3_IRQ);
		}
	}
}

__STATIC_INLINE void _i2c_status_clear(I2C_HandleTypeDef * hi2c, uint32_t flag)
{
	hi2c->Instance->control1 |= flag;
	hi2c->Instance->control1 &= (~flag);
}

__STATIC_INLINE void _i2c_dma_int_flag_clear(I2C_HandleTypeDef * hi2c, uint32_t flag)
{
	hi2c->gdma->int_flag |= flag;
}

__STATIC_INLINE void _i2c_reset(I2C_HandleTypeDef * hi2c)
{
	hi2c->Instance->control0 |= I2C_CTL0_SW_RESET;
}

__STATIC_INLINE void _i2c_data0_set(I2C_HandleTypeDef * hi2c, uint32_t * wdata)
{
	hi2c->Instance->data00_03 = *wdata;
}

__STATIC_INLINE void _i2c_int_en0_disable(I2C_HandleTypeDef * hi2c, uint32_t int0)
{
	hi2c->Instance->int_en0 &= ~(int0);
}

__STATIC_INLINE void _i2c_rdata_flag_get(I2C_HandleTypeDef * hi2c, uint32_t * flag)
{
	*flag = hi2c->Instance->i2cm_status3;
}

static void _i2c_data_get(I2C_HandleTypeDef * hi2c, int index, uint32_t * rdata)
{
	switch (index) {
	case 0:
		*rdata = hi2c->Instance->data00_03;
		break;

	case 1:
		*rdata = hi2c->Instance->data04_07;
		break;

	case 2:
		*rdata = hi2c->Instance->data08_11;
		break;

	case 3:
		*rdata = hi2c->Instance->data12_15;
		break;

	case 4:
		*rdata = hi2c->Instance->data16_19;
		break;

	case 5:
		*rdata = hi2c->Instance->data20_23;
		break;

	case 6:
		*rdata = hi2c->Instance->data24_27;
		break;

	case 7:
		*rdata = hi2c->Instance->data28_31;
		break;

	default:
		break;
	}
}

__STATIC_INLINE void _i2c_rdata_flag_clear(I2C_HandleTypeDef * hi2c, uint32_t flag)
{
	hi2c->Instance->control6 = flag;
	hi2c->Instance->control6 = 0;
}

static void _i2c_clock_freq_set(I2C_HandleTypeDef * hi2c, uint32_t freq)
{
	uint32_t div;

	div = I2C_CLK_SOURCE_FREQ / freq;
	div -= 1;
	if (0 != I2C_CLK_SOURCE_FREQ % freq) {
		div += 1;
	}

	if (div > I2C_CTL2_FREQ_CUSTOM_MASK) {
		div = I2C_CTL2_FREQ_CUSTOM_MASK;
	}

	/* G140.0 bit[26:24] set 0x0:custom */
	hi2c->Instance->control0 &= ~(I2C_CTL0_FREQ(I2C_CTL0_FREQ_MASK));

	hi2c->Instance->control2 &= ~(I2C_CTL2_FREQ_CUSTOM(I2C_CTL2_FREQ_CUSTOM_MASK));
	hi2c->Instance->control2 |= I2C_CTL2_FREQ_CUSTOM(div);

}

__STATIC_INLINE void _i2c_slave_addr_set(I2C_HandleTypeDef * hi2c, uint16_t slave_addr)
{
	uint16_t temp_addr = slave_addr & I2C_CTL0_SLAVE_ADDR_MASK;

	/* clear previous slave addr */
	hi2c->Instance->control0 &= ~(I2C_CTL0_SLAVE_ADDR(I2C_CTL0_SLAVE_ADDR_MASK));
	hi2c->Instance->control0 |= I2C_CTL0_SLAVE_ADDR(temp_addr);
}

__STATIC_INLINE void _i2c_scl_delay_set(I2C_HandleTypeDef * hi2c, uint32_t delay)
{
	hi2c->Instance->control2 &= ~(I2C_CTL2_SCL_DELAY(I2C_CTL2_SCL_DELAY_MASK));
	hi2c->Instance->control2 |= I2C_CTL2_SCL_DELAY(delay);

	hi2c->Instance->control2 &= ~(I2C_CTL2_SDA_HALF_ENABLE);
}

/* decide how many byte to write/read */
__STATIC_INLINE void _i2c_trans_cnt_set(I2C_HandleTypeDef * hi2c,
					uint16_t write_cnt, uint16_t read_cnt)
{
	uint32_t t_write = write_cnt & I2C_CTL7_RW_COUNT_MASK;
	uint32_t t_read = read_cnt & I2C_CTL7_RW_COUNT_MASK;

	hi2c->Instance->control7 = I2C_CTL7_WRCOUNT(t_write) | I2C_CTL7_RDCOUNT(t_read);
}

static void _i2c_active_mode_set(I2C_HandleTypeDef * hi2c, I2C_Active_Mode_e mode)
{
	hi2c->Instance->i2cm_mode &= ~(I2C_MODE_MANUAL_MODE | I2C_MODE_MANUAL_TRIG);
	switch (mode) {
	default:
	case I2C_TRIGGER:
		break;

	case I2C_AUTO:
		hi2c->Instance->i2cm_mode |= I2C_MODE_MANUAL_MODE;
		break;
	}
}

static void _i2c_data_set_modify(I2C_HandleTypeDef * hi2c, unsigned char *wdata, unsigned int size)
{
	unsigned int i, j;
	unsigned int index = (size - 1) / 4;
	unsigned int cnt = size / 4;	// size 2,cnt 0
	unsigned int remain = size % 4;	//remain 2
	unsigned int reg_val[8] = { 0 };

	if (cnt > 0) {
		for (i = 0; i < cnt; i++) {
			for (j = 0; j < 4; j++) {
				reg_val[i] |= (wdata[i * 4 + j] << (j * 8));
			}
		}
	}

	if (remain != 0) {
		for (i = 0; i < remain; i++) {
			reg_val[cnt] |= (wdata[cnt * 4 + i] << (i * 8));
		}
	}

	printf("\n");
	printf(">>>>>>>>wdata[0]=0x%x\n", wdata[0]);
	printf(">>>>>>>>wdata[1]=0x%x\n", wdata[1]);
	printf(">>>>>>>>reg_val[0]=0x%x\n", reg_val[0]);
	printf("\n");

	switch (index) {
	case 7:
		hi2c->Instance->data28_31 = reg_val[7];
	case 6:
		hi2c->Instance->data24_27 = reg_val[6];
	case 5:
		hi2c->Instance->data20_23 = reg_val[5];
	case 4:
		hi2c->Instance->data16_19 = reg_val[4];
	case 3:
		hi2c->Instance->data12_15 = reg_val[3];
	case 2:
		hi2c->Instance->data08_11 = reg_val[2];
	case 1:
		hi2c->Instance->data04_07 = reg_val[1];
	case 0:
		hi2c->Instance->data00_03 = reg_val[0];
	default:
		break;
	}
	printf(">>>>>>>hi2c->Instance->data00_03=0x%x\n", hi2c->Instance->data00_03);
}

static void _i2c_data_set(I2C_HandleTypeDef * hi2c, uint32_t * wdata)
{
	hi2c->Instance->data00_03 = wdata[0];
	hi2c->Instance->data04_07 = wdata[1];
	hi2c->Instance->data08_11 = wdata[2];
	hi2c->Instance->data12_15 = wdata[3];
	hi2c->Instance->data16_19 = wdata[4];
	hi2c->Instance->data20_23 = wdata[5];
	hi2c->Instance->data24_27 = wdata[6];
	hi2c->Instance->data28_31 = wdata[7];
}

static void _i2c_rw_mode_set(I2C_HandleTypeDef * hi2c, I2C_RW_Mode_e rw_mode)
{
	switch (rw_mode) {
	default:
	case I2C_WRITE_MODE:
		hi2c->Instance->control0 &=
		    (~(I2C_CTL0_PREFETCH | I2C_CTL0_RESTART_EN | I2C_CTL0_SUBADDR_EN));
		break;

	case I2C_READ_MODE:
		hi2c->Instance->control0 &= (~(I2C_CTL0_RESTART_EN | I2C_CTL0_SUBADDR_EN));
		hi2c->Instance->control0 |= I2C_CTL0_PREFETCH;
		break;

	case I2C_RESTART_MODE:
		hi2c->Instance->control0 |= (I2C_CTL0_PREFETCH | I2C_CTL0_RESTART_EN |
					     I2C_CTL0_SUBADDR_EN);
		break;
	}
}

/* I2C interrupt enable */
__STATIC_INLINE void _i2c_int_en0_set(I2C_HandleTypeDef * hi2c, uint32_t int0)
{
	hi2c->Instance->int_en0 = int0;
}

/* I2C burst read interrupt enable */
__STATIC_INLINE void _i2c_int_en1_set(I2C_HandleTypeDef * hi2c, uint32_t int1)
{
	hi2c->Instance->int_en1 = int1;	//rdata_en
}

/* I2C burst read the data buffer overflow interrupt enable */
__STATIC_INLINE void _i2c_int_en2_set(I2C_HandleTypeDef * hi2c, uint32_t int2)
{
	hi2c->Instance->int_en2 = int2;	//overflow_en
}

/* The most basic I2C module hardware initialization with MOON register */
__STATIC_INLINE void _i2c_enable(I2C_HandleTypeDef * hi2c)
{
	MODULE_REST->reset[3] = I2C_RESET(hi2c->Index, 0);
	CLK_EN->clock_enable[3] = I2C_CLKEN(hi2c->Index, 1);
	CLK_GATE->clock_gate_enable[3] = I2C_GCLKEN(hi2c->Index, 0);
}

/* Set the I2C master manual active when manual_mode is triggler mode */
__STATIC_INLINE void _i2c_manual_trigger(I2C_HandleTypeDef * hi2c)
{
	hi2c->Instance->i2cm_mode |= I2C_MODE_MANUAL_TRIG;
}

/* I2C mster ring fifo tmpty threshold control(sw control) */
__STATIC_INLINE void _i2c_int_en0_with_thershold_set(I2C_HandleTypeDef * hi2c,
						     uint32_t int0, uint8_t threshold)
{
	hi2c->Instance->int_en0 = (int0 | I2C_EN0_CTL_EMPTY_THRESHOLD(threshold));
}

/* select dma mode */
__STATIC_INLINE void _i2c_dma_mode_enable(I2C_HandleTypeDef * hi2c)
{
	hi2c->Instance->i2cm_mode |= I2C_MODE_DMA_MODE;
}

__STATIC_INLINE void _i2c_dma_addr_set(I2C_HandleTypeDef * hi2c, uint32_t addr)
{
	hi2c->gdma->dma_addr = addr;
}

__STATIC_INLINE void _i2c_dma_length_set(I2C_HandleTypeDef * hi2c, uint32_t len)
{
	/* Only support 16 bit */
	len &= (0xFFFF);
	hi2c->gdma->dma_length = len;
}

static void _i2c_dma_rw_mode_set(I2C_HandleTypeDef * hi2c, I2C_DMA_RW_Mode_e mode)
{
	switch (mode) {
	default:
	case I2C_DMA_WRITE_MODE:
		hi2c->gdma->dma_config |= I2C_DMA_CFG_DMA_MODE;
		break;

	case I2C_DMA_READ_MODE:
		hi2c->gdma->dma_config &= (~I2C_DMA_CFG_DMA_MODE);
		break;
	}
}

__STATIC_INLINE void _i2c_dma_int_en_set(I2C_HandleTypeDef * hi2c, uint32_t int0)
{
	hi2c->gdma->int_en = int0;
}

__STATIC_INLINE void _i2c_dma_go_set(I2C_HandleTypeDef * hi2c)
{
	hi2c->gdma->dma_config |= I2C_DMA_CFG_DMA_GO;
}

void HAL_I2C_IRQHandler(I2C_HandleTypeDef * hi2c)
{
	unsigned int i, j, loop;
	unsigned int status3, bit_index, flag;
	unsigned char w_data[32] = { 0 };

	if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_ADDRESS_NACK_FLAG) == SET) {
		printf("I2C slave address NACK !!\n");
		hi2c->ErrorCode |= HAL_I2C_ERR_ADDRESS_NACK;
		i2c_reset(hi2c);
		hi2c->State = HAL_I2C_STATE_READY;
		return;
	} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DATA_NACK_FLAG) == SET) {
		printf("read I2C slave data NACK !!\n");
		hi2c->ErrorCode |= HAL_I2C_ERR_RECEIVE_NACK;
		i2c_reset(hi2c);
		hi2c->State = HAL_I2C_STATE_READY;
		return;
	} else if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_SCL_HOLD_TOO_LONG_FLAG) == SET) {
		printf("I2C SCL hold too long occur !!\n");
		hi2c->ErrorCode |= HAL_I2C_ERR_SCL_HOLD_TOO_LONG;
		i2c_reset(hi2c);
		hi2c->State = HAL_I2C_STATE_READY;
		return;
	}

	switch (hi2c->State) {
	case HAL_I2C_STATE_BUSY_RX:
		if (hi2c->BurstCount) {
			_i2c_rdata_flag_get(hi2c, (uint32_t *)&status3);

			for (i = 0; i < (I2C_DATA_REG_TOTAL_SIZE / I2C_BURST_RDATA_BYTES); i++) {
				bit_index = (I2C_BURST_RDATA_BYTES - 1) + (I2C_BURST_RDATA_BYTES * i);

				/* Check the data buffer status flag */
				if (status3 & (1 << bit_index))
					continue;

				for (j = 0; j < (I2C_BURST_RDATA_BYTES / I2C_DATA_REG_SIZE); j++) {
					_i2c_data_get(hi2c, hi2c->RegDataIndex,
						      (uint32_t *)(&hi2c->pBuffPtr[hi2c->XferCount]));
					hi2c->RegDataIndex = (hi2c->RegDataIndex + 1) % I2C_DATA_REG_NUMS;
					hi2c->XferCount += I2C_DATA_REG_SIZE;
				}

				flag = ((1 << I2C_BURST_RDATA_BYTES) - 1) << (I2C_BURST_RDATA_BYTES * i);
				_i2c_rdata_flag_clear(hi2c, flag);

				hi2c->BurstCount--;
			}
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == SET) {
			if ((hi2c->BurstRemainder) && (hi2c->State == HAL_I2C_STATE_BUSY_RX)) {
				loop = hi2c->BurstRemainder / I2C_DATA_REG_SIZE;
				if (hi2c->BurstRemainder % I2C_DATA_REG_SIZE)
					loop ++;

				for (j = 0; j < loop; j++) {
					_i2c_data_get(hi2c, hi2c->RegDataIndex,
						      (uint32_t *)(&hi2c->pBuffPtr[hi2c->XferCount]));
					hi2c->RegDataIndex = (hi2c->RegDataIndex + 1) % I2C_DATA_REG_NUMS;
					/* Dont care the last XferCount. Not use. */
					hi2c->XferCount += I2C_DATA_REG_SIZE;
				}
			}
			i2c_reset(hi2c);	// reset
			hi2c->State = HAL_I2C_STATE_READY;
		}
		break;

	case HAL_I2C_STATE_BUSY_TX:
		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_EMPTY_THRESHOLD_FLAG) == SET && (hi2c->BurstCount > 0)) {
			for (i = 0; i < I2C_EMPTY_THRESHOLD_VALUE; i++) {
				for (j = 0; j < 4; j++) {
					/* write_cnt <= 32, DataIndex = DataTotalLen = write_cnt */
					if (hi2c->XferCount >= hi2c->XferSize) {
						w_data[j] = 0;
					} else {
						w_data[j] = hi2c->pBuffPtr[hi2c->XferCount];
					}
					hi2c->XferCount++;
				}
				/* unsigned char *->unsigned int *, 4 bytes, so using data00_03 is enough */
				_i2c_data0_set(hi2c, (uint32_t *)w_data);
				hi2c->BurstCount--;

				if (hi2c->BurstCount == 0) {
					_i2c_int_en0_disable(hi2c, (I2C_EN0_EMPTY_THRESHOLD_INT | I2C_EN0_EMPTY_INT));
					break;
				}
			}
			_i2c_status_clear(hi2c, I2C_CTL1_EMPTY_THRESHOLD_CLR);
		}

		if (__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == SET) {
			i2c_reset(hi2c);	// reset
			hi2c->State = HAL_I2C_STATE_READY;
		}
		break;

	case HAL_I2C_STATE_BUSY_DMA_RX:
	case HAL_I2C_STATE_BUSY_DMA_TX:
		if ((__HAL_I2C_GET_FLAG(hi2c, I2C_INT_DONE_FLAG) == SET) &&
		    (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_DMA_DONE_FLAG) == SET)) {
			i2c_reset(hi2c);	// reset
			hi2c->State = HAL_I2C_STATE_READY;
			i2c_interrupt_control_mask(hi2c->Index, 0);
		} else {
			if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_WCNT_ERROR_FLAG) == SET) {
				printf("I2C DMA WCNT ERR !!\n");
				i2c_reset(hi2c);	// reset
				hi2c->State = HAL_I2C_STATE_READY;
				return;
			} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_WB_EN_ERROR_FLAG) == SET) {
				printf("I2C DMA WB EN ERR !!\n");
				i2c_reset(hi2c);	// reset
				hi2c->State = HAL_I2C_STATE_READY;
				return;
			} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_GDMA_TIMEOUT_FLAG) == SET) {
				printf("I2C DMA timeout !!\n");
				i2c_reset(hi2c);	// reset
				hi2c->State = HAL_I2C_STATE_READY;
				return;
			} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_IP_TIMEOUT_FLAG) == SET) {
				printf("I2C IP timeout !!\n");
				i2c_reset(hi2c);	// reset
				hi2c->State = HAL_I2C_STATE_READY;
				return;
			} else if (__HAL_DMA_GET_FLAG(hi2c, I2C_DMA_INT_THRESHOLD_FLAG) == SET) {
				printf("I2C Length is zero !!\n");
				i2c_reset(hi2c);	// reset
				hi2c->State = HAL_I2C_STATE_READY;
				return;
			}
		}
		break;

	default:
		break;
	}
}
