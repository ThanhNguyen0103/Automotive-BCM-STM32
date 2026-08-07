/*
 * drivingmode.c
 *
 *  Created on: Jul 9, 2026
 *      Author: nguyz
 */

#include "Drivers/BUTTON/button.h"
#include "drivingmode.h"
#include "BCM/Ignition/ignition.h"

static Driving_Mode_t drivingMode;
static Button_t driving_button_mode;

Driving_Mode_t DrivingMode_GetState(void) {
	return drivingMode;
}

void DrivingMode_Init(void) {
	Button_Init(&driving_button_mode, GPIOB, GPIO_PIN_11);
	drivingMode = ECO_MODE;
}

void DrivingMode_Run(void) {
	Button_Update(&driving_button_mode);
	if (Ignition_GetState() == IGNITION_OFF) {
		return;
	}
	if (Button_IsPressed(&driving_button_mode)) {
		drivingMode = (drivingMode == ECO_MODE) ? SPORT_MODE : ECO_MODE;

	}

}
