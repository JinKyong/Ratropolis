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
	dImage* _defaultHUD;					//�⺻ HUD �̹���
	dImage* _defaultHUDHigh;				//�⺻ HUD ���̶���Ʈ

	BUTTON _defaultHUDButton[END_HUD_TYPE];	//HUD Button(�׸� �ڽ�)


	//LEFT TOP HUD
	dImage* _topHUD;		//�»�� HUD
	dImage* _goldIcon;		//��� ������
	dImage* _ratsIcon;		//�� ������
	dImage* _waveIcon;		//���̺� ������
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

