#include "stdafx.h"
#include "CardDict.h"

HRESULT CardDict::init()
{
	setCardImage();

	addCard(1, &CardDict::card1);
	addCard(31, &CardDict::card31);
	addCard(32, &CardDict::card32);

	return S_OK;
}

void CardDict::release()
{
}

void CardDict::addCard(int num, func f)
{
	_cardList.insert(make_pair(num, f));
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
	//500, 700
	IMAGEMANAGER->addDImage("economyFrame", L"img/card/frame/CardFrame1.png", 200, 280);
	IMAGEMANAGER->addDImage("millitaryFrame", L"img/card/frame/CardFrame2.png", 200, 280);
	IMAGEMANAGER->addDImage("buildFrame", L"img/card/frame/CardFrame3.png", 200, 280);
	IMAGEMANAGER->addDImage("techFrame", L"img/card/frame/CardFrame4.png", 200, 280);

	//404, 140
	IMAGEMANAGER->addDImage("nameTag", L"img/component/tooltip/Ribbon #2426.png", 162, 56);
}

void CardDict::registerCardGemImage()
{
	//32, 38
	IMAGEMANAGER->addDImage("card_rarity0", L"img/card/gem/Card_Rarity2_1.png", 13, 15);
	IMAGEMANAGER->addDImage("card_rarity1", L"img/card/gem/Card_Rarity2_2.png", 13, 15);
	IMAGEMANAGER->addDImage("card_rarity2", L"img/card/gem/Card_Rarity2_3.png", 13, 15);
	IMAGEMANAGER->addDImage("card_rarity3", L"img/card/gem/Card_Rarity2_4.png", 13, 15);
}

void CardDict::registerCardIlluste()
{
	for (int i = 0; i < 33; i++) {
		char key[128];
		WCHAR dir[128];

		sprintf_s(key, "illuste%d", i);
		swprintf_s(dir, L"img/card/illuste/illuste%d.png", i);

		//340, 250
		IMAGEMANAGER->addDImage(key, dir, 136, 100);
	}
}

void CardDict::registerCardCostImage()
{
	//70, 70
	IMAGEMANAGER->addDImage("cost_gold", L"img/card/cost/GoldFrame.png", 28, 28);
	IMAGEMANAGER->addDImage("cost_civil", L"img/card/cost/CostFrame.png", 28, 28);
	IMAGEMANAGER->addDImage("cost_ground", L"img/card/cost/GroundFrame.png", 28, 28);

	IMAGEMANAGER->addDImage("cost_sword", L"img/card/cost/Card2_Attack.png", 130, 250);
	IMAGEMANAGER->addDImage("cost_bow", L"img/card/cost/Card2_AttackBow.png", 193, 313);
	IMAGEMANAGER->addDImage("cost_assist", L"img/card/cost/Card2_Assist.png", 193, 313);
	IMAGEMANAGER->addDImage("cost_defense", L"img/card/cost/Card2_Deffense.png", 130, 135);
}
