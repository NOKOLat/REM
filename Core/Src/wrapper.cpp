/*
 * wrapper.cpp
 *
 *  Created on: Oct 23, 2023
 *      Author: ohya
 */

#include "wrapper.hpp"

#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <array>

#include "SBUS/sbus.h"

#include "channel_definision.h"
#include "user.h"

nokolat::SBUS sbus;
nokolat::SBUS_DATA sbusData;

#define PB7 GPIOB, GPIO_PIN_7
#define PC14 GPIOC, GPIO_PIN_14

void init(){
	HAL_GPIO_WritePin(PB7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PC14, GPIO_PIN_SET);

	sbusData = sbus.getData();
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);

	HAL_TIM_Base_Start_IT(&htim17);

}

void loop(){

}

void sbusRxCompleteCallBack(){
	HAL_GPIO_TogglePin(PC14);
	sbus.parse();
	sbusData = sbus.getData();
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());

	if(sbusData.failsafe){
		//failsafe
		failsafe();
	}else if(sbusData.framelost){
		//frame lost
		failsafe();
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim17){
		failsafe();
		HAL_GPIO_WritePin(PC14, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(PB7);
		HAL_UART_DMAStop(&huart2);
		HAL_UART_Receive_DMA(&huart2, (uint8_t*)sbus.getReceiveBufferPtr(), sbus.getDataLen());
	}
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
////	if(huart == huartSbus){
////		htim17.Instance->CNT = 0;
////		sbus.requireDecode();
////		sbusData = sbus.getData();
////		if(sbusData.failsafe){
////			//failsafe mode
////		}else if(sbusData.framelost){
////			//frame lost
////
////		}else{
////
////		}
////		HAL_UART_Receive_IT(huartSbus,sbus.getReceiveBufferPtr(),sbus.getDataLen());
////
//////		esc.setSpeed(hmulticopter->controller(multicopterInput));
////	}
//}


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
