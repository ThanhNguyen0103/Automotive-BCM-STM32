/*
 * canmanager.h
 *
 *  Created on: Jul 29, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_CANMANAGER_CAN_MANAGER_H_
#define APPLICATION_CANMANAGER_CAN_MANAGER_H_

void CANManager_Init(void);

void CANManager_Run(void);

void CANManager_SendIgnition(void);
void CANManager_SendSpeed(void);
void CANManager_SendTurnSignal(void);
void CANManager_SendDrivingMode(void);
void CANManager_SendCruiseControl(void);

#endif /* APPLICATION_CANMANAGER_CAN_MANAGER_H_ */
