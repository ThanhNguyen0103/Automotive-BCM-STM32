/*
 * vehiclespeed.h
 *
 *  Created on: Jul 12, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_VEHICLESPEED_H_
#define APPLICATION_VEHICLESPEED_H_

#include "stdint.h"

void VehicleSpeed_Init(void);
void VehicleSpeed_TimerUpdate(void);
uint32_t VehicleSpeed_GetSpeed(void);

#endif /* APPLICATION_VEHICLESPEED_H_ */
