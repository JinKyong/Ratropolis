#pragma once
#include "Menu.h"

typedef struct tagButton {
	dImage* icon;

	float x, y;
	RECT body;
}BUTTON;

enum HUD_TYPE {
	HUD_TYPE_LEADERSKILL,
	HUD_TYPE_CARDBAG,
	HUD_TYPE_ALLCARDS,
	HUD_TYPE_ADVISOR,
	HUD_TYPE_PAUSE,
	HUD_TYPE_OPTION,
	HUD_TYPE_REDRAW,
	HUD_TYPE_CARDGRAVE,
	END_HUD_TYPE
};

class InGameMenu
{
//Images
private:
	//OTHER HUD
	dImage* _defaultHUD;					//기본 HUD 이미지
	dImage* _defaultHUDHigh;				//기본 HUD 하이라이트

	BUTTON _defaultHUDButton[END_HUD_TYPE];	//HUD Button(네모 박스)


	//LEFT TOP HUD
	dImage* _topHUD;		//좌상단 HUD
	dImage* _goldIcon;		//골드 아이콘
	dImage* _ratsIcon;		//쥐 아이콘
	dImage* _waveIcon;		//웨이브 아이콘
	//dImage* _poisonIcon;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void leftTopInit();
	void leftBottomInit();
	void rightTopInit();
	void rightBottomInit();

	void leftTopText();
	void leftBottomText();
	void rightTopText();
	void rightBottomText();
};

