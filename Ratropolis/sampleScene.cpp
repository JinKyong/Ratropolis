#include "stdafx.h"
#include "sampleScene.h"

HRESULT sampleScene::init()
{
	return S_OK;
}

void sampleScene::release()
{
}

void sampleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		SCENEMANAGER->changeScene("test");
}

void sampleScene::render()
{
}

void sampleScene::changeScene()
{
}
