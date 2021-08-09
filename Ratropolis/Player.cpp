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

	_x = _ptMouse.x;
	_y = _ptMouse.y;

	_body = RectMakeCenter(_x, _y, 50, 100);

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	if (KEYMANAGER->isStayKeyDown('D')) {
		_camX += 10;
	}
	if (KEYMANAGER->isStayKeyDown('A')) {
		_camX -= 10;
	}



	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
		CAMERAMANAGER->resetZoom();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		DECKMANAGER->drawCard();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		_currentCursor = _cursor[CURSOR_TYPE_CLICK];

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		_currentCursor = _cursor[CURSOR_TYPE_DEFAULT];




	_x = _ptMouse.x;
	_y = _ptMouse.y;

	_body = RectMakeCenter(_x, _y, 50, 100);
}

void Player::render()
{
	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_UI);

	DTDMANAGER->beginDraw(false);

	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];
		D2D1_RECT_F screen = CAMERAMANAGER->getScreen();

		swprintf_s(tmp, L"x : %f", _x);
		DTDMANAGER->printText(tmp, _x, _y - 120, 100, 50);

		swprintf_s(tmp, L"y : %f", _y);
		DTDMANAGER->printText(tmp, _x, _y - 100, 100, 50);

		swprintf_s(tmp, L"cameraX : %f", screen.left);
		DTDMANAGER->printText(tmp, _x, _y - 80, 200, 50);

		swprintf_s(tmp, L"cameraY : %f", screen.top);
		DTDMANAGER->printText(tmp, _x, _y - 60, 200, 50);

		DTDMANAGER->Rectangle(_body);
	}

	_currentCursor->render(_x - _currentCursor->getWidth() / 2, 
		_y - _currentCursor->getHeight() / 2);

	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}

void Player::playGame()
{
	//�⺻ ���� ����
	_defaultStat.gold = 70;
	_defaultStat.prize = 0;
	_defaultStat.tax = 5;
	_defaultStat.currentCivil = 5;
	_defaultStat.maxCivil = 5;
	_defaultStat.wave = 1;

	//������ ����
	_level = 1;


	//���� ¡�� ������
	CreateThread(
		NULL,			//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,			//�������� ����ũ��(NULL�� �θ� ���ξ�����)
		threadCollectTax,	//����� �Լ�
		this,			//������ �Ű�����(this�� ������ �� Ŭ����)
		NULL,			//������ Ư��(��ٸ��� �ٷν�������(NULL))
		NULL			//������ ���� �� �������� ID �Ѱ���
	);
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

DWORD Player::threadCollectTax(LPVOID lpParameter)
{
	Player* playerHelper = (Player*)lpParameter;

	while (1) {
		//5�ʸ��� ���� ¡��
		Sleep(5000);

		playerHelper->changeGold(playerHelper->getDefaultStat().tax);
	}

	return 0;
}
