#pragma once

typedef struct tagButton {
	dImage* icon;

	float x, y;
	RECT body;

	bool activate;
	bool selected;
}BUTTON, *PBUTTON;