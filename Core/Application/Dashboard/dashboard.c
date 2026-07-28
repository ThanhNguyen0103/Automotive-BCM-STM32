/*
 * dashboard.c
 *
 *  Created on: Jul 4, 2026
 *      Author: nguyz
 */

#include "dashboard.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"

#include "CruiseControl/cruisecontrol.h"
#include "DrivingMode/drivingmode.h"
#include "Ignition/ignition.h"
#include "VehicleSpeed/vehiclespeed.h"

static IgnitionState_t preIgnition = IGNITION_OFF;
static Driving_Mode_t preMode = ECO_MODE;
static uint32_t preSpeed = 0;
static Cruise_State_t preCruise = CRUISE_OFF;

void Dashboard_Init(void) {
	ssd1306_Init();
}

void Dashboard_Run(void) {

	IgnitionState_t ignition = Ignition_GetState();
	Driving_Mode_t mode = DrivingMode_GetState();
	uint32_t speed = VehicleSpeed_GetSpeed();
	Cruise_State_t cruise = Cruise_IsEnabled();

	if (ignition == preIgnition && mode == preMode && speed == preSpeed
			&& cruise == preCruise) {
		return;
	}
	preIgnition = ignition;
	preMode = mode;
	preSpeed = speed;
	preCruise = cruise;

	char speedStr[16];

	snprintf(speedStr, sizeof(speedStr), "%lu km/h", speed);

	ssd1306_Fill(Black);

	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("IGNITION:", Font_7x10, White);

	ssd1306_SetCursor(80, 0);
	ssd1306_WriteString(ignition == IGNITION_ON ? "ON" : "OFF", Font_7x10,
			White);

	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString("MODE:", Font_7x10, White);

	ssd1306_SetCursor(80, 10);
	if (ignition == IGNITION_OFF) {
		ssd1306_WriteString("---", Font_7x10, White);
	} else {
		ssd1306_WriteString(mode == ECO_MODE ? "ECO" : "SPORT", Font_7x10,
				White);
	}

	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString("SPEED:", Font_7x10, White);

	ssd1306_SetCursor(80, 20);
	ssd1306_WriteString(speedStr, Font_7x10, White);

	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString("Cruise:", Font_7x10, White);

	ssd1306_SetCursor(80, 30);
	ssd1306_WriteString(cruise == CRUISE_OFF ? "OFF" : "ON", Font_7x10, White);

	ssd1306_UpdateScreen();

}
