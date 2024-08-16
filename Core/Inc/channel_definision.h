/*
 * channel_definision.h
 *
 *  Created on: Aug 9, 2024
 *      Author: ohya
 */

#ifndef INC_CHANNEL_DEFINISION_H_
#define INC_CHANNEL_DEFINISION_H_

#include "tim.h"

//#define CHANNEL1(arg) LL_TIM_OC_SetCompareCH3(TIM3, arg)

#define CHANNEL1(arg) LL_TIM_OC_SetCompareCH3(TIM3, arg)
#define CHANNEL2(arg) LL_TIM_OC_SetCompareCH1(TIM16, arg)
#define CHANNEL3(arg) LL_TIM_OC_SetCompareCH2(TIM1, arg)
#define CHANNEL4(arg) LL_TIM_OC_SetCompareCH3(TIM1, arg)
#define CHANNEL5(arg) LL_TIM_OC_SetCompareCH4(TIM1, arg)
#define CHANNEL6(arg) LL_TIM_OC_SetCompareCH1(TIM14, arg)
#define CHANNEL7(arg) LL_TIM_OC_SetCompareCH1(TIM1, arg)
#define CHANNEL8(arg) LL_TIM_OC_SetCompareCH1(TIM3, arg)
#define CHANNEL9(arg) LL_TIM_OC_SetCompareCH2(TIM3, arg)
#define CHANNEL10(arg) LL_TIM_OC_SetCompareCH4(TIM3, arg)




#endif /* INC_CHANNEL_DEFINISION_H_ */
