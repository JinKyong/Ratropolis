#include "stdafx.h"
#include "EnemyManager.h"

HRESULT EnemyManager::init()
{

	return S_OK;
}

void EnemyManager::release()
{
	enemyIter enemy = _enemies.begin();
	for (; enemy != _enemies.end();) {
		SAFE_RELEASE(*enemy);
		enemy = _enemies.erase(enemy);
	}

	_enemies.clear();
}

void EnemyManager::update()
{
	enemyIter enemy = _enemies.begin();
	for (; enemy != _enemies.end();){
		(*enemy)->update();

		if ((*enemy)->getOpacity() == 0)
			enemy = _enemies.erase(enemy);
		else
			++enemy;
	}
}

void EnemyManager::render()
{
	enemyIter enemy = _enemies.begin();
	for (; enemy != _enemies.end(); ++enemy)
		(*enemy)->render();
}

void EnemyManager::startWave(int num, int direct)
{
	switch (num) {
	case 1:
		//에너미 추가하고 
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		break;

	case 2:
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		break;

	case 3:
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		_enemies.push_back(new Punch_Rabbit);
		break;

	default:
		break;
	}


	//init()해주기
	int leftWall, rightWall;

	switch (direct) {
	case DIRECT_RIGHT:
		rightWall = GAMEMANAGER->getBuildManager()->getRightWall();
		for (int i = 0; i < _enemies.size(); ++i)
			_enemies[i]->init((rightWall + 8 + i) * 90, DIRECT_LEFT);
		break;
		
	case DIRECT_LEFT:
		leftWall = GAMEMANAGER->getBuildManager()->getLeftWall();
		for (int i = 0; i < _enemies.size(); ++i)
			_enemies[i]->init((leftWall - 7 - i) * 90, DIRECT_RIGHT);
		break;

	case DIRECT_ALL:
		rightWall = GAMEMANAGER->getBuildManager()->getRightWall();
		leftWall = GAMEMANAGER->getBuildManager()->getLeftWall();

		for (int i = 0; i < _enemies.size(); ++i) {
			if (i < _enemies.size() / 2)
				_enemies[i]->init(rightWall * 90, DIRECT_LEFT);
			else
				_enemies[i]->init(leftWall * 90, DIRECT_RIGHT);
		}
		break;

	default:
		break;
	}
}

bool EnemyManager::clearWave()
{
	return _enemies.empty();
}
