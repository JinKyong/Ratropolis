#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init(float x)
{
	//_x = 40 * 90;
	_x = x;
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

}

void NPC::render()
{

}

void NPC::updatePosition()
{
	
}

void NPC::updateDirect()
{
	
}