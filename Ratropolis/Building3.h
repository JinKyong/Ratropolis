#pragma once
#include "Building.h"

class Building3 : public Building
{
public:
	HRESULT init(float idX, int level = 1);
	void release();
	void update();
	void render();
};

