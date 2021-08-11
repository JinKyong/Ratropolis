#include "stdafx.h"
#include "NameTag.h"

HRESULT NameTag::init(LPCWCHAR name)
{
	_image = IMAGEMANAGER->findDImage("nameTag");

	int len = lstrlenW(name);
	_name = new WCHAR[len + 1];
	lstrcpyW(_name, name);

	return S_OK;
}

void NameTag::render(float x, float y)
{
	_image->render(x - _image->getWidth() / 2, y - _image->getHeight() / 2 + 50);

	//text
	DTDMANAGER->printText(_name, x, y + 40,
		_image->getWidth(), _image->getHeight(), 18, true);
}
