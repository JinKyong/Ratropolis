#include "stdafx.h"
#include "InGameMenu.h"
#include "Player.h"

HRESULT InGameMenu::init()
{
	//LEFT TOP HUD
	_topHUD = IMAGEMANAGER->addDImage("topHUD", L"img/UI/TopHud2.png", 300, 110);
	_goldIcon = IMAGEMANAGER->addDImage("goldIcon", L"img/UI/UI_Icon_Economy.png", 30, 30);
	_ratsIcon = IMAGEMANAGER->addDImage("ratsIcon", L"img/UI/Icon_Mouse.png", 30, 30);
	_waveIcon = IMAGEMANAGER->addDImage("waveIcon", L"img/UI/EasyIcon.png", 30, 30);
	//_poisonIcon;


	//OTHER HUD
	_defaultHUD = IMAGEMANAGER->addDImage("defaultHUD", L"img/UI/BottomHud_Default_Full.png", 100, 100);
	_defaultHUDHighlite = IMAGEMANAGER->addDImage("defaultHUD_high", L"img/UI/BottomHud_Default_FullGlow.png", 128, 128);


	//LEFT BOTTOM ICON
	//_playerSkillIcon;
	_cardBagIcon = IMAGEMANAGER->addDImage("cardBagIcon", L"Img/UI/UI_CardDeck_Own.png", 90, 90);


	//RIGHT TOP ICON
	_allCardsIcon = IMAGEMANAGER->addDImage("allCardsIcon", L"img/UI/Icon_Card.png", 128, 128);
	_advisorIcon = IMAGEMANAGER->addDImage("advisorIcon", L"img/UI/UI_Icon_Advisor.png", 128, 128);
	//_pauseIcon;
	//_optionIcon;


	//RIGHT BOTTOM ICON
	_redrawIcon = IMAGEMANAGER->addDImage("redrawIcon", L"img/UI/UI_Icon_ReDraw.png", 80, 80);
	_cardGraveIcon = IMAGEMANAGER->addDImage("cardGraveIcon", L"img/UI/UI_CardDeck_Used.png", 95, 95);

	return S_OK;
}

void InGameMenu::release()
{
}

void InGameMenu::update()
{
}

void InGameMenu::render()
{
	leftTopRender();
	leftBottomRender();
	rightTopRender();
	rightBottomRender();
}

void InGameMenu::setPlayer(Player * player)
{
	_player = player;
}

void InGameMenu::leftTopRender()
{
	//LEFT TOP HUD
	_topHUD->render(0, 0);
	_goldIcon->render(30, 20);
	_ratsIcon->render(150, 20);
	_waveIcon->render(50, 62);
	//_poisonIcon;

	//TEXT
	DEFAULT_STAT stat = _player->getDefaultStat();
	D2D1_RECT_F tmpRECT = dRectMake(70, 25, 100, 50);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", stat.gold);
	//DTDMANAGER->setBrushColor(ColorF(ColorF::DarkGoldenrod));
	DTDMANAGER->printText(tmp, tmpRECT, 20);


	DTDMANAGER->resetBrushColor();
}

void InGameMenu::leftBottomRender()
{
	_defaultHUD->render(30, WINSIZEY - 250);
	//_playerSkillIcon;

	_defaultHUD->render(30, WINSIZEY - 125);
	_cardBagIcon->render(37, WINSIZEY - 120);
}

void InGameMenu::rightTopRender()
{
}

void InGameMenu::rightBottomRender()
{
	_defaultHUD->render(WINSIZEX - 130, WINSIZEY - 250);
	_redrawIcon->render(WINSIZEX - 118, WINSIZEY - 240);

	_defaultHUD->render(WINSIZEX - 130, WINSIZEY - 125);
	_cardGraveIcon->render(WINSIZEX - 127, WINSIZEY - 120);
}
