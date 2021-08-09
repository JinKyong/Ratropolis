#include "stdafx.h"
#include "Scene.h"

Player* Scene::_player = NULL;

HRESULT Scene::init(Player * player)
{
	_player = player;

	return S_OK;
}
