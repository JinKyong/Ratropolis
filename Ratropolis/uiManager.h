#pragma once
#include "singletonBase.h"
#include "Menu.h"
#include <map>

class InGameMenu;

class uiManager : public singletonBase<uiManager>
{
private:
	typedef map<string, Menu*>				menuList;
	typedef map<string, Menu*>::iterator	menuIter;

private:
	InGameMenu* _inGame;

	menuList	_menuList;
	static Menu* _currentMenu;
	string _currentMenuName;

	bool _start;
	bool _open;

	uiManager() {};
	friend singletonBase<uiManager>;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	Menu* addMenu(string menuName, Menu* menu);
	Menu* findMenu(string menuName);
	HRESULT changeMenu(string menuName);

	void playGame();
	void useButton(int index);
	void addCircleBar(int cost, float duration, int* reward);





	InGameMenu* getInGame() { return _inGame; }
	Menu* getCurrentMenu() { return _currentMenu; }
	string getCurrentMenuName() { return _currentMenuName; }

	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }
};