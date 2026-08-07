/*
 * cruisecontrol.c
 *
 *  Created on: Jul 28, 2026
 *      Author: nguyz
 */

#include "Drivers/BUTTON/button.h"
#include "cruisecontrol.h"

#include "BCM/Brake/brake.h"
#include "BCM/Ignition/ignition.h"
#include "BCM/VehicleSpeed/vehiclespeed.h"

#define CRUISE_MIN_SPEED 20

static uint32_t setSpeed = 0;
static Cruise_State_t cruiseState = CRUISE_OFF;
static Button_t cruiseButton;

void Cruise_Init(void) {
	Button_Init(&cruiseButton, GPIOB, GPIO_PIN_0);

}

void Cruise_Run(void) {

	Button_Update(&cruiseButton);
	if (Button_IsPressed(&cruiseButton)) {
		if (cruiseState == CRUISE_ON) {
			Cruise_Disable();
		} else {
			if (VehicleSpeed_GetSpeed() >= CRUISE_MIN_SPEED) {
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
	if (VehicleSpeed_GetSpeed() < CRUISE_MIN_SPEED) {
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
