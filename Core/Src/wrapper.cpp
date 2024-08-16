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
#include "LL_Extension/TIM/LL_Extension_TIM_all.hpp"
#include "LL_Extension/GPIO/LL_Extension_GPIO_all.hpp"

#include "channel_definision.h"
#include "user.h"

nokolat::SBUS sbus;
nokolat::SBUS_DATA sbusData;

llex::USART_Interrupt husart2(USART2,sbusRxCompleteCallBack);
llex::TIM_interrupt htimer17(TIM17);
llex::GPIO pb7(GPIOB,LL_GPIO_PIN_7);
llex::GPIO pc14(GPIOC, LL_GPIO_PIN_14);

void init(){
	LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_7);
	pb7.set();
	pc14.set();
	sbusData = sbus.getData();
	husart2.receive((uint8_t*)sbus.getBufferIterator(), sbus.getDataLen());

	LL_TIM_EnableCounter(TIM3);
	LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH2|LL_TIM_CHANNEL_CH3|LL_TIM_CHANNEL_CH4);
	LL_TIM_EnableCounter(TIM14);
	LL_TIM_CC_EnableChannel(TIM14, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM16);
	LL_TIM_CC_EnableChannel(TIM16, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH2|LL_TIM_CHANNEL_CH3|LL_TIM_CHANNEL_CH4);
	LL_TIM_WriteReg(TIM1,BDTR,(LL_TIM_ReadReg(TIM1,BDTR)|TIM_BDTR_MOE));
	LL_TIM_WriteReg(TIM16,BDTR,(LL_TIM_ReadReg(TIM1,BDTR)|TIM_BDTR_MOE));

}

void loop(){

}

void sbusRxCompleteCallBack(){
	LL_GPIO_TogglePin(GPIOC,LL_GPIO_PIN_14);
	////		htim17.Instance->CNT = 0;
	sbus.requireDecode();
	sbusData = sbus.getData();
	husart2.receive((uint8_t*)sbus.getBufferIterator(), sbus.getDataLen());

	if(sbusData.failsafe){
		//failsafe mode66
	}else if(sbusData.framelost){
		//frame lost

	}

	std::array<uint16_t, 10> mixedChannels = mixer(sbusData);
	auto it = mixedChannels.begin();

	if(sbusData[0]>1300){
		LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_7);
	}else{
		LL_GPIO_ResetOutputPin(GPIOB,LL_GPIO_PIN_7);
	}

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
