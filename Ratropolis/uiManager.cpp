#include "stdafx.h"
#include "uiManager.h"
#include "MenuHeader.h"

HRESULT uiManager::init()
{

	//changeDownMenu("logMenu");

	_open = false;

	return S_OK;
}

void uiManager::release()
{
	
}

void uiManager::update()
{
}

void uiManager::render()
{
	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_UI);

	DTDMANAGER->beginDraw();

	//���⼭ �׸���


	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}
