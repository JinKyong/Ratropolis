#include "stdafx.h"
#include "uiManager.h"
#include "MenuHeader.h"

Menu* uiManager::_currentMenu = NULL;

HRESULT uiManager::init()
{
	_currentMenu = NULL;

	addMenu("cardGrave", new CardGraveMenu);

	_start = false;
	_open = false;

	return S_OK;
}

void uiManager::release()
{
	SAFE_RELEASE(_inGame);

	//메뉴 release
	menuIter miList = _menuList.begin();

	for (; miList != _menuList.end();)
	{
		if (miList->second != NULL)
		{
			if (miList->second == _currentMenu) miList->second->release();
			SAFE_DELETE(miList->second);
			miList = _menuList.erase(miList);
		}
		else ++miList;
	}

	_menuList.clear();
}

void uiManager::update()
{
	if (_start)_inGame->update();
	if (_currentMenu) _currentMenu->update();
}

void uiManager::render()
{
	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_UI);

	DTDMANAGER->beginDraw();

	//여기서 그리자
	if (_start) _inGame->render();
	if (_currentMenu) _currentMenu->render();

	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}

Menu * uiManager::addMenu(string menuName, Menu * menu)
{
	if (!menu) return nullptr;

	_menuList.insert(make_pair(menuName, menu));

	return menu;
}

HRESULT uiManager::changeMenu(string menuName)
{
	if (menuName == "null") {
		if (_currentMenu) _currentMenu->release();
		_open = false;

		_currentMenu = NULL;
	}

	menuIter find = _menuList.find(menuName);

	if (find == _menuList.end()) return E_FAIL;

	if (find->second == _currentMenu) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		//현재(있던) 씬의 릴리즈 함수를 실행해주고
		if (_currentMenu) _currentMenu->release();

		//바꾸려는 씬을 현재씬으로 체인지
		_currentMenu = find->second;

		//CAMERAMANAGER->setFade(FADEIN);

		return S_OK;
	}

	return E_FAIL;
}

void uiManager::playGame()
{
	_start = true;

	_inGame = new InGameMenu;
	_inGame->init();
}