#include "stdafx.h"
#include "Card.h"

HRESULT Card::init()
{
	//플레이어
	_player = GAMEMANAGER->getPlayer();

	//상태
	_select = _usable = false;

	//이펙트 이미지 & 프레임
	_selectEffect = IMAGEMANAGER->addFrameDImage("selectEffect", L"img/card/effect/Card_SelectEffect_Blue.png", 1000, 840, 5, 3);
	_usableEffect = IMAGEMANAGER->addFrameDImage("usableEffect", L"img/card/effect/Card_ActiveEffect_Green.png", 1000, 840, 5, 3);
	_frameX = _frameY = 0;
	_count = 0;

	return S_OK;
}

void Card::release()
{
}

void Card::update()
{
	if (_select)
		_body = RectMakeCenter(_x, _y, CARDWIDTH * 2, CARDHEIGHT * 2);
	else
		_body = RectMakeCenter(_x, _y, CARDWIDTH, CARDHEIGHT);
}

void Card::render()
{
	controlFrame();
}

void Card::controlFrame()
{
	if (_select) {
		_count += TIMEMANAGER->getElapsedTime();
		
		if (_count >= 0.1) {
			if (_frameX >= _selectEffect->getMaxFrameX()) {

				if (_frameY >= _selectEffect->getMaxFrameY()) {
					_frameX = _frameY = 0;
				}
				else {
					_frameX = 0;
					_frameY++;
				}

			}
			else {
				_frameX++;
			}

			_count = 0;
		}

		_selectEffect->frameRender(_x - CARDWIDTH / 2 - 21, _y - CARDHEIGHT / 2 - 19, _frameX, _frameY);
	}
	else if (_usable) {
		_count += TIMEMANAGER->getElapsedTime();

		if (_count >= 0.1) {
			if (_frameX >= _usableEffect->getMaxFrameX()) {

				if (_frameY >= _usableEffect->getMaxFrameY()) {
					_frameX = _frameY = 0;
				}
				else {
					_frameX = 0;
					_frameY++;
				}

			}
			else {
				_frameX++;
			}

			_count = 0;
		}

		_usableEffect->frameRender(_x - CARDWIDTH / 2 - 21, _y - CARDHEIGHT / 2 - 19, _frameX, _frameY);
	}
}
