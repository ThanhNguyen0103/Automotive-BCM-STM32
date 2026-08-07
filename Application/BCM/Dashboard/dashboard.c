///*
// * dashboard.c
// *
// *  Created on: Jul 4, 2026
// *      Author: nguyz
// */
//

#include "dashboard.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "Drivers/CAN/can.h"
#include "Common/config.h"

static void Dashboard_UpdateDisplay(void);
static DashboardData_t dashboard;

void Dashboard_Init(void) {
	ssd1306_Init();
	ssd1306_Fill(Black);

	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("IGNITION:", Font_7x10, White);

	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString("MODE:", Font_7x10, White);

	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString("SPEED:", Font_7x10, White);

	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString("Cruise:", Font_7x10, White);

	ssd1306_SetCursor(0, 40);
	ssd1306_WriteString("Signal:", Font_7x10, White);

	ssd1306_UpdateScreen();
}

void Dashboard_Run(void) {

	CAN_Frame_t frame;

	while (CAN_Receive(&frame)) {
		switch (frame.id) {
		case CAN_ID_IGNITION:
			dashboard.ignition = frame.data[0];
			break;

		case CAN_ID_MODE:
			dashboard.mode = frame.data[0];
			break;

		case CAN_ID_SPEED:
			dashboard.speed = frame.data[0];
			break;

		case CAN_ID_TURNSIGNAL:
			dashboard.signal = frame.data[0];
			break;
		}
	}
	Dashboard_UpdateDisplay();

}
static void Dashboard_UpdateDisplay(void) {
	char str[10];

	ssd1306_SetCursor(80, 0);
	ssd1306_WriteString(dashboard.ignition == IGNITION_ON ? "ON " : "OFF",
			Font_7x10, White);

	ssd1306_SetCursor(80, 10);
	ssd1306_WriteString(dashboard.mode == ECO_MODE ? "ECO  " : "SPORT",
			Font_7x10, White);

	sprintf(str, "%3d", dashboard.speed);

	ssd1306_SetCursor(80, 20);
	ssd1306_WriteString(str, Font_7x10, White);

	ssd1306_SetCursor(80, 40);

	switch (dashboard.signal) {
	case TURN_LEFT:
		ssd1306_WriteString("LEFT ", Font_7x10, White);
		break;

	case TURN_RIGHT:
		ssd1306_WriteString("RIGHT", Font_7x10, White);
		break;

	case TURN_HAZARD:
		ssd1306_WriteString("BOTH ", Font_7x10, White);
		break;

	default:
		ssd1306_WriteString("OFF  ", Font_7x10, White);
		break;
	}

	ssd1306_UpdateScreen();
}
