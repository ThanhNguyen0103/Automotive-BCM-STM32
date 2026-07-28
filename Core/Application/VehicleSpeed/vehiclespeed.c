/*
 * vehiclespeed.c
 *
 *  Created on: Jul 12, 2026
 *      Author: nguyz
 */

#include <ADC/adc.h>
#include "vehiclespeed.h"

#include "Brake/brake.h"
#include "CruiseControl/cruisecontrol.h"
#include "DrivingMode/drivingmode.h"
#include "Ignition/ignition.h"

#define ADC_MAX_VALUE 4095

#define ECO_MAX_SPEED 45

#define SPORT_MAX_SPEED 70

static uint32_t currentSpeed = 0;

void VehicleSpeed_Init(void) {
	ADC_Init();
}

void VehicleSpeed_Run(void) {

	uint32_t targetSpeed;

	if (Ignition_GetState() == IGNITION_OFF) {
		if (currentSpeed > 0) {
			currentSpeed--;
		}
		return;
	}

	Driving_Mode_t mode = DrivingMode_GetState();

	const uint32_t maxSpeed =
			(mode == ECO_MODE) ? ECO_MAX_SPEED : SPORT_MAX_SPEED;

	const uint32_t adc_value = ADC_ReadValue();

	if (Cruise_IsEnabled()) {
		targetSpeed = Cruise_GetSetSpeed();
	} else {
		targetSpeed = (adc_value * maxSpeed) / ADC_MAX_VALUE;
	}

	if (Brake_GetState() == BRAKE_ON) {
		if (currentSpeed > 0)
			currentSpeed--;
	} else {
		if (currentSpeed < targetSpeed) {
			currentSpeed++;
		} else if (currentSpeed > targetSpeed) {
			currentSpeed--;
		}
	}

//	CAN_Frame_t frame;
//	frame.id = CAN_ID_VEHICLE_SPEED;
//	frame.dlc = 1;
//	frame.data[0] = VehicleSpeed_GetSpeed();
//
//	CAN_Send(&frame);

}
uint32_t VehicleSpeed_GetSpeed(void) {
	return currentSpeed;
}
