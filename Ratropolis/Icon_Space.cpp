#include "stdafx.h"
#include "Icon_Space.h"

HRESULT Icon_Space::init(int value)
{
	_image = IMAGEMANAGER->findDImage("cost_space");

	_value = value;

	return S_OK;
}
