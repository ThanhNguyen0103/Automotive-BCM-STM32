/*
 * turnsignal.c
 *
 *  Created on: Jul 27, 2026
 *      Author: nguyz
 */

#include "Drivers/LED/led.h"
#include "Drivers/BUTTON/button.h"
#include "turnsignal.h"

#define BLINK_PERIOD_MS 500

static Button_t button_left;
static Button_t button_right;
static Button_t button_hazard;
static Led_t led_left;
static Led_t led_right;
static TurnSignalState_t turnState = TURN_OFF;

static uint32_t lastBlinkTick = 0;
static bool blinkState = false;

void TurnSignal_Init(void) {
	Button_Init(&button_left, GPIOB, GPIO_PIN_12);
	Button_Init(&button_right, GPIOB, GPIO_PIN_13);
	Button_Init(&button_hazard, GPIOB, GPIO_PIN_14);
	//
	Led_Init(&led_left, GPIOA, GPIO_PIN_1);
	Led_Init(&led_right, GPIOA, GPIO_PIN_2);
}

void TurnSignal_Run(void) {

	Button_Update(&button_hazard);
	Button_Update(&button_left);
	Button_Update(&button_right);
	if (Button_IsPressed(&button_left)) {
		turnState = (turnState == TURN_LEFT) ? TURN_OFF : TURN_LEFT;
	} else if (Button_IsPressed(&button_right)) {
		turnState = (turnState == TURN_RIGHT) ? TURN_OFF : TURN_RIGHT;
	} else if (Button_IsPressed(&button_hazard)) {
		turnState = (turnState == TURN_HAZARD) ? TURN_OFF : TURN_HAZARD;
	}

	switch (turnState) {
	case TURN_RIGHT:
		Led_Blink(&led_right);
		Led_Off(&led_left);
		break;
	case TURN_LEFT:
		Led_Blink(&led_left);
		Led_Off(&led_right);
		break;
	case TURN_HAZARD:
		if (HAL_GetTick() - lastBlinkTick > BLINK_PERIOD_MS) {
			lastBlinkTick = HAL_GetTick();
			blinkState = !blinkState;
			if (blinkState) {
				Led_On(&led_left);
				Led_On(&led_right);
			} else {
				Led_Off(&led_left);
				Led_Off(&led_right);
			}
		}
		break;
	default:
		Led_Off(&led_left);
		Led_Off(&led_right);
		break;
	}

}

TurnSignalState_t TurnSignal_GetState(void) {
	return turnState;
}

