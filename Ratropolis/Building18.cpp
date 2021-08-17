#include "stdafx.h"
#include "Building18.h"

Building18::Building18(int level)
{
	//건물 이미지
	if (level == 1)
		_bodyImage = IMAGEMANAGER->addDImage("building18_1", L"img/build/Build18_1_0.png", 180, 160);
	else
		_bodyImage = IMAGEMANAGER->addDImage("building18_2", L"img/build/Build18_2_0.png", 180, 160);

	_space = 2;
	_hp = 400 + (level - 1) * 200;
	_level = level;

	_active = false;
}

Building18::~Building18()
{
}
