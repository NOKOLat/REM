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
#include <array>

#include "SBUS/sbus.h"

#include "channel_definision.h"
#include "user.h"

#define PB7 GPIOB, GPIO_PIN_7
#define PC14 GPIOC, GPIO_PIN_14

extern nokolat::SBUS sbus;
extern nokolat::SBUS_DATA sbusData;

extern uint32_t adcValue;

inline void init(void){
	HAL_GPIO_WritePin(PB7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC14, GPIO_PIN_SET);

	sbusData = sbus.getData();
//	HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());

//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);

	HAL_TIM_Base_Start_IT(&htim17);
	HAL_GPIO_WritePin(PB7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PC14, GPIO_PIN_RESET);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcValue, 1);
}

inline void loop(void){
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());
}

inline void sbusRxCompleteCallBack(){
	HAL_GPIO_TogglePin(PC14);
	sbus.parse();
//	sbusData = sbus.getData();

	if(sbusData.failsafe){
		//failsafe
		failsafe();
	}else if(sbusData.framelost){
		//frame lost
//		failsafe();
	}else{
		//Receive the data successfully.
		__HAL_TIM_SET_COUNTER(&htim17,0);
	}

	std::array<uint16_t, 10> mixedChannels = mixer(sbusData);
	auto it = mixedChannels.begin();

	CHANNEL1(*it++);
	CHANNEL2(*it++);
	CHANNEL3(*it++);
	CHANNEL4(*it++);
	CHANNEL5(*it++);
	CHANNEL6(*it++);
	CHANNEL7(*it++);
	CHANNEL8(*it++);
	CHANNEL9(*it++);
	CHANNEL10(*it++);
}


#endif /* INC_WRAPPER_HPP_ */

