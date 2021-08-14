#pragma once
#include "BuildingHeader.h"
#include <vector>

class Cursor;

class BuildManager
{
private:
	typedef vector<Building*>				buildList;
	typedef vector<Building*>::iterator		buildIter;

private:
	buildList _buildings;

	Cursor* _cursor;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	Building* addBuilding(int idX, int num, int level = 1);
};

