/*
 * cruisecontrol.c
 *
 *  Created on: Jul 28, 2026
 *      Author: nguyz
 */

#include <Button/button.h>
#include "cruisecontrol.h"

#include "Brake/brake.h"
#include "Ignition/ignition.h"
#include "VehicleSpeed/vehiclespeed.h"

static uint32_t setSpeed = 0;
static Cruise_State_t cruiseState = CRUISE_OFF;
static Button_t cruiseButton;

void Cruise_Init(void) {
	Button_Init(&cruiseButton, GPIOB, GPIO_PIN_0);

}

void Cruise_Run(void) {

	Button_Update(&cruiseButton);
	if (Button_IsPressed(&cruiseButton)) {
		if (cruiseState) {
			Cruise_Disable();
		} else {
			if (VehicleSpeed_GetSpeed() > 20) {
				Cruise_Enable();
			}
		}
	}

	if (Ignition_GetState() == IGNITION_OFF) {
		Cruise_Disable();
	}
	if (Brake_GetState() == BRAKE_ON) {
		Cruise_Disable();
	}
	if (VehicleSpeed_GetSpeed() < 20) {
		Cruise_Disable();
	}
}

Cruise_State_t Cruise_IsEnabled(void) {
	return cruiseState;
}

uint32_t Cruise_GetSetSpeed(void) {
	return setSpeed;
}
void Cruise_Enable(void) {
	cruiseState = CRUISE_ON;
	setSpeed = VehicleSpeed_GetSpeed();
}

void Cruise_Disable(void) {
	cruiseState = CRUISE_OFF;
}
