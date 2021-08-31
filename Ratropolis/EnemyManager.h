#pragma once
#include "EnemyHeader.h"
#include <vector>

class EnemyManager
{
private:
	typedef vector<Enemy*>				enemyList;
	typedef vector<Enemy*>::iterator	enemyIter;

private:
	enemyList	_enemies;



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void startWave(int num, int direct);
	bool clearWave();



	enemyList* getEnemies() { return &_enemies; }
};

