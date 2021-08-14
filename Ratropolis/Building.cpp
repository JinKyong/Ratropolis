#include "stdafx.h"
#include "Building.h"

HRESULT Building::init(int idX)
{
	_idX = idX;
	_space = _bodyImage->getWidth() / EACH_SPACE;
	_body = RectMake(_idX * EACH_SPACE, GROUND - _bodyImage->getHeight(), _space * EACH_SPACE, _bodyImage->getHeight());

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
	_bodyImage->render(_idX * EACH_SPACE, GROUND - _bodyImage->getHeight());

	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];

		swprintf_s(tmp, L"idX : %d", _idX);
		DTDMANAGER->printText(tmp, _body.left, _body.top - 80, 200, 50);

		DTDMANAGER->Rectangle(_body);
	}
}
