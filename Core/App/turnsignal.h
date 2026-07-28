/*
 * turnsignal.h
 *
 *  Created on: Jul 27, 2026
 *      Author: nguyz
 */

#ifndef APP_TURNSIGNAL_H_
#define APP_TURNSIGNAL_H_

typedef enum {
	TURN_OFF = 0, TURN_LEFT, TURN_RIGHT, TURN_HAZARD
} TurnSignalState_t;

void TurnSignal_Init(void);
void TurnSignal_Run(void);
TurnSignalState_t TurnSignal_GetState(void);
#endif /* APP_TURNSIGNAL_H_ */
