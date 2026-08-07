/*
 * ignition.h
 *
 *  Created on: Jul 4, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_IGNITION_H_
#define APPLICATION_IGNITION_H_

#include "Common/types.h"

void Ignition_Run(void);
void Ignition_Init(void);

IgnitionState_t Ignition_GetState(void);

#endif /* APPLICATION_IGNITION_H_ */
