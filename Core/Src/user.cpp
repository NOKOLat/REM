/*
 * user.cpp
 *
 *  Created on: Aug 16, 2024
 *      Author: ohya
 */

#include "user.h"
#include "channel_definision.h"

uint32_t adcValue=0;

void failsafe(){
	CHANNEL3(0);
}
