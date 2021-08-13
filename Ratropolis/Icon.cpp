#include "stdafx.h"
#include "Icon.h"

HRESULT Icon::init(int value)
{


	return S_OK;
}

void Icon::release()
{
}

void Icon::update()
{
}

void Icon::render(float x, float y)
{
	_image->render(x - _image->getWidth() / 2, y - _image->getHeight() / 2, 0.9);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", _value);

	DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
	DTDMANAGER->printText(tmp, x + 1, y + 1, _image->getWidth(), _image->getHeight(), 18, true, true);
	DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
	DTDMANAGER->printText(tmp, x, y, _image->getWidth(), _image->getHeight(), 18, true, true);

	DTDMANAGER->resetBrushColor();
}
