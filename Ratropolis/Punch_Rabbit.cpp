#include "stdafx.h"
#include "Punch_Rabbit.h"

Punch_Rabbit::Punch_Rabbit()
{
	//stateImages
	_stateImages[ENEMY_STATE_IDLE] = IMAGEMANAGER->addFrameDImage("punchRabbit_idle", L"img/object/enemy/punch rabbit/idle.png",
		280, 144, 4, 2);
	_stateImages[ENEMY_STATE_MOVE] = IMAGEMANAGER->addFrameDImage("punchRabbit_move", L"img/object/enemy/punch rabbit/move.png",
		456, 148, 6, 2);
	_stateImages[ENEMY_STATE_ATTACK] = IMAGEMANAGER->addFrameDImage("punchRabbit_attack", L"img/object/enemy/punch rabbit/attack.png",
		784, 184, 7, 2);
	_stateImages[ENEMY_STATE_DEATH] = IMAGEMANAGER->addFrameDImage("punchRabbit_death", L"img/object/enemy/punch rabbit/death.png",
		172, 136, 2, 2);

	//renderCount
	_renderCount[ENEMY_STATE_IDLE] = 0.15;
	_renderCount[ENEMY_STATE_MOVE] = 0.15;
	_renderCount[ENEMY_STATE_ATTACK] = 0.1;
	_renderCount[ENEMY_STATE_DEATH] = 0.5;


	_hp = 50;
	_damage = 5;
	_speed = 2;
}

Punch_Rabbit::~Punch_Rabbit()
{
}

HRESULT Punch_Rabbit::init(float x, int direct)
{
	Enemy::init(x, direct);

	_body = RectMakeCenter(_x, _y + _currentImage->getFrameHeight() / 2, _currentImage->getFrameWidth(), _currentImage->getFrameHeight());
	_detect = _body;

	return S_OK;
}

void Punch_Rabbit::release()
{
}

void Punch_Rabbit::update()
{
	Enemy::update();
	_detect = _body;

	if (KEYMANAGER->isOnceKeyDown('H'))
		changeState(ENEMY_STATE_IDLE);
	if (KEYMANAGER->isOnceKeyDown('J'))
		changeState(ENEMY_STATE_MOVE);
	if (KEYMANAGER->isOnceKeyDown('K'))
		changeState(ENEMY_STATE_ATTACK);
	if (KEYMANAGER->isOnceKeyDown('L'))
		changeState(ENEMY_STATE_DEATH);
	if (KEYMANAGER->isOnceKeyDown('M'))
		changeHP(-5);
}

void Punch_Rabbit::render()
{
	Enemy::render();
}
