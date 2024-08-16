/*
 * wrapper.hpp
 *
 *  Created on: Oct 23, 2023
 *      Author: ohya
 */


#ifndef INC_WRAPPER_HPP_
#define INC_WRAPPER_HPP_

#include "tim.h"
#include "LL_Extension/USART/LL_Extension_USART_Interrupt.hpp"

void init(void);
void loop(void);

//void tim17Callback();
inline void sbusRxCompleteCallBack();

extern llex::USART_Interrupt husart2;

void debug();

#endif /* INC_WRAPPER_HPP_ */

