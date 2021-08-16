#include "stdafx.h"
#include "Building3.h"

Building3::Building3(int level)
{
	//건물 이미지
	if (level == 1)
		_bodyImage = IMAGEMANAGER->addDImage("building3_1", L"img/build/Build3_1_0.png", 90, 85);
	else
		_bodyImage = IMAGEMANAGER->addDImage("building3_2", L"img/build/Build3_2_0.png", 90, 116); 

	_space = _bodyImage->getWidth() / EACH_SPACE;
	_hp = 3;
	_level = level;

	_active = false;
}

Building3::~Building3()
{
}