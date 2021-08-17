#include "stdafx.h"
#include "Citizen.h"

Citizen::Citizen()
{
	_image = IMAGEMANAGER->addDImage("citizen", L"img/object/NPC/Civilian_Blue_00.png", 512, 512);

	_bPart[BODY_PART_HEAD].position = dRectMake(0, 263, 180, 145);	//¸Ó¸®
	_bPart[BODY_PART_BODY].position = dRectMake(0, 135, 120, 120);	//¸ö
}

Citizen::~Citizen()
{
}