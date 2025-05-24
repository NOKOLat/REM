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

std::array<uint16_t,10> mixer(nokolat::SBUS_DATA &input);
void failsafe();

#endif /* INC_USER_H_ */
