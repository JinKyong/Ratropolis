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


	//세금 징수 쓰레드
	CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		threadCollectTax,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		NULL,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);
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



	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		DECKMANAGER->drawCard();
}

void Player::changeGold(int num)
{
	_defaultStat.gold += num;

	if (_defaultStat.gold >= 99999)
		_defaultStat.gold = 99999;
}

void Player::changeCivil(int num)
{
	_defaultStat.currentCivil += num;

	if (_defaultStat.currentCivil >= 200)
		_defaultStat.currentCivil = 200;
}

void Player::changeMaxCivil(int num)
{
	_defaultStat.maxCivil += num;

	if (_defaultStat.maxCivil >= 200)
		_defaultStat.maxCivil = 200;
}

void Player::changeCard(Card * card)
{
	if (_selectedCard == card) return;

	_selectedCard = card;
}

DWORD Player::threadCollectTax(LPVOID lpParameter)
{
	Player* playerHelper = (Player*)lpParameter;

	while (1) {
		//5초마다 세금 징수
		Sleep(5000);

		playerHelper->changeGold(playerHelper->getDefaultStat().tax);
	}

	return 0;
}
