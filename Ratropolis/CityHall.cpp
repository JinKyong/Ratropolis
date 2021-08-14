#include "stdafx.h"
#include "CityHall.h"

CityHall::CityHall(int level)
{
	_bodyImage = IMAGEMANAGER->addDImage("cityHall", L"img/build/cityhall/Cityhall_1_0.png", 360, 410);
	_door = IMAGEMANAGER->addDImage("cityHall_door", L"img/build/cityHall/Door_1_0.png", 100, 90);

	_hp = 4;
	_level = level;

	_active = false;
}

CityHall::~CityHall()
{
}

void CityHall::render()
{
	_door->render((_idX + _space / 2) * EACH_SPACE - _door->getWidth() / 2, GROUND - _door->getHeight() + 2);
	Building::render();
}
