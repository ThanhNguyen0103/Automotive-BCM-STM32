/*
 * brake.c
 *
 *  Created on: Jul 21, 2026
 *      Author: nguyz
 */

#include "Drivers/BUTTON/button.h"
#include "Drivers/LED/led.h"
#include "brake.h"

static Button_t brakeButton;
static Brake_State_t brakeState;
static Led_t ledBrake;

void Brake_Init(void) {
	brakeState = BRAKE_OFF;
	Button_Init(&brakeButton, GPIOB, GPIO_PIN_1);
	Led_Init(&ledBrake, GPIOA, GPIO_PIN_3);
}
void Brake_Run(void) {
	Button_Update(&brakeButton);
	if (Button_IsHolding(&brakeButton)) {
		brakeState = BRAKE_ON;
		Led_On(&ledBrake);
	} else {
		brakeState = BRAKE_OFF;
		Led_Off(&ledBrake);
	}

}

Brake_State_t Brake_GetState(void) {
	return brakeState;
}

