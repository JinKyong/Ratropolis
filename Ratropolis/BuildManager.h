#pragma once
#include "BuildingHeader.h"
#include <vector>

class Cursor;

class BuildManager
{
private:
	typedef vector<Building*>				buildList;
	typedef vector<Building*>::iterator		buildIter;

	typedef vector<PSPACE>					spaceList;
	typedef vector<PSPACE>::iterator		spaceIter;

private:
	buildList _buildings;
	spaceList _space;
	Building* _building;

	dImage* _groundLight;

	Cursor* _cursor;

	bool _possible;

public:
	HRESULT init();
	HRESULT init(int num);
	void release();
	void update();
	void render();

	void isPossible();
	void spaceRender();

	void grabBcard();
	void putBcard();

	void addBuilding();
	Building* addBuilding(int idX, int num, int level = 1);






	bool getPossible() { return _possible; }
	void setPossible(bool possible) { _possible = possible; }
};

