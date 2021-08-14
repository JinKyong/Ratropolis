#include "stdafx.h"
#include "CityHall.h"

HRESULT CityHall::init(float idX, int level)
{
	_bodyImage = IMAGEMANAGER->addDImage("cityHall", L"img/build/cityhall/Cityhall_1_0.png", 360, 410);
	_door = IMAGEMANAGER->addDImage("cityHall_door", L"img/build/cityHall/Door_Merchant.png", 100, 90);

	_x = idX;
	_y = CAMERAMANAGER->getBackScreenHeight() - 300;
	_space = _bodyImage->getWidth() / EACH_SPACE;
	_body = RectMake(_x * EACH_SPACE, _y - _bodyImage->getHeight(), _space * EACH_SPACE, _bodyImage->getHeight());

	_hp = 4;
	_level = level;

	_active = false;

	return S_OK;
}

void CityHall::release()
{
}

void CityHall::update()
{
}

void CityHall::render()
{
	_door->render((_x + _space / 2) * EACH_SPACE - _door->getWidth() / 2, _y - _door->getHeight() + 2);
	Building::render();
}
