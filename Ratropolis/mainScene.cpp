#include "stdafx.h"
#include "mainScene.h"

HRESULT mainScene::init(Player * player)
{
	Scene::init(player);

	CAMERAMANAGER->setFade(FADEOUT);
	CAMERAMANAGER->setBackScreenSize(WINSIZEX, WINSIZEY);


	backInit();
	middleInit();
	frontInit();


	_count = 0;
	_ratCloakX = _ratCloakY = 0;


	_start.x = 200;
	_start.y = 450;
	_start.body = RectMake(_start.x, _start.y, 200, 50);
	_start.activate = false;
	_start.selected = false;

	_exit.x = 200;
	_exit.y = 600;
	_exit.body = RectMake(_exit.x, _exit.y, 200, 50);
	_exit.activate = false;
	_exit.selected = false;


	_change = false;

	SOUNDMANAGER->play("mainTheme");

	return S_OK;
}

void mainScene::release()
{
	SOUNDMANAGER->stop("mainTheme");
}

void mainScene::update()
{
	_player->getCursor()->updatePosition(_ptMouse.x, _ptMouse.y);

	COLLISIONMANAGER->buttonWithCursor(&_start, _player->getCursor()->getX(), _player->getCursor()->getY());
	COLLISIONMANAGER->buttonWithCursor(&_exit, _player->getCursor()->getX(), _player->getCursor()->getY());

	if (_start.activate)
		_player->getCursor()->changeButton(&_start);
	else if (_exit.activate)
		_player->getCursor()->changeButton(&_exit);
	else
		_player->getCursor()->changeButton(NULL);

	_player->getCursor()->updatePosition(_ptMouse.x, _ptMouse.y);
	_player->getCursor()->controlMouseMain();

	if (_start.selected) {
		CAMERAMANAGER->setFade(FADEOUT);
		_change = true;
	}
	else if (_exit.selected) {
		PostQuitMessage(0);
		return;
	}

	controlFrame();
	changeScene();
}

void mainScene::render()
{
	backRender();
	middleRender();
	frontRender();

	D2D1_RECT_F tempRECT = { _start.body.left, _start.body.top, _start.body.right, _start.body.bottom };
	if (_start.activate)
		DTDMANAGER->printText(L"게임 시작", tempRECT, 50, false, false, true);
	else
		DTDMANAGER->printText(L"게임 시작", tempRECT, 40, false, false, true);

	tempRECT = dRectMake(_exit.body.left, _exit.body.top, 200, 50);
	if (_exit.activate)
		DTDMANAGER->printText(L"게임 종료", tempRECT, 50, false, false, true);
	else
		DTDMANAGER->printText(L"게임 종료", tempRECT, 40, false, false, true);

	_player->render();
}

void mainScene::changeScene()
{
	if (_change) {
		if (CAMERAMANAGER->getAlpha() == 1.0)
			SCENEMANAGER->changeScene("loading");
	}
}

void mainScene::controlFrame()
{
	_count += TIMEMANAGER->getElapsedTime();

	if (_count >= 0.05) {
		if (_ratCloakX >= _middle_ratCloak.img->getMaxFrameX()) {
			if (_ratCloakY >= _middle_ratCloak.img->getMaxFrameY())
				_ratCloakY = 0;
			else
				_ratCloakY++;

			_ratCloakX = 0;
		}
		else
			_ratCloakX++;


		if (_flagX >= _middle_flag->getMaxFrameX()) {
			if (_flagY >= _middle_flag->getMaxFrameY())
				_flagY = 0;
			else
				_flagY++;

			_flagX = 0;
		}
		else
			_flagX++;

		_count = 0;
	}
}

void mainScene::backInit()
{
	_background = IMAGEMANAGER->addDImage("main_background", L"img/main/Title_Background.png", WINSIZEX, WINSIZEY);
	_back_wall = IMAGEMANAGER->addDImage("main_back_wall", L"img/main/Title_Wall.png", 700, WINSIZEY);
	_back_monsterRat = IMAGEMANAGER->addDImage("main_back_monsterRat", L"img/main/Title_MonsterRat.png", 282, 388);
}

