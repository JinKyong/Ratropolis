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
	//list
	buildList _buildings;
	spaceList _space;
	int _leftWall, _rightWall;

	Building* _building;

	//image
	dImage* _groundLight;
	dImage* _wall;
	dImage* _wallLight;

	Cursor* _cursor;

	int _getWall;
	bool _possible;

public:
	HRESULT init();
	HRESULT init(int num);
	void release();
	void update();
	void render();

	void isPossibleWall();	//방어선 생성 여부 판별
	void isPossible();		//건물 생성 여부 판별

	void wallRender();		//방어선 출력
	void spaceRender();		//빈 공간 출력

	void grabBcard();
	void putBcard();

	void expandSpace(int idX);	//공간 확장
	void addWall();				//방어선 추가
	void addBuilding();			//건물 추가
	Building* addBuilding(int idX, int num, int level = 1, bool reverse = false);







	buildList* getBuildings() { return &_buildings; }

	int getLeftWall() { return _leftWall; }
	int getRightWall() { return _rightWall; }

	bool getPossible() { return _possible; }
	void setPossible(bool possible) { _possible = possible; }
};

