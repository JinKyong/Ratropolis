#include "stdafx.h"
#include "Dictionary.h"

HRESULT Dictionary::init()
{
#pragma region cardInit
	registerCard();
	registerCardFrameImage();
	registerCardGemImage();
	registerCardIlluste();
	registerCardCostImage();
#pragma endregion

#pragma region buildingInit
	registerBuilding();
	registerBuildEffect();
#pragma endregion

#pragma region NPCInit

#pragma endregion



	return S_OK;
}

void Dictionary::release()
{
}

void Dictionary::addCard(int num, funcCard f)
{
	if (!f) return;

	_cardList.insert(make_pair(num, f));
}

Card * Dictionary::makeCard(int num, int level)
{
	cardIter find = _cardList.find(num);

	if (find == _cardList.end()) return NULL;
	
	return (this->*find->second)(level);
}

void Dictionary::addBuilding(int num, funcBuilding f)
{
	if (!f) return;

	_buildingList.insert(make_pair(num, f));
}

Building * Dictionary::makeBuilding(int num, int level)
{
	buildingIter find = _buildingList.find(num);

	if (find == _buildingList.end()) return NULL;

	return (this->*find->second)(level);
}

#pragma region Cards
void Dictionary::registerCard()
{
	addCard(1, &Dictionary::card1);
	addCard(3, &Dictionary::card3);
	addCard(18, &Dictionary::card18);
	addCard(31, &Dictionary::card31);
	addCard(32, &Dictionary::card32);
}

void Dictionary::registerCardFrameImage()
{
	//500, 700
	IMAGEMANAGER->addDImage("economyFrame", L"img/card/frame/CardFrame1.png", 200, 280);
	IMAGEMANAGER->addDImage("millitaryFrame", L"img/card/frame/CardFrame2.png", 200, 280);
	IMAGEMANAGER->addDImage("buildFrame", L"img/card/frame/CardFrame3.png", 200, 280);
	IMAGEMANAGER->addDImage("techFrame", L"img/card/frame/CardFrame4.png", 200, 280);

	//404, 140
	IMAGEMANAGER->addDImage("nameTag", L"img/component/tooltip/Ribbon #2426.png", 162, 56);
}

void Dictionary::registerCardGemImage()
{
	//32, 38
	IMAGEMANAGER->addDImage("card_rarity0", L"img/card/gem/Card_Rarity2_1.png", 13, 15);
	IMAGEMANAGER->addDImage("card_rarity1", L"img/card/gem/Card_Rarity2_2.png", 13, 15);
	IMAGEMANAGER->addDImage("card_rarity2", L"img/card/gem/Card_Rarity2_3.png", 13, 15);
	IMAGEMANAGER->addDImage("card_rarity3", L"img/card/gem/Card_Rarity2_4.png", 13, 15);
}

void Dictionary::registerCardIlluste()
{
	IMAGEMANAGER->addDImage("illuste1", L"img/card/illuste/illuste1.png", 136, 100);
	IMAGEMANAGER->addDImage("illuste3", L"img/card/illuste/illuste3.png", 136, 100);
	IMAGEMANAGER->addDImage("illuste18", L"img/card/illuste/illuste18.png", 136, 100);
	IMAGEMANAGER->addDImage("illuste31", L"img/card/illuste/illuste31.png", 136, 100);
	IMAGEMANAGER->addDImage("illuste32", L"img/card/illuste/illuste32.png", 136, 100);

	IMAGEMANAGER->addDImage("UI_illuste1", L"img/card/illuste/illuste1.png", 68, 50);
	IMAGEMANAGER->addDImage("UI_illuste3", L"img/card/illuste/illuste3.png", 68, 50);
	IMAGEMANAGER->addDImage("UI_illuste18", L"img/card/illuste/illuste18.png", 68, 50);
	IMAGEMANAGER->addDImage("UI_illuste31", L"img/card/illuste/illuste31.png", 68, 50);
	IMAGEMANAGER->addDImage("UI_illuste32", L"img/card/illuste/illuste32.png", 68, 50);

	//for (int i = 0; i < 33; i++) {
	//	char key[128];
	//	WCHAR dir[128];

	//	sprintf_s(key, "illuste%d", i);
	//	swprintf_s(dir, L"img/card/illuste/illuste%d.png", i);

	//	//340, 250
	//	IMAGEMANAGER->addDImage(key, dir, 136, 100);
	//	sprintf_s(key, "UI_illuste%d", i);
	//	IMAGEMANAGER->addDImage(key, dir, 68, 50);
	//}
}

void Dictionary::registerCardCostImage()
{
	//70, 70
	IMAGEMANAGER->addDImage("cost_gold", L"img/component/cost/GoldFrame.png", 28, 28);
	IMAGEMANAGER->addDImage("cost_civil", L"img/component/cost/CostFrame.png", 28, 28);
	IMAGEMANAGER->addDImage("cost_space", L"img/component/cost/GroundFrame.png", 28, 28);

	IMAGEMANAGER->addDImage("cost_sword", L"img/component/cost/Card2_Attack.png", 130, 250);
	IMAGEMANAGER->addDImage("cost_bow", L"img/component/cost/Card2_AttackBow.png", 193, 313);
	IMAGEMANAGER->addDImage("cost_assist", L"img/component/cost/Card2_Assist.png", 193, 313);
	IMAGEMANAGER->addDImage("cost_defense", L"img/component/cost/Card2_Deffense.png", 130, 135);
}
#pragma endregion

#pragma region Buildings

void Dictionary::registerBuilding()
{
	addBuilding(0, &Dictionary::cityHall);
	addBuilding(3, &Dictionary::building3);
	addBuilding(18, &Dictionary::building18);
}

void Dictionary::registerBuildEffect()
{
	IMAGEMANAGER->addDImage("buildSign", L"img/build/effect/Build_Effect.png", 60, 69);
	IMAGEMANAGER->addDImage("buildEffect1", L"img/build/effect/Build_Effect1.png", 90, 99);
	IMAGEMANAGER->addDImage("buildEffect2", L"img/build/effect/Build_Effect2.png", 180, 186);
	IMAGEMANAGER->addDImage("buildEffect3", L"img/build/effect/Build_Effect3.png", 270, 237);
	IMAGEMANAGER->addDImage("buildEffect4", L"img/build/effect/Build_Effect4.png", 360, 326);
}

#pragma endregion

#pragma region NPCs

#pragma endregion