void mainScene::middleInit()
{
	_middle_flag = IMAGEMANAGER->addFrameDImage("main_middle_flag", L"img/main/Title_Flag.png", 2136, 1152, 8, 8);


	_middle_plagueRat.img = IMAGEMANAGER->addDImage("main_middle_plagueRat", L"img/main/Title_PlagueRat.png", 459, 551);
	_middle_plagueRat.x = 1040;
	_middle_plagueRat.y = 200;
	_middle_plagueRat.reverse = false;




	_middle_ratShield.img = IMAGEMANAGER->addDImage("main_middle_ratShield", L"img/main/Title_Shieldbearer_Shield.png", 150, 259);
	_middle_ratShield.x = 710;
	_middle_ratShield.y = 600;
	_middle_ratShield.reverse = false;

	_middle_ratBody.img = IMAGEMANAGER->addDImage("main_middle_ratBody", L"img/main/Title_Shieldbearer_Body.png", 305, 532);
	_middle_ratBody.x = 550;
	_middle_ratBody.y = 400;
	_middle_ratBody.reverse = false;

	_middle_ratCloak.img = IMAGEMANAGER->addFrameDImage("main_middle_ratCloak", L"img/main/Title_Cloak.png", 2304, 2304, 8, 8);
	_middle_ratCloak.x = 380;
	_middle_ratCloak.y = 550;
	_middle_ratCloak.reverse = false;

	_middle_ratSword.img = IMAGEMANAGER->addDImage("main_middle_ratSword", L"img/main/Title_Shieldbearer_Sword.png", 233, 262);
	_middle_ratSword.x = 510;
	_middle_ratSword.y = 630;
	_middle_ratSword.reverse = false;




	_middle_amorRatBody.img = IMAGEMANAGER->addDImage("main_middle_amorRatBody", L"img/main/Title_ArmorMan_Body.png", 430, 767);
	_middle_amorRatBody.x = 100;
	_middle_amorRatBody.y = 200;
	_middle_amorRatBody.reverse = false;

	_middle_amorRatHand.img = IMAGEMANAGER->addDImage("main_middle_amorRatHand", L"img/main/Title_ArmorMan_Hand.png", 400, 282);
	_middle_amorRatHand.x = 110;
	_middle_amorRatHand.y = 550;
	_middle_amorRatHand.reverse = false;
}

void mainScene::frontInit()
{
	_front_stone = IMAGEMANAGER->addDImage("main_front_stone", L"img/main/Title_Stone.png", WINSIZEX, WINSIZEY);
	_front_gradient = IMAGEMANAGER->addDImage("main_front_gradient", L"img/main/Title_Gradient.png", WINSIZEX, WINSIZEY);
	_front_logo = IMAGEMANAGER->addDImage("main_front_logo", L"img/main/TitleLogo.png", 540, 270);
}

void mainScene::backRender()
{
	_background->render(0, 0);
	_back_wall->render(0, 0);
	_back_monsterRat->render(1040, 415);
}

void mainScene::middleRender()
{
	_middle_flag->frameRender(430, 150, _flagX, _flagY);


	_middle_plagueRat.img->render(_middle_plagueRat.x, _middle_plagueRat.y);


	_middle_ratShield.img->render(_middle_ratShield.x, _middle_ratShield.y);
	_middle_ratCloak.img->frameRender(_middle_ratCloak.x, _middle_ratCloak.y, _ratCloakX, _ratCloakY);
	_middle_ratBody.img->render(_middle_ratBody.x, _middle_ratBody.y);
	_middle_ratSword.img->render(_middle_ratSword.x, _middle_ratSword.y);


	_middle_amorRatBody.img->render(_middle_amorRatBody.x, _middle_amorRatBody.y);
	_middle_amorRatHand.img->render(_middle_amorRatHand.x, _middle_amorRatHand.y);
}

void mainScene::frontRender()
{
	_front_stone->render(0, 0);
	_front_gradient->render(0, 0);
	_front_logo->render(20, 80);
}
