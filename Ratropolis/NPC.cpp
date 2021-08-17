#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init()
{
	_x = 40 * 90;
	_y = GROUND - 65 / 2;
	_body = RectMakeCenter(_x, _y, 40, 65);

	_direct = 0;

	return S_OK;
}

void NPC::release()
{
}

void NPC::update()
{
	//RIGHT
	if (_direct == 0)
		moveRight();
	//LEFT
	else
		moveLeft();

	_body = RectMakeCenter(_x, _y, 35, 65);
}

void NPC::render()
{
	//body
	D2D1_RECT_F dest = dRectMakeCenter(_x, _y + 10, 30, 30);
	_image->render(dest, _bPart[BODY_PART_BODY].position);
	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(dest);

	//head
	dest = dRectMakeCenter(_x - 3, _y - 18, 45, 35);
	_image->render(dest, _bPart[BODY_PART_HEAD].position);
	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(dest);

	//R_Arm
	dest = dRectMakeCenter(_x - 12, _y + 10, 10, 20);
	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(dest);

	//L_Arm
	dest = dRectMakeCenter(_x + 10, _y + 10, 10, 20);
	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(dest);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(_body);
}

void NPC::moveRight()
{
}

void NPC::moveLeft()
{
}
