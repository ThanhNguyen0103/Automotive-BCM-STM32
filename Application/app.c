/*
 * app.c
 *
 *  Created on: Jul 3, 2026
 *      Author: nguyz
 */

#include "app.h"
#include "BCM/Brake/brake.h"
#include "BCM/CruiseControl/cruisecontrol.h"
#include "BCM/Dashboard/dashboard.h"
#include "BCM/DrivingMode/drivingmode.h"
#include "BCM/Ignition/ignition.h"
#include "BCM/TurnSignal/turnsignal.h"
#include "BCM/VehicleSpeed/vehiclespeed.h"
#include "CAN/can_manager.h"

void App_Init(void) {

	CANManager_Init();

	Dashboard_Init();

	Ignition_Init();

	DrivingMode_Init();

	VehicleSpeed_Init();

	Brake_Init();

	Cruise_Init();

	TurnSignal_Init();

}
void App_Run(void) {

	Ignition_Run();

	DrivingMode_Run();

	Brake_Run();

	Cruise_Run();

	VehicleSpeed_Run();

	TurnSignal_Run();

	CANManager_Run();

	Dashboard_Run();

}
