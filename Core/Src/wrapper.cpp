/*
 * wrapper.cpp
 *
 *  Created on: Oct 23, 2023
 *      Author: ohya
 */
#include "wrapper.hpp"

#include "SBUS/sbus.h"

nokolat::SBUS sbus;
nokolat::SBUS_DATA sbusData;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim17){
		failsafe();
		HAL_GPIO_WritePin(PC14, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(PB7);
		HAL_UART_AbortReceive(&huart2);
		HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart2){
		sbusRxCompleteCallBack();
	}
}


//void tim17Callback(){
////	auto htim = &htim17;
////	uint16_t sr = htim->Instance->SR;
////	if((sr & (TIM_IT_CC1)) == (TIM_IT_CC1)){
////		__HAL_TIM_CLEAR_FLAG(htim,TIM_IT_CC1);
////		HAL_UART_AbortReceive(huartSbus);
////		HAL_UART_Receive_IT(huartSbus,sbus.getReceiveBufferPtr(),sbus.getDataLen());
////	}else if((sr & TIM_IT_UPDATE) == (TIM_IT_UPDATE)){
////		__HAL_TIM_CLEAR_FLAG(htim,TIM_IT_UPDATE);
////	}
//}
