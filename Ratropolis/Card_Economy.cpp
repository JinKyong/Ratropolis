#include "stdafx.h"
#include "Card_Economy.h"
#include "Player.h"

HRESULT Card_Economy::init()
{
	Card::init();

	//경제 카드
	_cardStat.type = CARD_TYPE_ECONOMY;

	//이미지 할당
	_frame = IMAGEMANAGER->findDImage("economyFrame");

	char tmp[128];
	sprintf_s(tmp, "card_rarity%d", _cardStat.rarity);
	_gem = IMAGEMANAGER->findDImage(tmp);

	sprintf_s(tmp, "illuste%d", _cardStat.number);
	_illuste = IMAGEMANAGER->findDImage(tmp);

	_nameTag = IMAGEMANAGER->findDImage("nameTag");
	_mainCost = IMAGEMANAGER->findDImage("cost_gold");
	_subCost = IMAGEMANAGER->findDImage("cost_civil");

	return S_OK;
}

void Card_Economy::release()
{
	Card::release();
}

void Card_Economy::update()
{
	Card::update();

	if (_cardStat.mainCost <= _player->getDefaultStat().gold &&
		_cardStat.subCost <= _player->getDefaultStat().currentCivil)
		_usable = true;
	else
		_usable = false;
}

void Card_Economy::render()
{
	if(_select)
		DTDMANAGER->setScale(2.0, 2.0, _x, _y);

	Card::render();

	//이미지
	_illuste->render(_x - _illuste->getWidth() / 2, _y - _illuste->getHeight() / 2 - 40);
	_frame->render(_x - _frame->getWidth() / 2, _y - _frame->getHeight() / 2);
	_gem->render(_x - _gem->getWidth() / 2, _y - _gem->getHeight() / 2 + 22);

	//이름태그 및 코스트(+ 스탯)
	_nameTag->render(_x - _nameTag->getWidth() / 2, _y - CARDHEIGHT / 2 + 10);
	_mainCost->render(_x - CARDWIDTH / 2 - _mainCost->getWidth() / 2 + 16,
		_y - CARDHEIGHT / 2 - _mainCost->getHeight() / 2 + 22);
	if (_cardStat.subCost > 0)
		_subCost->render(_x + CARDWIDTH / 2 - _subCost->getWidth() / 2 - 16,
			_y - CARDHEIGHT / 2 - _subCost->getHeight() / 2 + 22);


	//텍스트
	D2D1_RECT_F tmpRect = dRectMakeCenter(_x, _y + 62, 120, 60);
	DTDMANAGER->printText(_cardStat.desc.c_str(), tmpRect, 10, true);

	//디버깅
	if (PRINTMANAGER->isDebug()) {
		DTDMANAGER->Rectangle(_body);
		WCHAR tmp[128];
		swprintf_s(tmp, L"x : %f", _x);
		DTDMANAGER->printText(tmp, _x, _body.top, CARDWIDTH, 20, 10);
		DTDMANAGER->Rectangle(tmpRect);
	}

	DTDMANAGER->setBrushColor(ColorF(ColorF::White));
	DTDMANAGER->printText(_cardStat.name.c_str(), _x, _y - CARDHEIGHT / 2 + 25,
		_nameTag->getWidth(), _nameTag->getHeight(), 18, true);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", _cardStat.mainCost);
	DTDMANAGER->printText(tmp, _x - CARDWIDTH / 2 + 16, _y - CARDHEIGHT / 2 + 22,
		_mainCost->getWidth(), _mainCost->getHeight(), 18, true);
	if (_cardStat.subCost > 0) {
		swprintf_s(tmp, L"%d", _cardStat.subCost);
		DTDMANAGER->printText(tmp, _x + CARDWIDTH / 2 - 16, _y - CARDHEIGHT / 2 + 22,
			_subCost->getWidth(), _subCost->getHeight(), 18, true);
	}

	DTDMANAGER->resetBrushColor();
	DTDMANAGER->resetTransform();
}

void Card_Economy::useCard()
{
	if (_usable) {
		_player->changeGold(-_cardStat.mainCost);
		_player->changeCivil(-_cardStat.subCost);
		DECKMANAGER->useCard(this);
	}
}