#include "stdafx.h"
#include "InGameMenu.h"
#include "Player.h"

HRESULT InGameMenu::init()
{
	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	//OTHER HUD
	_defaultHUD = IMAGEMANAGER->addDImage("defaultHUD", L"img/UI/menu/ingame/BottomHud_Default_Full.png", 100, 100);
	_defaultHUDHigh = IMAGEMANAGER->addDImage("defaultHUD_high", L"img/UI/menu/ingame/BottomHud_Default_FullGlow.png", 128, 128);



	leftTopInit();
	leftBottomInit();
	rightTopInit();
	rightBottomInit();

	//BUTTON BODY
	for (int i = 0; i < END_HUD_TYPE; i++) {
		_defaultHUDButton[i].x += _defaultHUD->getWidth() / 2;
		_defaultHUDButton[i].y += _defaultHUD->getHeight() / 2;
		_defaultHUDButton[i].body = RectMakeCenter(_defaultHUDButton[i].x, _defaultHUDButton[i].y,
			_defaultHUD->getWidth(), _defaultHUD->getHeight());

		_defaultHUDButton[i].activate = false;
	}


	return S_OK;
}

void InGameMenu::release()
{
}

void InGameMenu::update()
{
	//진행
	progressIter progress = _progress.begin();
	for (; progress != _progress.end();) {
		(*progress)->update();

		if ((*progress)->getFin())
			progress = _progress.erase(progress);
		else
			++progress;
	}

	//버튼 충돌 검사
	if (!UIMANAGER->getOpen()) {
		for (int i = 0; i < END_HUD_TYPE; i++)
			COLLISIONMANAGER->buttonWithCursor(&_defaultHUDButton[i], _cursor->getX(), _cursor->getY());
	}
}

void InGameMenu::render()
{
	//LEFT TOP HUD
	_topHUD->render(0, 0);
	_goldIcon->render(30, 20);
	_ratsIcon->render(160, 20);
	_waveIcon->render(50, 62);
	//_poisonIcon;


	//progress
	progressIter progress = _progress.begin();
	int width, height;
	for (int i = 0; progress != _progress.end(); ++progress, ++i) {
		width = i % 7;
		height = i / 7;

		(*progress)->render(360 + width * 110, 60 + height * 110);
	}


	//Other HUD
	for (int i = 0; i < END_HUD_TYPE; i++) {
		//Button
		if(_defaultHUDButton[i].activate)
			_defaultHUDHigh->render(_defaultHUDButton[i].body.left - 15,
				_defaultHUDButton[i].body.top - 15);
		_defaultHUD->render(_defaultHUDButton[i].body.left,
			_defaultHUDButton[i].body.top);

		//Icon
		_defaultHUDButton[i].icon->render(_defaultHUDButton[i].x - _defaultHUDButton[i].icon->getWidth() / 2,
			_defaultHUDButton[i].y - _defaultHUDButton[i].icon->getHeight() / 2);
	}


	//TEXT
	leftTopText();
	leftBottomText();
	rightTopText();
	rightBottomText();
}

void InGameMenu::useButton(int index)
{
	if (index >= END_HUD_TYPE) return;

	switch (index) {
	case HUD_TYPE_LEADERSKILL:
		//useSkill();
		break;

	case HUD_TYPE_CARDBAG:
		UIMANAGER->changeMenu("cardBag");
		break;

	case HUD_TYPE_ALLCARDS:
		UIMANAGER->changeMenu("allCard");
		break;

	case HUD_TYPE_ADVISOR:
		//hide and seek (advisor)
		break;

	case HUD_TYPE_PAUSE:
		//pause & change Icon
		break;

	case HUD_TYPE_OPTION:
		//UIMANAGER->changeMenu("option");
		break;

	case HUD_TYPE_REDRAW:
		DECKMANAGER->redrawCard();
		break;

	case HUD_TYPE_CARDGRAVE:
		UIMANAGER->changeMenu("cardGrave");
		break;

	default:
		break;
	}
}

void InGameMenu::addCircleBar(int cost, float duration, int * reward)
{
	CircleBar* bar = new CircleBar;
	bar->init(cost, duration, reward);
	_progress.push_back(bar);
}

void InGameMenu::leftTopInit()
{
	//LEFT TOP HUD
	_topHUD = IMAGEMANAGER->addDImage("topHUD", L"img/UI/menu/ingame/TopHud2.png", 300, 110);
	_goldIcon = IMAGEMANAGER->addDImage("goldIcon", L"img/UI/menu/ingame/UI_Icon_Economy.png", 30, 30);
	_ratsIcon = IMAGEMANAGER->addDImage("ratsIcon", L"img/UI/menu/ingame/Icon_Mouse.png", 30, 30);
	_waveIcon = IMAGEMANAGER->addDImage("waveIcon", L"img/UI/menu/ingame/EasyIcon.png", 30, 30);
	//_poisonIcon;
}

void InGameMenu::leftBottomInit()
{
	//LEFT BOTTOM BUTTON & ICON
	_defaultHUDButton[HUD_TYPE_LEADERSKILL].x = 30;
	_defaultHUDButton[HUD_TYPE_LEADERSKILL].y = WINSIZEY - 250;
	_defaultHUDButton[HUD_TYPE_LEADERSKILL].icon = IMAGEMANAGER->addDImage("cardBagIcon", L"Img/UI/menu/ingame/UI_CardDeck_Own.png", 90, 90);

	_defaultHUDButton[HUD_TYPE_CARDBAG].x = 30;
	_defaultHUDButton[HUD_TYPE_CARDBAG].y = WINSIZEY - 125;
	_defaultHUDButton[HUD_TYPE_CARDBAG].icon = IMAGEMANAGER->addDImage("cardBagIcon", L"Img/UI/menu/ingame/UI_CardDeck_Own.png", 90, 90);
}

