#include "stdafx.h"
#include "ToolTip.h"

HRESULT ToolTip::init(LPCWCHAR name, LPCWCHAR desc)
{
	_frame = IMAGEMANAGER->addDImage("toolTipFrame", L"img/component/tooltip/UI_CardToolTip.png", 170, 140);


	//이름과 설명
	int len = lstrlenW(name);
	_name = new WCHAR[len + 1];
	lstrcpyW(_name, name);

	len = lstrlenW(desc);
	_desc = new WCHAR[len + 1];
	lstrcpyW(_desc, desc);

	return S_OK;
}

void ToolTip::release()
{
}

void ToolTip::update()
{
}

void ToolTip::render(float x, float y)
{
	_frame->render(x, y);

	D2D1_RECT_F tmpRECT = dRectMake(x + 10, y + 8, _frame->getWidth() - 25, _frame->getHeight() - 25);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(tmpRECT);


	DTDMANAGER->setBrushColor(ColorF(ColorF::Red));
	DTDMANAGER->printText(_name, tmpRECT, 20);
	DTDMANAGER->resetBrushColor();
	
	tmpRECT.top += 20;
	DTDMANAGER->printText(_desc, tmpRECT, 20);
}
