#pragma once

typedef struct tagButton {
	dImage* icon;

	float x, y;
	RECT body;

	bool activate;
}BUTTON, *PBUTTON;