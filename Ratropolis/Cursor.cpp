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
	if (UIMANAGER->getOpen())
		controlMouseUI();
	else
		controlMouse();

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

void Cursor::controlMouse()
{
	//not UI Open
	if (KEYMANAGER->isOnceKeyDown(MOUSE_WHEEL_CLICK)) {
		CAMERAMANAGER->resetZoom();
	}

	if (KEYMANAGER->isOnceKeyDown(MOUSE_LEFT_CLICK)) {
		changeCursor(CURSOR_TYPE_CLICK);

		COLLISIONMANAGER->buttonWithCursor();
	}

	if (KEYMANAGER->isStayKeyDown(MOUSE_LEFT_CLICK)) {
		if (COLLISIONMANAGER->grabbedCard())
			changeCursor(CURSOR_TYPE_GRAB);
	}

	if (KEYMANAGER->isOnceKeyUp(MOUSE_LEFT_CLICK)) {
		changeCursor(CURSOR_TYPE_DEFAULT);

		if (_player->getCard()) {
			_x = _y = -1000;
			//충돌검사
			COLLISIONMANAGER->handsWithUseBox(_player->getCard());
			_player->setCard(NULL);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(MOUSE_RIGHT_CLICK)) {
		if (_player->getCard()) {
			changeCursor(CURSOR_TYPE_DEFAULT);

			_player->cancleCard();
		}
	}
}

void Cursor::controlMouseUI()
{
	//UI open
	if (KEYMANAGER->isOnceKeyDown(MOUSE_WHEEL_CLICK)) {

	}

	if (KEYMANAGER->isOnceKeyDown(MOUSE_LEFT_CLICK)) {
		changeCursor(CURSOR_TYPE_CLICK);

		if (UIMANAGER->getCurrentMenu()->getHide()) {
			if (COLLISIONMANAGER->selectedCard(DECKMANAGER->getCurrentDeck(), _x, _y))
				UIMANAGER->getCurrentMenu()->setHide(false);
			else
				UIMANAGER->getCurrentMenu()->setHide(true);
		}
	}

	if (KEYMANAGER->isStayKeyDown(MOUSE_LEFT_CLICK)) {

	}

	if (KEYMANAGER->isOnceKeyUp(MOUSE_LEFT_CLICK)) {
		changeCursor(CURSOR_TYPE_DEFAULT);
	}

	if (KEYMANAGER->isOnceKeyDown(MOUSE_RIGHT_CLICK)) {
		if (!UIMANAGER->getCurrentMenu()->getHide())
			UIMANAGER->getCurrentMenu()->setHide(true);
		else
			UIMANAGER->changeMenu("null");
	}
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
