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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		_currentCursor = _cursor[CURSOR_TYPE_CLICK];

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		_currentCursor = _cursor[CURSOR_TYPE_DEFAULT];


	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	float zoom = CAMERAMANAGER->getZoom();

	_x = _ptMouse.x / zoom + screen.left;
	_y = _ptMouse.y / zoom + screen.top;

	_body = RectMakeCenter(_x, _y, 50, 100);
}

void Player::render()
{
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
}
