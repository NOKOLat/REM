/*
 * wrapper.hpp
 *
 *  Created on: Oct 23, 2023
 *      Author: ohya
 */


#ifndef INC_WRAPPER_HPP_
#define INC_WRAPPER_HPP_

#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"
#include <array>

#include "SBUS/sbus.h"

#include "channel_definision.h"
#include "user.h"

extern nokolat::SBUS sbus;

extern uint16_t adcValue;

inline void init(void){
	HAL_GPIO_WritePin(PB7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC14, GPIO_PIN_SET);

	/* Set the TIM channel state */
	TIM_CHANNEL_STATE_SET(&htim1, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim1, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim1, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim1, TIM_CHANNEL_4, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim3, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim3, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim3, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim3, TIM_CHANNEL_4, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim14, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
	TIM_CHANNEL_STATE_SET(&htim16, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
	/* Enable the Capture compare channel */
	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_4, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim3.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim3.Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim3.Instance, TIM_CHANNEL_3, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim3.Instance, TIM_CHANNEL_4, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim14.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	TIM_CCxChannelCmd(htim16.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	__HAL_TIM_MOE_ENABLE(&htim1);
	__HAL_TIM_MOE_ENABLE(&htim16);
	__HAL_TIM_ENABLE(&htim1);
	__HAL_TIM_ENABLE(&htim3);
	__HAL_TIM_ENABLE(&htim14);
	__HAL_TIM_ENABLE(&htim16);

	htim17.State = HAL_TIM_STATE_BUSY;
	__HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&htim17);

	HAL_GPIO_WritePin(PB7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC14, GPIO_PIN_RESET);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcValue, 1);
	hadc1.DMA_Handle->Instance->CCR &= ~(DMA_IT_TC | DMA_IT_HT);
}

inline void loop(void){
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());
}

inline void sbusRxCompleteCallBack(){
	HAL_GPIO_TogglePin(PB7);
	nokolat::SBUS_DATA sbusData = sbus.getData();
	sbus.parse();

	if(sbusData.failsafe){
		//failsafe
		failsafe();
	}else if(sbusData.framelost){
		//frame lost
		failsafe();
	}else{
		//Receive the data successfully.
		__HAL_TIM_SET_COUNTER(&htim17,0);
		HAL_GPIO_WritePin(PC14, GPIO_PIN_RESET);
	}

	std::array<uint16_t, 10> mixedChannels = mixer(sbusData);
	auto it = mixedChannels.begin();

	CHANNEL1(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL2(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL3(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL4(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL5(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL6(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL7(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL8(sbus.convertSbus2PwmWidthUS(*it++));
	CHANNEL9(((*it++-sbus.getSbusMin())*2500)/(sbus.getSbusMax() - sbus.getSbusMin()));
	CHANNEL10(((*it++-sbus.getSbusMin())*2500)/(sbus.getSbusMax() - sbus.getSbusMin()));
}


#endif /* INC_WRAPPER_HPP_ */

