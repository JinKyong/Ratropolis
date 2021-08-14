#include "stdafx.h"
#include "Building.h"

HRESULT Building::init(float idX, int level)
{

	return S_OK;
}

void Building::release()
{
}

void Building::update()
{
}

void Building::render()
{
	_bodyImage->render(_x * EACH_SPACE, _y - _bodyImage->getHeight());

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_body);
}
