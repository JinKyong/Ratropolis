#include "stdafx.h"
#include "Cursor.h"
#include "Player.h"
#include "Card.h"

HRESULT Cursor::init(Player* player)
{
	_player = player;

	_images[CURSOR_TYPE_DEFAULT] = IMAGEMANAGER->addDImage("cursor_default",
		L"img/component/cursor/Cursor_Default.png", 32, 32);
	_images[CURSOR_TYPE_CLICK] = IMAGEMANAGER->addDImage("cursor_click",
		L"img/component/cursor/Cursor_Click.png", 32, 32);
	_images[CURSOR_TYPE_GRAB] = IMAGEMANAGER->addDImage("cursor_grab",
		L"img/component/cursor/Cursor_Grab.png", 32, 32);
	_images[CURSOR_TYPE_ATTACK] = IMAGEMANAGER->addDImage("cursor_attack",
		L"img/component/cursor/Cursor_Attack.png", 32, 32);
	_images[CURSOR_TYPE_MINING] = IMAGEMANAGER->addDImage("cursor_mining",
		L"img/component/cursor/Cursor_Mining.png", 32, 32);

	_currentImage = _images[CURSOR_TYPE_DEFAULT];

	updatePosition(_ptMouse.x, _ptMouse.y);

	return S_OK;
}

void Cursor::release()
{
}

void Cursor::update()
{
	//Mouse
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON)) {
		//메뉴 열려있을때와 아닐때
		if (UIMANAGER->getOpen()) {

		}
		else {
			CAMERAMANAGER->resetZoom();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		changeCursor(CURSOR_TYPE_CLICK);

		//메뉴 열려있을때와 아닐때
		if (UIMANAGER->getOpen()) {
			if (UIMANAGER->getCurrentMenu()->getHide()) {
				if (COLLISIONMANAGER->selectedCard(DECKMANAGER->getCurrentDeck(), _x, _y))
					UIMANAGER->getCurrentMenu()->setHide(false);
				else
					UIMANAGER->getCurrentMenu()->setHide(true);
			}
		}
		else {
			COLLISIONMANAGER->buttonWithCursor();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {

		//메뉴 열려있을때와 아닐때
		if (UIMANAGER->getOpen()) {

		}
		else {
			if (COLLISIONMANAGER->grabbedCard())
				changeCursor(CURSOR_TYPE_GRAB);
			if (_player->getCard()) {
				_player->getCard()->setX(_ptMouse.x);
				_player->getCard()->setY(_ptMouse.y);
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		changeCursor(CURSOR_TYPE_DEFAULT);

		//메뉴 열려있을때와 아닐때
		if (UIMANAGER->getOpen()) {

		}
		else {
			if (_player->getCard()) {
				_x = _y = -1000;
				//충돌검사
				COLLISIONMANAGER->handsWithUseBox(_player->getCard());
				_player->setCard(NULL);
			}
		}
	}

}

void Cursor::render()
{
	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];

		swprintf_s(tmp, L"x : %f", _x);
		DTDMANAGER->printText(tmp, _x, _y - 120, 200, 50);

		swprintf_s(tmp, L"y : %f", _y);
		DTDMANAGER->printText(tmp, _x, _y - 100, 200, 50);

		swprintf_s(tmp, L"backX : %f", _backX);
		DTDMANAGER->printText(tmp, _x, _y - 80, 200, 50);

		swprintf_s(tmp, L"backY : %f", _backY);
		DTDMANAGER->printText(tmp, _x, _y - 60, 200, 50);

		DTDMANAGER->Rectangle(_body);
		DTDMANAGER->Rectangle(_backBody);
	}

	_currentImage->render(_x - _currentImage->getWidth() / 2, _y - _currentImage->getHeight() / 2);
}

void Cursor::updatePosition(float x, float y)
{
	_x = x;
	_y = y;
	_body = RectMakeCenter(_x, _y, 50, 100);

	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	float zoom = CAMERAMANAGER->getZoom();

	_backX = _x / zoom + screen.left;
	_backY = _y / zoom + screen.top;
	_backBody = RectMakeCenter(_backX, _backY, 50, 100);
}

void Cursor::changeCursor(CURSOR_TYPE type)
{
	if (type >= END_CURSOR_TYPE) return;
	if (_currentImage = _images[type]) return;

	_currentImage = _images[type];
}
