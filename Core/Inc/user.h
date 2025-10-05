/*
 * user.h
 *
 *  Created on: Aug 16, 2024
 *      Author: ohya
 */

#ifndef INC_USER_H_
#define INC_USER_H_

#include <array>

#include "SBUS/sbus.h"

#define PB7 GPIOB, GPIO_PIN_7
#define PC14 GPIOC, GPIO_PIN_14

#define CONVERT_TO_RC_PWM_WIDTH(sbusValue) sbus.convertSbus2PwmWidthUS(sbusValue)
#define CONVERT_TO_LED_PWM_WIDTH(sbusValue) ((sbusValue -sbus.getSbusMin())*maxPulseWidthUs)/(sbus.getSbusMax() - sbus.getSbusMin())

extern uint16_t adcValue;
extern const uint16_t maxPulseWidthUs;
extern nokolat::SBUS sbus;

inline std::array<uint16_t,10> mixer(nokolat::SBUS_DATA &input){
	std::array<uint16_t,10> res;
	auto it_res = res.begin();

	*it_res++ = input.at(0);
	*it_res++ = input.at(1);
	*it_res++ = input.at(2);
	*it_res++ = input.at(3);
	*it_res++ = input.at(4);
	*it_res++ = input.at(5);
	*it_res++ = input.at(6);
	*it_res++ = input.at(7);
	*it_res++ = input.at(8);
	*it_res++ = input.at(9);

	return res;
}

inline std::array<uint16_t,10> convertToPwmWidth(std::array<uint16_t, 10> &sbusValue){
	std::array<uint16_t,10> res;
	auto it_res = res.begin();
	auto it_arg = sbusValue.begin();

	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 1
	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 2
	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 3
	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 4
	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 5
	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 6
	*it_res++ = CONVERT_TO_RC_PWM_WIDTH(*it_arg++);//ch. 7
	*it_res++ = CONVERT_TO_LED_PWM_WIDTH(*it_arg++);//ch. 8
	*it_res++ = CONVERT_TO_LED_PWM_WIDTH(*it_arg++);//ch. 9
	*it_res++ = CONVERT_TO_LED_PWM_WIDTH(*it_arg++);//ch. 10

	return res;
}

void failsafe();

#endif /* INC_USER_H_ */
