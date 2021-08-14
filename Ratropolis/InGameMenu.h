#pragma once
#include "Menu.h"
#include "CircleBar.h"
#include <vector>

typedef struct tagButton {
	dImage* icon;

	float x, y;
	RECT body;

	void useButton() {};
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
private:
	typedef vector<CircleBar*>				progressList;
	typedef vector<CircleBar*>::iterator	progressIter;
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

	//CircleLoading
	progressList _progress;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void useButton(int index);
	void addCircleBar(int cost, float duration, int* reward);


	void leftTopInit();
	void leftBottomInit();
	void rightTopInit();
	void rightBottomInit();

	void leftTopText();
	void leftBottomText();
	void rightTopText();
	void rightBottomText();







	BUTTON* getButton() { return _defaultHUDButton; }
};

