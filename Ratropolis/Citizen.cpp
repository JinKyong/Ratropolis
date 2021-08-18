#include "stdafx.h"
#include "Citizen.h"

Citizen::Citizen()
{
	_image = IMAGEMANAGER->addDImage("citizen", L"img/object/NPC/Civilian_Blue_00.png", 512, 512);

	//ÀÌ¹ÌÁö¿¡¼­ À§Ä¡ ¼³Á¤(D2D1_RECT_F)
	_bPart[BODY_PART_HEAD].position = dRectMake(0, 263, 180, 145);	//¸Ó¸®
	_bPart[BODY_PART_BODY].position = dRectMake(0, 135, 120, 120);	//¸ö
	_bPart[BODY_PART_RARM].position = dRectMake(270, 300, 30, 30);	//¿À¸¥ÆÈ
	_bPart[BODY_PART_LARM].position = dRectMake(60, 100, 30, 30);	//¿ÞÆÈ
}

Citizen::~Citizen()
{
}