#include "stdafx.h"
#include "Icon_Civil.h"

HRESULT Icon_Civil::init(int value)
{
	_image = IMAGEMANAGER->findDImage("cost_civil");

	_value = value;

	return S_OK;
}
