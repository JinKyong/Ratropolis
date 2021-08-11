#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	_cursor[CURSOR_TYPE_DEFAULT] = IMAGEMANAGER->addDImage("cursor_default",
		L"img/player/cursor/Cursor_Default.png", 32, 32);
	_cursor[CURSOR_TYPE_CLICK] = IMAGEMANAGER->addDImage("cursor_click",
		L"img/player/cursor/Cursor_Click.png", 32, 32);
	_cursor[CURSOR_TYPE_GRAB] = IMAGEMANAGER->addDImage("cursor_grab",
		L"img/player/cursor/Cursor_Grab.png", 32, 32);
	_cursor[CURSOR_TYPE_ATTACK] = IMAGEMANAGER->addDImage("cursor_attack",
		L"img/player/cursor/Cursor_Attack.png", 32, 32);
	_cursor[CURSOR_TYPE_MINING] = IMAGEMANAGER->addDImage("cursor_mining",
		L"img/player/cursor/Cursor_Mining.png", 32, 32);

	_currentCursor = _cursor[CURSOR_TYPE_DEFAULT];

	_body = RectMakeCenter(_ptMouse.x, _ptMouse.y, 50, 100);

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	_x = _ptMouse.x;
	_y = _ptMouse.y;

	//testKey
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1)) {
		changeGold(-5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD2)) {
		changeGold(+5);
	}

	

	//조작키
	controlMouse();
	controlKeyboard();

	

	_body = RectMakeCenter(_ptMouse.x, _ptMouse.y, 50, 100);
}

void Player::render()
{

	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];
		D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

		swprintf_s(tmp, L"x : %f", _ptMouse.x);
		DTDMANAGER->printText(tmp, _ptMouse.x, _ptMouse.y - 120, 100, 50);

		swprintf_s(tmp, L"y : %f", _ptMouse.y);
		DTDMANAGER->printText(tmp, _ptMouse.x, _ptMouse.y - 100, 100, 50);

		swprintf_s(tmp, L"cameraX : %f", screen.left);
		DTDMANAGER->printText(tmp, _ptMouse.x, _ptMouse.y - 80, 200, 50);

		swprintf_s(tmp, L"cameraY : %f", screen.top);
		DTDMANAGER->printText(tmp, _ptMouse.x, _ptMouse.y - 60, 200, 50);

		DTDMANAGER->Rectangle(_body);
	}

	_currentCursor->render(_ptMouse.x - _currentCursor->getWidth() / 2,
		_ptMouse.y - _currentCursor->getHeight() / 2);
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

void Player::controlMouse()
{
	//Mouse
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
		CAMERAMANAGER->resetZoom();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		changeCursor(CURSOR_TYPE_CLICK);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		if (COLLISIONMANAGER->grabbedCard())
			changeCursor(CURSOR_TYPE_GRAB);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		changeCursor(CURSOR_TYPE_DEFAULT);
		if (_selectedCard) {
			_x = _y = -1000;
			//충돌검사
			COLLISIONMANAGER->handsWithUseBox(_selectedCard);
			_selectedCard = NULL;
		}
	}
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

void Player::changeCursor(CURSOR_TYPE type)
{
	if (type >= END_CURSOR_TYPE) return;
	if (_currentCursor = _cursor[type]) return;

	_currentCursor = _cursor[type];
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
