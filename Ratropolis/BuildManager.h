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

	void isPossibleWall();	//�� ���� ���� �Ǻ�
	void isPossible();		//�ǹ� ���� ���� �Ǻ�

	void wallRender();		//�� ���
	void spaceRender();		//�� ���� ���

	void grabBcard();
	void putBcard();

	void expandSpace(int idX);	//���� Ȯ��
	void addWall();				//�� �߰�
	void addBuilding();			//�ǹ� �߰�
	Building* addBuilding(int idX, int num, int level = 1, bool reverse = false);







	buildList* getBuildings() { return &_buildings; }

	int getLeftWall() { return _leftWall; }
	int getRightWall() { return _rightWall; }

	bool getPossible() { return _possible; }
	void setPossible(bool possible) { _possible = possible; }
};

