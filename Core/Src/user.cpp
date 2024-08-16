/*
 * user.cpp
 *
 *  Created on: Aug 16, 2024
 *      Author: ohya
 */

#include "user.h"

std::array<uint16_t,10> mixer(nokolat::SBUS_DATA &input){
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
