/*
 * wrapper.cpp
 *
 *  Created on: Oct 23, 2023
 *      Author: ohya
 */
#include "wrapper.hpp"

#include "SBUS/sbus.h"

nokolat::SBUS sbus;
uint16_t adcValue=0;

const uint16_t maxPulseWidthUs = 2500;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim17){
		failsafe();
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
