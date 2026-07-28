/*
 * app.c
 *
 *  Created on: Jul 3, 2026
 *      Author: nguyz
 */

#include <app.h>
#include "Dashboard/dashboard.h"
#include "TurnSignal/turnsignal.h"
#include "VehicleSpeed/vehiclespeed.h"
#include "Brake/brake.h"
#include "CruiseControl/cruisecontrol.h"
#include "DrivingMode/drivingmode.h"
#include "Ignition/ignition.h"

void App_Init(void) {
	Dashboard_Init();
	Ignition_Init();
	DrivingMode_Init();
	VehicleSpeed_Init();
	Brake_Init();
	TurnSignal_Init();
	Cruise_Init();

}
void App_Run(void) {

	Ignition_Run();

	DrivingMode_Run();

	Brake_Run();

	Cruise_Run();

	VehicleSpeed_Run();

	TurnSignal_Run();

	Dashboard_Run();

}
