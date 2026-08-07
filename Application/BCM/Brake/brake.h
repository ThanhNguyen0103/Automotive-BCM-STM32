/*
 * brake.h
 *
 *  Created on: Jul 21, 2026
 *      Author: nguyz
 */

#ifndef APPLICATION_BRAKE_H_
#define APPLICATION_BRAKE_H_

#include "Common/types.h"

void Brake_Init(void);
void Brake_Run(void);
Brake_State_t Brake_GetState(void);

#endif /* APPLICATION_BRAKE_H_ */
