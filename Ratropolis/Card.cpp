#include "stdafx.h"
#include "Card.h"
#include "ToolTip.h"

HRESULT Card::init()
{
	//플레이어
	_player = GAMEMANAGER->getPlayer();

	//상태
	_zoom = 1.0;
	_usable = _select = false;

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
	_body = RectMakeCenter(_x, _y, CARDWIDTH * _zoom, CARDHEIGHT * _zoom);
}

void Card::render()
{
	controlFrame();
}

void Card::renderDetailed()
{
	for (int i = 0; i < _atbList.size(); i++)
		_atbList[i]->render(_body.right, _body.top + 10 + i * 140);
}

void Card::controlFrame()
{
	if (_usable) {
		_count += TIMEMANAGER->getElapsedTime();

		if (_select) {
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
		else {
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
}
