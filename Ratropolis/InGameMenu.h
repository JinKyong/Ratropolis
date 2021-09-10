#pragma once
#include "Button.h"
#include "CircleBar.h"
#include "WaveBar.h"
#include <vector>

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

class Cursor;

class InGameMenu
{
private:
	typedef vector<CircleBar*>				progressList;
	typedef vector<CircleBar*>::iterator	progressIter;
//Images
private:
	Cursor* _cursor;


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


	//drawCost
	float _drawCount;
	int _drawCost;


	//CircleLoading
	progressList _progress;

	//waveLoading
	WaveBar *_leftWave, *_rightWave;
	int _wave;
	int _nextWave;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void useButton(int index);
	void addCircleBar(int cost, float duration, int* reward);
	void addWaveBar(int direct);
	void waveLoadingFin();

	void leftTopInit();
	void leftBottomInit();
	void rightTopInit();
	void rightBottomInit();

	void leftTopText();
	void leftBottomText();
	void rightTopText();
	void rightBottomText();







	BUTTON* getButton() { return _defaultHUDButton; }

	WaveBar* getLeftWave() { return _leftWave; }
	WaveBar* getRightWave() { return _rightWave; }

	int getWave() { return _wave; }
	void setWave(int wave) { _wave = wave; }
	int getNextWave() { return _nextWave; }
	void setNextWave(int nextWave) { _nextWave = nextWave; }
};

