#pragma once
#include "Building.h"

class CityHall : public Building
{
private:
	dImage *_door;

public:
	CityHall(int level);
	~CityHall();

	void render();
};

