/*
 * user.cpp
 *
 *  Created on: Aug 16, 2024
 *      Author: ohya
 */

#include "user.h"
#include "channel_definision.h"

void failsafe(){
	HAL_GPIO_WritePin(PC14, GPIO_PIN_SET);
	CHANNEL3(0);
}
