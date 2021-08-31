#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(float x, int direct)
{
	_state = ENEMY_STATE_MOVE;
	_currentImage = _stateImages[_state];
	_frameX = 0;
	_isDead = false;

	_x = x;
	_y = GROUND - _currentImage->getFrameHeight();
	_direct = direct;

	_count = 0;
	_opacity = 1;

	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	//죽으면 점점 투명해짐
	if (_isDead) {
		if (_opacity) {
			_opacity -= 0.01;
			if (_opacity <= 0)
				_opacity = 0;
		}
	}

	if (_state == ENEMY_STATE_MOVE) {
		if (_direct)
			_x -= _speed;
		else
			_x += _speed;
		//충돌 검사
		//충돌하면 attack으로 바꿈
	}

	controlFrame();

	//갱신
	_body = RectMakeCenter(_x, _y + _currentImage->getFrameHeight() / 2, _currentImage->getFrameWidth(), _currentImage->getFrameHeight());
}

void Enemy::render()
{
	_currentImage->frameRender(_x - _currentImage->getFrameWidth() / 2, _y,	_frameX, _direct, _opacity);

	if (PRINTMANAGER->isDebug()) {
		DTDMANAGER->Rectangle(_body);
		DTDMANAGER->Rectangle(_detect);
	}
}

void Enemy::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= _renderCount[_state]) {
		if (_frameX >= _currentImage->getMaxFrameX()) {
			switch (_state) {
			case ENEMY_STATE_IDLE:
				//충돌 검사 해봐
				//트루면? attack 아니면 move
				_frameX = 0;
				break;

			case ENEMY_STATE_MOVE:
				_frameX = 0;
				break;

			case ENEMY_STATE_ATTACK:
				changeState(ENEMY_STATE_IDLE);
				break;

			default:
				break;
			}
		}
		else
			_frameX++;

		_count = 0;
	}
}

void Enemy::changeState(ENEMY_STATE state)
{
	//예외처리
	if (state >= END_ENEMY_STATE) return;
	if (_state == state) return;

	_state = state;

	_currentImage = _stateImages[_state];
	_frameX = 0;

	_y = GROUND - _currentImage->getFrameHeight();
}

void Enemy::changeHP(int num)
{
	_hp += num;

	if (_hp <= 0) {
		_hp = 0;
		_isDead = true;
		changeState(ENEMY_STATE_DEATH);
	}
}
