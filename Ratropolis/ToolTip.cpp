#include "stdafx.h"
#include "ToolTip.h"

HRESULT ToolTip::init()
{
	_frame = IMAGEMANAGER->addDImage("toolTipFrame", L"img/component/tooltip/UI_CardToolTip.png", 170, 140);

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
