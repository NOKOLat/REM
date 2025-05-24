/*
 * channel_definision.h
 *
 *  Created on: Aug 9, 2024
 *      Author: ohya
 */

#ifndef INC_CHANNEL_DEFINISION_H_
#define INC_CHANNEL_DEFINISION_H_

#include "tim.h"

#define CHANNEL1(arg) __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arg)
#define CHANNEL2(arg) __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, arg)
#define CHANNEL3(arg) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, arg)
#define CHANNEL4(arg) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, arg)
#define CHANNEL5(arg) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, arg)
#define CHANNEL6(arg) __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, arg)
#define CHANNEL7(arg) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, arg)
#define CHANNEL8(arg) __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arg)
#define CHANNEL9(arg) __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arg)
#define CHANNEL10(arg) __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arg)




#endif /* INC_CHANNEL_DEFINISION_H_ */
