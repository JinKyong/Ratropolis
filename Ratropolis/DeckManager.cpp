#include "stdafx.h"
#include "DeckManager.h"

HRESULT DeckManager::init()
{
	//카드 이미지 등록
	registerCardFrameImage();
	registerCardGemImage();
	registerCardIlluste();
	registerCardCostImage();

	return S_OK;
}

void DeckManager::release()
{
}

void DeckManager::update()
{
}

void DeckManager::render()
{
	//각도 계산 잘해야함;
}

void DeckManager::shuffle()
{
	int index1, index2;
	Card* tmp;

	for (int i = 0; i < 1000; i++) {
		index1 = RND->getInt(_currentDeck.size());
		index2 = RND->getInt(_currentDeck.size());

		tmp = _currentDeck[index1];
		_currentDeck[index1] = _currentDeck[index2];
		_currentDeck[index2] = tmp;
	}
}

void DeckManager::registerCardFrameImage()
{
	IMAGEMANAGER->addDImage("economyFrame", L"img/card/frame/CardFrame1.png", 500, 700);
	IMAGEMANAGER->addDImage("millitaryFrame", L"img/card/frame/CardFrame2.png", 500, 700);
	IMAGEMANAGER->addDImage("buildFrame", L"img/card/frame/CardFrame3.png", 500, 700);
	IMAGEMANAGER->addDImage("techFrame", L"img/card/frame/CardFrame4.png", 500, 700);

	IMAGEMANAGER->addDImage("nameTag", L"img/card/frame/Ribbon #2426.png", 404, 140);
}

void DeckManager::registerCardGemImage()
{
	IMAGEMANAGER->addDImage("card_rarity0", L"img/card/gem/Card_Rarity2_1.png", 32, 38);
	IMAGEMANAGER->addDImage("card_rarity1", L"img/card/gem/Card_Rarity2_2.png", 32, 38);
	IMAGEMANAGER->addDImage("card_rarity2", L"img/card/gem/Card_Rarity2_3.png", 32, 38);
	IMAGEMANAGER->addDImage("card_rarity3", L"img/card/gem/Card_Rarity2_4.png", 32, 38);
}

void DeckManager::registerCardIlluste()
{
}

void DeckManager::registerCardCostImage()
{
	IMAGEMANAGER->addDImage("cost_gold", L"img/card/cost/GoldFrame.png", 70, 70);
	IMAGEMANAGER->addDImage("cost_civil", L"img/card/cost/CostFrame.png", 70, 70);
	IMAGEMANAGER->addDImage("cost_ground", L"img/card/cost/GroundFrame.png", 70, 70);
}
