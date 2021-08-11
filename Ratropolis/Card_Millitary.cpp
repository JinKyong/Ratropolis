#include "stdafx.h"
#include "Card_Millitary.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon.h"

HRESULT Card_Millitary::init()
{
	Card::init();

	//좌표
	_x = 5000;
	_y = 500;
	_body = RectMakeCenter(_x, _y, CARDWIDTH, CARDHEIGHT);


	//군사 카드
	_cardStat.type = CARD_TYPE_MILLITARY;



	//이미지 할당
	_frame = IMAGEMANAGER->findDImage("millitaryFrame");

	char tmp[128];
	sprintf_s(tmp, "card_rarity%d", _cardStat.rarity);
	_gem = IMAGEMANAGER->findDImage(tmp);

	sprintf_s(tmp, "illuste%d", _cardStat.number);
	_illuste = IMAGEMANAGER->findDImage(tmp);


	return S_OK;
}

void Card_Millitary::release()
{
	Card::release();
}

void Card_Millitary::update()
{
	Card::update();

	if (_cost->getValue() <= _player->getDefaultStat().gold) {
		if (_civilCost) {
			if (_civilCost->getValue() <= _player->getDefaultStat().currentCivil)
				_usable = true;
		}
		else
			_usable = true;
	}
	else
		_usable = false;
}

void Card_Millitary::render()
{
	if (_select)
		DTDMANAGER->setScale(2.0, 2.0, _x, _y);

	Card::render();

	//이미지
	_illuste->render(_x - _illuste->getWidth() / 2, _y - _illuste->getHeight() / 2 - 40);
	_frame->render(_x - _frame->getWidth() / 2, _y - _frame->getHeight() / 2);
	_gem->render(_x - _gem->getWidth() / 2, _y - _gem->getHeight() / 2 + 22);

	//이름태그 및 코스트(+ 스탯)
	_name->render(_x, _y - _frame->getHeight() / 2);
	_cost->render(_x - CARDWIDTH / 2 + 16, _y - CARDHEIGHT / 2 + 22);
	if (_civilCost)
		_civilCost->render(_x + CARDWIDTH / 2 - 16, _y - CARDHEIGHT / 2 + 22);


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

	DTDMANAGER->resetTransform();
}

void Card_Millitary::useCard()
{
	//cost
	_player->changeGold(-_cost->getValue());
	if (_civilCost)
		_player->changeCivil(-_civilCost->getValue());

	DECKMANAGER->useCard(this);
}
