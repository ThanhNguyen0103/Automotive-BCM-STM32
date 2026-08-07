/*
 * canmanager.c
 *
 *  Created on: Jul 29, 2026
 *      Author: nguyz
 */
#include "can_manager.h"
#include "Drivers/CAN/can.h"
#include "BCM/Ignition/ignition.h"
#include "BCM/VehicleSpeed/vehiclespeed.h"
#include "BCM/DrivingMode/drivingmode.h"
#include "BCM/TurnSignal/turnsignal.h"
#include "Common/config.h"

void CANManager_Init(void) {
	CAN_Init();
}
void CANManager_SendSpeed(void) {
	static uint32_t lastSpeed = 0;

	uint32_t speed = VehicleSpeed_GetSpeed();

	if (speed == lastSpeed)
		return;

	lastSpeed = speed;

	CAN_Frame_t frame;
	frame.id = CAN_ID_SPEED;
	frame.dlc = 1;
	frame.data[0] = (uint8_t) speed;

	CAN_Send(&frame);
}
void CANManager_SendIgnition(void) {

	static IgnitionState_t lastIgnition = IGNITION_OFF;

	IgnitionState_t ignition = Ignition_GetState();
	if (ignition == lastIgnition)
		return;
	lastIgnition = ignition;

	CAN_Frame_t frame;
	frame.id = CAN_ID_IGNITION;
	frame.dlc = 1;
	frame.data[0] = (uint8_t) ignition;

	CAN_Send(&frame);
}

void CANManager_SendTurnSignal(void) {
	static TurnSignalState_t lastState = TURN_OFF;
	TurnSignalState_t state = TurnSignal_GetState();
	if (state == lastState)
		return;
	lastState = state;

	CAN_Frame_t frame;
	frame.id = CAN_ID_TURNSIGNAL;
	frame.dlc = 1;
	frame.data[0] = (uint8_t) state;

	CAN_Send(&frame);

}
void CANManager_SendDrivingMode(void) {
	static Driving_Mode_t lastDrvingMode = ECO_MODE;
	Driving_Mode_t drivingMode = DrivingMode_GetState();
	if (drivingMode == lastDrvingMode)
		return;
	lastDrvingMode = drivingMode;

	CAN_Frame_t frame;
	frame.id = CAN_ID_MODE;
	frame.dlc = 1;
	frame.data[0] = (uint8_t) drivingMode;

	CAN_Send(&frame);
}

void CANManager_Run(void) {

	CANManager_SendIgnition();

	CANManager_SendTurnSignal();

	CANManager_SendSpeed();

	CANManager_SendDrivingMode();
}