void InGameMenu::rightTopInit()
{
	//RIGHT TOP BUTTON & ICON
	_defaultHUDButton[HUD_TYPE_ALLCARDS].x = WINSIZEX - 505;
	_defaultHUDButton[HUD_TYPE_ALLCARDS].y = 15;
	_defaultHUDButton[HUD_TYPE_ALLCARDS].icon = IMAGEMANAGER->addDImage("allCardsIcon", L"img/UI/menu/ingame/Icon_Card.png", 65, 65);

	_defaultHUDButton[HUD_TYPE_ADVISOR].x = WINSIZEX - 380;
	_defaultHUDButton[HUD_TYPE_ADVISOR].y = 15;
	_defaultHUDButton[HUD_TYPE_ADVISOR].icon = IMAGEMANAGER->addDImage("advisorIcon", L"img/UI/menu/ingame/UI_Icon_Advisor.png", 60, 60);

	_defaultHUDButton[HUD_TYPE_PAUSE].x = WINSIZEX - 255;
	_defaultHUDButton[HUD_TYPE_PAUSE].y = 15;
	_defaultHUDButton[HUD_TYPE_PAUSE].icon = IMAGEMANAGER->addDImage("pauseIcon", L"Img/UI/menu/ingame/UI_Icon_Pause.png", 45, 45);

	_defaultHUDButton[HUD_TYPE_OPTION].x = WINSIZEX - 130;
	_defaultHUDButton[HUD_TYPE_OPTION].y = 15;
	_defaultHUDButton[HUD_TYPE_OPTION].icon = IMAGEMANAGER->addDImage("optionIcon", L"Img/UI/menu/ingame/UI_Icon_Menu.png", 70, 70);
}

void InGameMenu::rightBottomInit()
{
	//RIGHT BOTTOM BUTTON & ICON
	_defaultHUDButton[HUD_TYPE_REDRAW].x = WINSIZEX - 130;
	_defaultHUDButton[HUD_TYPE_REDRAW].y = WINSIZEY - 250;
	_defaultHUDButton[HUD_TYPE_REDRAW].icon = IMAGEMANAGER->addDImage("redrawIcon", L"img/UI/menu/ingame/UI_Icon_ReDraw.png", 80, 80);

	_defaultHUDButton[HUD_TYPE_CARDGRAVE].x = WINSIZEX - 130;
	_defaultHUDButton[HUD_TYPE_CARDGRAVE].y = WINSIZEY - 125;
	_defaultHUDButton[HUD_TYPE_CARDGRAVE].icon = IMAGEMANAGER->addDImage("cardGraveIcon", L"img/UI/menu/ingame/UI_CardDeck_Used.png", 95, 95);
}

void InGameMenu::leftTopText()
{
	//TEXT
	DEFAULT_STAT stat = GAMEMANAGER->getPlayer()->getDefaultStat();
	D2D1_RECT_F tmpRECT;
	WCHAR tmp[128];



	//gold
	swprintf_s(tmp, L"%d", stat.gold);

	DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
	tmpRECT = dRectMake(65 + 1, 27 + 1, 80, 20);
	DTDMANAGER->printText(tmp, tmpRECT, 18);

	DTDMANAGER->setBrushColor(ColorF(ColorF::Goldenrod));
	tmpRECT = dRectMake(65, 27, 80, 20);
	DTDMANAGER->printText(tmp, tmpRECT, 18);



	//tax
	swprintf_s(tmp, L"+%d", stat.tax);

	DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
	tmpRECT = dRectMake(120 + 1, 23 + 1, 80, 20);
	DTDMANAGER->printText(tmp, tmpRECT, 13);

	DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
	tmpRECT = dRectMake(120, 23, 80, 20);
	DTDMANAGER->printText(tmp, tmpRECT, 13);



	//civil
	swprintf_s(tmp, L"%d/%d", stat.currentCivil, stat.maxCivil);

	DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
	tmpRECT = dRectMake(195 + 1, 27 + 1, 80, 20);
	DTDMANAGER->printText(tmp, tmpRECT, 18);
	DTDMANAGER->setBrushColor(ColorF(ColorF::Green));
	tmpRECT = dRectMake(195, 27, 80, 20);
	DTDMANAGER->printText(tmp, tmpRECT, 18);


	DTDMANAGER->resetBrushColor();
}

void InGameMenu::leftBottomText()
{
	//TEXT
	D2D1_RECT_F tmpRECT = dRectMake(110, WINSIZEY - 115, 100, 50);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", DECKMANAGER->getCardBag().size());
	DTDMANAGER->printText(tmp, tmpRECT, 20);
}

void InGameMenu::rightTopText()
{
}

void InGameMenu::rightBottomText()
{

	//TEXT
	D2D1_RECT_F tmpRECT = dRectMake(WINSIZEX - 50, WINSIZEY - 115, 100, 50);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", DECKMANAGER->getCardGrave().size());
	DTDMANAGER->printText(tmp, tmpRECT, 20);
}
