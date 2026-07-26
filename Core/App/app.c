/*
 * app.c
 *
 *  Created on: Jul 3, 2026
 *      Author: nguyz
 */

#include "app.h"
#include "ignition.h"
#include "dashboard.h"
#include"drivingmode.h"
#include "vehiclespeed.h"
#include "brake.h"
#include "turnsignal.h"

void App_Init(void) {
	Dashboard_Init();
	Ignition_Init();
	DrivingMode_Init();
	VehicleSpeed_Init();
	Brake_Init();
	TurnSignal_Init();

}
void App_Run(void) {

	Ignition_Run();
	DrivingMode_Run();
	VehicleSpeed_Run();
	Brake_Run();
	TurnSignal_Run();

	Dashboard_Run();

}
