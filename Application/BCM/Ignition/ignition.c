/*
 * ignition.c
 *
 *  Created on: Jul 4, 2026
 *      Author: nguyz
 */

#include "Drivers/BUTTON/button.h"
#include "ignition.h"

static IgnitionState_t ignitionState;
static Button_t ignitionButton;
void Ignition_Init(void) {
	ignitionState = IGNITION_OFF;
	Button_Init(&ignitionButton, GPIOB, GPIO_PIN_15);
}
IgnitionState_t Ignition_GetState(void) {
	return ignitionState;
}

void Ignition_Run(void) {
	Button_Update(&ignitionButton);
	if (Button_IsPressed(&ignitionButton)) {
		ignitionState =
				(ignitionState == IGNITION_OFF) ? IGNITION_ON : IGNITION_OFF;

	}

}
