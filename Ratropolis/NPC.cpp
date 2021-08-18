#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init()
{
	//RIGHT
	_orderRight[0] = BODY_PART_LFOOT;
	_orderRight[1] = BODY_PART_RFOOT;
	_orderRight[2] = BODY_PART_LLEG;
	_orderRight[3] = BODY_PART_RLEG;
	_orderRight[4] = BODY_PART_TAIL;
	_orderRight[5] = BODY_PART_LARM;
	_orderRight[6] = BODY_PART_BODY;
	_orderRight[7] = BODY_PART_RARM;
	_orderRight[8] = BODY_PART_HEAD;


	//LEFT
	_orderLeft[0] = BODY_PART_RFOOT;
	_orderLeft[1] = BODY_PART_LFOOT;
	_orderLeft[2] = BODY_PART_RLEG;
	_orderLeft[3] = BODY_PART_LLEG;
	_orderLeft[4] = BODY_PART_TAIL;
	_orderLeft[5] = BODY_PART_RARM;
	_orderLeft[6] = BODY_PART_BODY;
	_orderLeft[7] = BODY_PART_LARM;
	_orderLeft[8] = BODY_PART_HEAD;


	_x = 40 * 90;
	_y = GROUND - 65 / 2;
	_body = RectMakeCenter(_x, _y, 35, 65);

	_direct = 0;

	return S_OK;
}

void NPC::release()
{
}

void NPC::update()
{
	//updateDirect();

	//RIGHT
	if (_direct == 0)
		moveRight();
	//LEFT
	else
		moveLeft();

	updatePosition();
}

void NPC::render()
{
	if (_direct == 0) {
		for (int i = 0; i < END_BODY_PART; i++) {
			int order = _orderRight[i];
			_image->render(_destBPart[order], _bPart[order].position);

			if (PRINTMANAGER->isDebug())
				DTDMANAGER->Rectangle(_destBPart[order]);
		}
	}
	else {
		for (int i = 0; i < END_BODY_PART; i++) {
			int order = _orderLeft[i];
			_image->render(_destBPart[order], _bPart[order].position);

			if (PRINTMANAGER->isDebug())
				DTDMANAGER->Rectangle(_destBPart[order]);
		}
	}
}

void NPC::updatePosition()
{
	//Ãæµ¹ RECT
	_body = RectMakeCenter(_x, _y, 35, 65);

	//BPART RECT
	_destBPart[BODY_PART_HEAD] = dRectMakeCenter(_x - 3, _y - 18, 45, 35); 
	_destBPart[BODY_PART_BODY] = dRectMakeCenter(_x, _y + 10, 30, 30);
	_destBPart[BODY_PART_RARM] = dRectMakeCenter(_x - 12, _y + 10, 10, 20);
	_destBPart[BODY_PART_LARM] = dRectMakeCenter(_x + 10, _y + 10, 10, 20);
}

void NPC::updateDirect()
{
	
}

void NPC::moveRight()
{
}

void NPC::moveLeft()
{
}
