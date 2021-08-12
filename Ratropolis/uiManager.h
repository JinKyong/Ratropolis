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

	bool _start;
	bool _open;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	Menu* addMenu(string menuName, Menu* menu);
	HRESULT changeMenu(string menuName);

	void playGame();







	InGameMenu* getInGame() { return _inGame; }
	Menu* getCurrentMenu() { return _currentMenu; }

	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }
};