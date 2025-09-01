/*
 * user.h
 *
 *  Created on: Aug 16, 2024
 *      Author: ohya
 */

#ifndef INC_USER_H_
#define INC_USER_H_

#define MANUAL_ONLY

#include "gpio.h"
#include <array>

#include "sbus.h"

#define PB7 GPIOB, GPIO_PIN_7
#define PC14 GPIOC, GPIO_PIN_14

extern uint16_t adcValue;

inline std::array<uint16_t,10> mixer(nokolat::SBUS_DATA &input){
	const uint8_t ADC_THRESHOLD = 100;
	const uint16_t AUTO_MANULA_THRESHOLD = 1500;
	static std::array<uint16_t,10> res;
	auto it_res = res.begin();

	*it_res++ = input.at(0);
	*it_res++ = input.at(1);
	*it_res++ = input.at(2);
	*it_res++ = input.at(3);
	*it_res++ = input.at(4);
	*it_res++ = input.at(5);

#ifdef MANUAL_ONLY
	*it_res++ = input.at(6);
#endif

#ifndef MANUAL_ONLY
	// 6chは自動/手動の切り替え
	// 7chは投下装置
	if(adcValue < ADC_THRESHOLD && input.at(5) > AUTO_MANULA_THRESHOLD){
		// 赤外線検知 かつ 6chが閾値より大きい
		// 7chの値を渡す
		*it_res++ = input.at(6);
	}else if(input.at(5) <= AUTO_MANULA_THRESHOLD){
		// 赤外線の値によらず 6chが閾値以下
		// 7chの値を渡す
		*it_res++ = input.at(6);
	}else{
		// 赤外線未検知 かつ 自動投下on
		// 前の値を保持
		it_res++;
	}
#endif

	*it_res++ = input.at(7);
	*it_res++ = input.at(8);
	*it_res++ = input.at(9);

	return res;
}

void failsafe();

#endif /* INC_USER_H_ */
/*
	if(adcValue < ADC_THRESHOLD){
		// 赤外線検知
		// 赤外線検知フラグたてる
		IRDetection = true;
		if(autoDropParmittion)
			*it_res++ = input.at(6);
		}else{
			*it_res++;
		}
	}else{
		IRDetection = false;
	}
	if(input.at(5) > AUTO_MANULA_THRESHOLD){
		if(IRDetection){
			autoDropParmittion = true;
		}
	}else{
		autoDropParmittion = false;
		*it_res++ = input.at(6);
	}
*/
