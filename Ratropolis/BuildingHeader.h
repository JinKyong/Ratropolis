#pragma once
#include "Building.h"

typedef struct tagSpace {
	int idX;
	RECT body;
	bool empty;

	tagSpace(int i) {
		idX = i;
		body = RectMake(idX * 90, GROUND - 120, 90, 120);
		empty = false;
	}
}SPACE, *PSPACE;

#include "CityHall.h"
#include "Building3.h"