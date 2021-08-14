#pragma once
#include "Building.h"

class CityHall : public Building
{
private:
	dImage *_door;

public:
	HRESULT init(float idX, int level = 1);
	void release();
	void update();
	void render();
};

