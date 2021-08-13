#include "stdafx.h"
#include "NameTag.h"
#include "Card.h"

HRESULT NameTag::init(LPCWCHAR name, int level)
{
	_image = IMAGEMANAGER->findDImage("nameTag");

	int len = lstrlenW(name);
	_name = new WCHAR[len + 1];
	lstrcpyW(_name, name);

	_level = level;

	if (_level >= 2)
		lstrcatW(_name, L" Lv.2");

	return S_OK;
}

void NameTag::render(float x, float y)
{
	_image->render(x - _image->getWidth() / 2, y - _image->getHeight() / 2 + 50);

	//text
	DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
	DTDMANAGER->printText(_name, x + 1, y + 1 + 40,
		_image->getWidth(), _image->getHeight(), 18, true, true);
	if (_level == 1)
		DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
	else
		DTDMANAGER->setBrushColor(ColorF(ColorF::SpringGreen));
	DTDMANAGER->printText(_name, x, y + 40,
		_image->getWidth(), _image->getHeight(), 18, true, true);

	DTDMANAGER->resetBrushColor();
}