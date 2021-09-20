#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "InGameMenu.h"

HRESULT GameManager::init(Player * player)
{
	_fadeImage = IMAGEMANAGER->addDImage("fade_B", L"img/fade_B.png", WINSIZEX, WINSIZEY);

	_player = player;
	

	//Shop & Event Button

	_buildManager = new BuildManager;
	_enemyManager = new EnemyManager;
	_NPCManager = new NPCManager;

	_gameTime = _waveTime = 0;
	_firstWaveStart = false;
	_onWave = false;

	return S_OK;
}

void GameManager::release()
{
	_buildManager->release();
	_enemyManager->release();
	_NPCManager->release();
}

void GameManager::update()
{
	_buildManager->update();
	_enemyManager->update();
	_NPCManager->update();

	//ButtonMove
	if (_onShop) {
		COLLISIONMANAGER->buttonWithCursor(&_shopButton, _player->getCursor()->getBackX(), _player->getCursor()->getBackY());

		if (_shopCount <= 0)
			offShop();
		else
			_shopCount -= TIMEMANAGER->getElapsedTime();
	}
	else {
		if (_shopCount >= 10)
			onShop();
		else
			_shopCount += TIMEMANAGER->getElapsedTime();
	}

	if (_onEvent) {
		COLLISIONMANAGER->buttonWithCursor(&_eventButton, _player->getCursor()->getBackX(), _player->getCursor()->getBackY());

		if (_eventCount <= 0)
			offEvent();
		else
			_eventCount -= TIMEMANAGER->getElapsedTime();
	}
	else {
		if (_eventCount >= 10)
			onEvent();
		else
			_eventCount += TIMEMANAGER->getElapsedTime();
	}

	_player->update();

	//경과시간
	_gameTime += TIMEMANAGER->getElapsedTime();
	if (!_firstWaveStart && _gameTime >= 25) {
		_firstWaveStart = true;
		UIMANAGER->getInGame()->addWaveBar(RND->getInt(2));
	}

	if (_onWave) {
		_waveTime += TIMEMANAGER->getElapsedTime();
		
		if (_enemyManager->clearWave()) {
			_onWave = false;
			_waveTime = 0;
			UIMANAGER->getInGame()->addWaveBar(RND->getInt(2));
		}
		else if (_waveTime >= 120) {
			UIMANAGER->getInGame()->addWaveBar(RND->getInt(2));
			_waveTime = 0;
		}
	}
	else {
		_waveTime = 0;
	}
}

void GameManager::render()
{
	_buildManager->render();
	_enemyManager->render();
	_NPCManager->render();

	WCHAR tmp[128];
	D2D1_RECT_F tmpRECT;

	if (_onShop) {
		if(_shopButton.activate)
			_shopButtonHL->render(_shopButton.x - _shopButtonHL->getWidth() / 2, _shopButton.y - _shopButtonHL->getHeight() / 2);
		_shopButton.icon->render(_shopButton.x - _shopButton.icon->getWidth() / 2, _shopButton.y - _shopButton.icon->getHeight() / 2);

		swprintf_s(tmp, L"%ds", (int)_shopCount);
		DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
		tmpRECT = dRectMakeCenter(_shopButton.x + 10, _shopButton.body.bottom - 10, 80, 30);
		DTDMANAGER->printText(tmp, tmpRECT, 15, true, true, true);
	}
	if (_onEvent) {
		if (_eventButton.activate)
			_eventButtonHL->render(_eventButton.x - _eventButtonHL->getWidth() / 2, _eventButton.y - _eventButtonHL->getHeight() / 2);
		_eventButton.icon->render(_eventButton.x - _eventButton.icon->getWidth() / 2, _eventButton.y - _eventButton.icon->getHeight() / 2);

		swprintf_s(tmp, L"%ds", (int)_eventCount);
		DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
		tmpRECT = dRectMakeCenter(_eventButton.x + 10, _eventButton.body.bottom - 10, 80, 30);
		DTDMANAGER->printText(tmp, tmpRECT, 15, true, true, true);
	}

	//배경 시야
	renderSight();
	renderPlayer();


	if (PRINTMANAGER->isDebug()) {
		WCHAR tmp[128];
		swprintf_s(tmp, L"time : %f", _gameTime);
		D2D1_RECT_F tmpRECT = CAMERAMANAGER->getScreen();
		tmpRECT = dRectMakeCenter((tmpRECT.right + tmpRECT.left) / 2, tmpRECT.top + 50, 200, 50);
		DTDMANAGER->printText(tmp, tmpRECT, 15, true, true);
	}
}

