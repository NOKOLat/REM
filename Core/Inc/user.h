/*
 * user.h
 *
 *  Created on: Aug 16, 2024
 *      Author: ohya
 */

#ifndef INC_USER_H_
#define INC_USER_H_

#include "gpio.h"
#include <array>

#include "SBUS/sbus.h"

#define PB7 GPIOB, GPIO_PIN_7
#define PC14 GPIOC, GPIO_PIN_14

#define __IS_IR_DETECTED adcValue < ADC_THRESHOLD

#define __SET_MANUAL_HOLDING_TIME(arg) arg = HAL_GetTick() + 5*1000;

extern uint16_t adcValue;

inline std::array<uint16_t,10> mixer(nokolat::SBUS_DATA &input){
	const uint8_t ADC_THRESHOLD = 100;
	const uint16_t AUTO_MANULA_THRESHOLD = 1500;
	static uint32_t holdManualModeUntill = 0;
	static std::array<uint16_t,10> res;
	auto it_res = res.begin();

	*it_res++ = input.at(0);
	*it_res++ = input.at(1);
	*it_res++ = input.at(2);
	*it_res++ = input.at(3);
	*it_res++ = input.at(4);
	*it_res++ = input.at(5);

	if(__IS_IR_DETECTED && input.at(5) > AUTO_MANULA_THRESHOLD){
		//auto release
		*it_res++ = input.at(6);
	}else if(input.at(5) <= AUTO_MANULA_THRESHOLD){
		//controller is set to manual mode
		if(__IS_IR_DETECTED){
			__SET_MANUAL_HOLDING_TIME(holdManualModeUntill);
			it_res++;
		}else if(holdManualModeUntill > HAL_GetTick()){
			//Hold on manual mode after IR is detected
			it_res++;
		}else{
			//manual mode
			*it_res++ = input.at(6);
		}
	}else{
		//Hold on auto mode
		it_res++;
	}

	*it_res++ = input.at(7);
	*it_res++ = input.at(8);
	*it_res++ = input.at(9);

	return res;
}

void failsafe();

#endif /* INC_USER_H_ */
