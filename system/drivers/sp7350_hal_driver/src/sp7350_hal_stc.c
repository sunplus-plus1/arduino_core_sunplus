#include "sp7350_hal.h"
#include "sp7350_hal_stc.h"


#ifdef __cplusplus
extern "C" {
#endif


void HAL_STC_EnableSTCClock(STC_HandleTypeDef *Hstc)
{
	MODULE_ID_Type mode_id = STC_0;

	assert_param(IS_STC_INSTANCE(Hstc->Instance));

	switch((uint32_t)Hstc->Instance)
	{
		case (uint32_t)STC0: 
			mode_id = STC_0;
			break;
		case (uint32_t)STC1: 
			mode_id = STC_AV0;
			break;
		case (uint32_t)STC2: 
			mode_id = STC_AV1;
			break;
		case (uint32_t)STC3: 
			mode_id = STC_AV2;
			break;
		default: 
			break;
	}

	HAL_Module_Clock_enable(mode_id, 1);
	HAL_Module_Clock_gate(mode_id, 1);
	HAL_Module_Reset(mode_id, 0);

}

HAL_StatusTypeDef HAL_STC_Init(STC_HandleTypeDef *Hstc)
{
	if (Hstc == NULL)
		return HAL_ERROR;
	assert_param(IS_STC_INSTANCE(Hstc->Instance));

	HAL_STC_EnableSTCClock(Hstc);
	memset(Hstc->Instance, 0, sizeof(STC_TypeDef));	
	Hstc->Instance->stc_prescale_val = 0;
	Hstc->Instance->stc_config = 0;
	/*External Clock source*/
	if (Hstc->ClockSource){
		Hstc->Instance->stc_config = Hstc->ExtDiv;
		MODIFY_REG(Hstc->Instance->stc_prescale_val, STC_TRIG_SRC, 1<<STC_TRIG_SRC_Pos);
	}
 	MODIFY_REG(Hstc->Instance->stc_prescale_val, STC_PRESCALER, Hstc->Prescaler<<STC_PRESCALER_Pos);
 	Hstc->Instance->stc_64 = 0;
	Hstc->Instance->stc_63_32 = 0;
	Hstc->Instance->stc_31_0 = 0;

	return HAL_OK;

}

HAL_StatusTypeDef HAL_STC_SetPrescaler(STC_HandleTypeDef *Hstc, uint32_t u32Prescaler)
{
	if (Hstc == NULL)
		return HAL_ERROR;
	assert_param(IS_STC_INSTANCE(Hstc->Instance));

	MODIFY_REG(Hstc->Instance->stc_prescale_val, STC_PRESCALER, Hstc->Prescaler<<STC_PRESCALER_Pos);
	Hstc->Prescaler = u32Prescaler;
	return HAL_OK;
}


HAL_StatusTypeDef HAL_STC_SetExtDiv(STC_HandleTypeDef *Hstc, uint32_t u32div)
{

	if (Hstc == NULL || !IS_STC_INSTANCE(Hstc->Instance))
		return HAL_ERROR;
	
	MODIFY_REG(Hstc->Instance->stc_config, STC_EXT_DIV, Hstc->Instance->stc_config << STC_EXT_DIV_Pos);
	Hstc->ExtDiv = u32div;
	
	return HAL_OK;
}

uint64_t HAL_STC_GetCounter(STC_HandleTypeDef *Hstc)
{
	if (Hstc == NULL || !IS_STC_INSTANCE(Hstc->Instance))
		return 0;

	READ_REG(Hstc->Instance->stc_31_0); /* latch stc value */

	return READ_REG(Hstc->Instance->stc_31_0);
}

uint32_t HAL_STC_GetPrescaler(STC_HandleTypeDef *Hstc)
{

	if (Hstc == NULL)
		return 0;
	assert_param(IS_STC_INSTANCE(Hstc->Instance));

	return (Hstc->Instance->stc_prescale_val&STC_PRESCALER_Msk)>>STC_PRESCALER_Pos;

}


uint32_t HAL_STC_GetExtDiv(STC_HandleTypeDef *Hstc)
{

	if (Hstc == NULL)
		return 0;
	assert_param(IS_STC_INSTANCE(Hstc->Instance));

	return (Hstc->Instance->stc_config&STC_EXT_DIV_Msk)>>STC_EXT_DIV_Pos;

}












#ifdef __cplusplus
}
#endif