void GameManager::playGame()
{
	_useBox = RectMakeCenter(WINSIZEX / 2, (WINSIZEY - 240) / 2, WINSIZEX, WINSIZEY - 360);

	_player->setCamX(44 * 90);
	_player->setCamY(CAMERAMANAGER->getBackScreenHeight() / 2 + 300);
	_player->playGame();

	//Button
	_shopButton.x = 44 * 90 - 45;
	_shopButton.y = GROUND - 100;
	_shopButton.icon = IMAGEMANAGER->addDImage("shopIcon", L"img/object/UI_Icon_Shop.png", 64, 64);
	_shopButton.body = RectMakeCenter(_shopButton.x, _shopButton.y, _shopButton.icon->getWidth(), _shopButton.icon->getHeight());
	_shopButton.activate = false;

	_eventButton.x = 45 * 90 - 45;
	_eventButton.y = GROUND - 100;
	_eventButton.icon = IMAGEMANAGER->addDImage("eventIcon", L"img/object/UI_Icon_Scroll.png", 64, 64);
	_eventButton.body = RectMakeCenter(_eventButton.x, _eventButton.y, _eventButton.icon->getWidth(), _eventButton.icon->getHeight());
	_eventButton.activate = false;

	_shopButtonHL = IMAGEMANAGER->addDImage("shopIconHL", L"img/object/UI_Icon_Shop_Glow.png", 64, 64);
	_eventButtonHL = IMAGEMANAGER->addDImage("eventIconHL", L"img/object/UI_Icon_Scroll_Glow.png", 64, 64);

	_shopCount = _eventCount = 0;
	_onShop = _onEvent = false;


	_buildManager->init(88);
	_enemyManager->init();
	_NPCManager->init();
}

void GameManager::renderSight()
{
	int left = _player->getMaxLeft();
	int right = _player->getMaxRight();
	float width = CAMERAMANAGER->getBackScreenWidth();
	float height = CAMERAMANAGER->getBackScreenHeight();
	D2D1_RECT_F tmpRECT, tmpRECT2;
	float alpha;
	tmpRECT2 = dRectMake(0, 0, _fadeImage->getWidth(), _fadeImage->getHeight());

	//left
	alpha = 1;
	tmpRECT = dRectMake(left - 630, 0, 630 + 180, height);
	_fadeImage->render(tmpRECT, tmpRECT2, alpha);
	for (int i = 1; i <= 100; i++) {
		tmpRECT = dRectMake(tmpRECT.right, tmpRECT.top, 2, height);
		_fadeImage->render(tmpRECT, tmpRECT2, alpha);
		alpha -= 0.01;
	}

	//right
	alpha = 1;
	tmpRECT = dRectMake(right - 180, 0, 630 + 180, height);
	_fadeImage->render(tmpRECT, tmpRECT2, alpha);
	for (int i = 1; i <= 100; i++) {
		tmpRECT = dRectMake(tmpRECT.left - 2, tmpRECT.top, 2, height);
		_fadeImage->render(tmpRECT, tmpRECT2, alpha);
		alpha -= 0.01;
	}
}

void GameManager::renderPlayer()
{
	if (UIMANAGER->getOpen()) return;

	DTDMANAGER->changeRenderTarget(RENDERTARGET_TYPE_CARD);

	DTDMANAGER->beginDraw(false);

	_player->render();

	if (PRINTMANAGER->isDebug()) {
		DTDMANAGER->Rectangle(_useBox);
	}

	DTDMANAGER->endDraw();

	DTDMANAGER->changeRenderTargetPast();
}

void GameManager::onShop()
{
	_onShop = true;
	_shopCount = 30;

	SOUNDMANAGER->play("shopArrive");
}

void GameManager::offShop()
{
	_shopButton.activate = false;
	_onShop = false;
	_shopCount = 0;

	UIMANAGER->findMenu("shop")->setHide(false);
	UIMANAGER->findMenu("shop")->release();

	SOUNDMANAGER->play("shopLeave");
}

void GameManager::onEvent()
{
	_onEvent = true;
	_eventCount = 30;

	SOUNDMANAGER->play("eventArrive");
}

void GameManager::offEvent()
{
	_eventButton.activate = false;
	_onEvent = false;
	_eventCount = 0;

	SOUNDMANAGER->play("eventLeave");
}
