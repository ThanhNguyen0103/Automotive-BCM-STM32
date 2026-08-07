/*
 * cruisecontrol.h
 *
 *  Created on: Jul 28, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_CRUISECONTROL_H_
#define APPLICATION_CRUISECONTROL_H_

#include "stdbool.h"
#include "stdint.h"
#include "Common/types.h"

Cruise_State_t Cruise_IsEnabled(void);

uint32_t Cruise_GetSetSpeed(void);

void Cruise_Enable(void);

void Cruise_Disable(void);

void Cruise_Init(void);

void Cruise_Run(void);

#endif /* APPLICATION_CRUISECONTROL_H_ */
