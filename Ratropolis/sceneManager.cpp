#include "stdafx.h"
#include "sceneManager.h"
#include "Player.h"
#include "Scene.h"
#include "SceneHeader.h"

Player* sceneManager::_player = NULL;
Scene* sceneManager::_currentScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::init()
{
	addScene("test", new testGameScene);

	return S_OK;
}

HRESULT sceneManager::init(Player * player)
{
	_player = player;

	addScene("test", new testGameScene);

	return S_OK;
}


//☆
void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{					//맵이라 필요한 second
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

Scene* sceneManager::addScene(string sceneName, Scene* scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init(_player)))
	{
		//현재(있던) 씬의 릴리즈 함수를 실행해주고
		if (_currentScene) _currentScene->release();

		//바꾸려는 씬을 현재씬으로 체인지
		_currentScene = find->second;

		CAMERAMANAGER->setFade(FADEIN);

		return S_OK;
	}

	return E_FAIL;
}