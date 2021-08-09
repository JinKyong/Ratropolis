#pragma once
#include "singletonBase.h"

class uiManager : public singletonBase<uiManager>
{
private:

private:
	//돈과 시민, 웨이브
	int _gold;			//돈
	int _prize;			//현상금
	int _tax;			//세금
	int _currentCivil;	//현재 시민
	int _maxCivil;		//전체 시민
	int _wave;			//현재 웨이브

	//덱
	int _deck;			//덱의 장수
	int _grave;			//무덤 장수
	int _remain;		//남은 장수

	//스킬
	int _level;			//스킬 레벨



	//메뉴 리스트

	//현재 메뉴


	bool _open;

public:
	HRESULT init();
	void release();
	void update();
	void render();

/*
	UpMenu* addUpMenu(string menuName, UpMenu* menu);
	DownMenu* addDownMenu(string menuName, DownMenu* menu);
	HRESULT changeUpMenu(string menuName);
	HRESULT changeDownMenu(string menuName);*/





	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }
};

