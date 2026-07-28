/*
 * drivingmode.h
 *
 *  Created on: Jul 9, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_DRIVINGMODE_H_
#define APPLICATION_DRIVINGMODE_H_

typedef enum {
	ECO_MODE, SPORT_MODE,

} Driving_Mode_t;

Driving_Mode_t DrivingMode_GetState(void);
//Driving_Mode_t drivingMode_setState(Driving_Mode_t mode);

void DrivingMode_Init(void);
void DrivingMode_Run(void);
#endif /* APPLICATION_DRIVINGMODE_H_ */
