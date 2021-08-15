#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	_cursor = new Cursor;
	_cursor->init(this);

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	//testKey
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1)) {
		changeGold(-5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD2)) {
		changeGold(+5);
	}

	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 5) {
		changeGold(_defaultStat.tax);
		_count = 0;
	}
	

	//조작키
	//controlMouse();
	_cursor->updatePosition(_ptMouse.x, _ptMouse.y);
	_cursor->update();
	controlKeyboard();
}

void Player::render()
{
	_cursor->render();
}

void Player::playGame()
{
	//기본 스탯 설정
	_defaultStat.gold = 70;
	_defaultStat.prize = 0;
	_defaultStat.tax = 5;
	_defaultStat.currentCivil = 5;
	_defaultStat.maxCivil = 5;
	_defaultStat.wave = 1;

	//지도자 레벨
	_level = 1;

	_selectedCard = NULL;

	_count = 0;
}

void Player::controlKeyboard()
{
	//Keyboard
	if (KEYMANAGER->isStayKeyDown('D')) {
		_camX += 10;
	}
	if (KEYMANAGER->isStayKeyDown('A')) {
		_camX -= 10;
	}



	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		if(!_selectedCard)
			DECKMANAGER->drawCard();
	}
}

void Player::changeGold(int num)
{
	_defaultStat.gold += num;

	if (_defaultStat.gold >= 99999)
		_defaultStat.gold = 99999;
}

void Player::changePrize(int num)
{
	_defaultStat.prize += num;

	if (_defaultStat.prize >= 99999)
		_defaultStat.prize = 99999;
}

void Player::changeTax(int num)
{
	_defaultStat.tax += num;

	if (_defaultStat.tax >= 99999)
		_defaultStat.tax = 99999;
}

void Player::changeCivil(int num)
{
	_defaultStat.currentCivil += num;

	if (_defaultStat.currentCivil >= _defaultStat.maxCivil)
		_defaultStat.currentCivil = _defaultStat.maxCivil;
}

void Player::changeMaxCivil(int num)
{
	_defaultStat.maxCivil += num;

	if (_defaultStat.maxCivil >= 200)
		_defaultStat.maxCivil = 200;

	changeCivil(num);
}

void Player::changeCard(Card * card)
{
	if (_selectedCard == card) return;

	_selectedCard = card;

	if (_selectedCard->getCardStat()->type == CARD_TYPE_BUILD)
		GAMEMANAGER->getBuildManager()->grabBcard();
}
