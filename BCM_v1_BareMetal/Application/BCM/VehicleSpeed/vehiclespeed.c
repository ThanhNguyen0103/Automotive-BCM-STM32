/*
 * vehiclespeed.c
 *
 *  Created on: Jul 12, 2026
 *      Author: nguyz
 */

#include "Drivers/ADC/adc.h"
#include "vehiclespeed.h"
#include "BCM/Ignition/ignition.h"
#include "BCM/Brake/brake.h"
#include "BCM/CruiseControl/cruisecontrol.h"
#include "BCM/DrivingMode/drivingmode.h"

#define ADC_MAX_VALUE 4095

#define ECO_MAX_SPEED 45

#define SPORT_MAX_SPEED 70

static uint32_t currentSpeed = 0;

void VehicleSpeed_Init(void) {
	ADC_Init();
}

void VehicleSpeed_TimerUpdate(void) {

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

	if (Cruise_IsEnabled()) {
		targetSpeed = Cruise_GetSetSpeed();
	} else {
		uint32_t adc_value = ADC_ReadValue();
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

}
uint32_t VehicleSpeed_GetSpeed(void) {
	return currentSpeed;
}
