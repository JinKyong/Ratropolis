#include "stdafx.h"
#include "Building3.h"

HRESULT Building3::init(float idX, int level)
{
	if(level == 1)
		_bodyImage = IMAGEMANAGER->addDImage("building3_1", L"img/build/Build3_1_0.png", 90, 85);
	else
		_bodyImage = IMAGEMANAGER->addDImage("building3_2", L"img/build/Build3_1_0.png", 90, 85);

	_x = idX;
	_y = CAMERAMANAGER->getBackScreenHeight() - 300;
	_space = _bodyImage->getWidth() / EACH_SPACE;
	_body = RectMake(_x * EACH_SPACE, _y - _bodyImage->getHeight(), _space * EACH_SPACE, _bodyImage->getHeight());

	_hp = 3;
	_level = level;

	_active = false;

	return S_OK;
}

void Building3::release()
{
}

void Building3::update()
{
}

void Building3::render()
{
	Building::render();
}
