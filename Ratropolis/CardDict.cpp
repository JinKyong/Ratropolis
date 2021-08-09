#include "stdafx.h"
#include "CardDict.h"

HRESULT CardDict::init()
{
	setCardImage();

	return S_OK;
}

void CardDict::release()
{
}

void CardDict::addCard(func f)
{
}

void CardDict::setCardImage()
{
	registerCardFrameImage();
	registerCardGemImage();
	registerCardIlluste();
	registerCardCostImage();
}

void CardDict::registerCardFrameImage()
{
	IMAGEMANAGER->addDImage("economyFrame", L"img/card/frame/CardFrame1.png", 500, 700);
	IMAGEMANAGER->addDImage("millitaryFrame", L"img/card/frame/CardFrame2.png", 500, 700);
	IMAGEMANAGER->addDImage("buildFrame", L"img/card/frame/CardFrame3.png", 500, 700);
	IMAGEMANAGER->addDImage("techFrame", L"img/card/frame/CardFrame4.png", 500, 700);

	IMAGEMANAGER->addDImage("nameTag", L"img/card/frame/Ribbon #2426.png", 404, 140);
}

void CardDict::registerCardGemImage()
{
	IMAGEMANAGER->addDImage("card_rarity0", L"img/card/gem/Card_Rarity2_1.png", 32, 38);
	IMAGEMANAGER->addDImage("card_rarity1", L"img/card/gem/Card_Rarity2_2.png", 32, 38);
	IMAGEMANAGER->addDImage("card_rarity2", L"img/card/gem/Card_Rarity2_3.png", 32, 38);
	IMAGEMANAGER->addDImage("card_rarity3", L"img/card/gem/Card_Rarity2_4.png", 32, 38);
}

void CardDict::registerCardIlluste()
{
	//for(int i=0; i)
}

void CardDict::registerCardCostImage()
{
	IMAGEMANAGER->addDImage("cost_gold", L"img/card/cost/GoldFrame.png", 70, 70);
	IMAGEMANAGER->addDImage("cost_civil", L"img/card/cost/CostFrame.png", 70, 70);
	IMAGEMANAGER->addDImage("cost_ground", L"img/card/cost/GroundFrame.png", 70, 70);

	IMAGEMANAGER->addDImage("cost_sword", L"img/card/cost/Card2_Attack.png", 130, 250);
	IMAGEMANAGER->addDImage("cost_bow", L"img/card/cost/Card2_AttackBow.png", 193, 313);
	IMAGEMANAGER->addDImage("cost_assist", L"img/card/cost/Card2_Assist.png", 193, 313);
	IMAGEMANAGER->addDImage("cost_defense", L"img/card/cost/Card2_Deffense.png", 130, 135);
}
