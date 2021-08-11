#include "stdafx.h"
#include "Icon_Gold.h"

HRESULT Icon_Gold::init(int value)
{
	_image = IMAGEMANAGER->findDImage("cost_gold");

	_value = value;

	return S_OK;
}
