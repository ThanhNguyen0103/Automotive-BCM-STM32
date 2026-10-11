/*
 * drivingmode.h
 *
 *  Created on: Jul 9, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_DRIVINGMODE_H_
#define APPLICATION_DRIVINGMODE_H_

#include "Common/types.h"

Driving_Mode_t DrivingMode_GetState(void);

void DrivingMode_Init(void);
void DrivingMode_Run(void);
#endif /* APPLICATION_DRIVINGMODE_H_ */
