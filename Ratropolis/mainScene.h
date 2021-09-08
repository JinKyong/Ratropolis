#pragma once
#include "Scene.h"
#include "Button.h"

class mainScene : public Scene
{
private:
	typedef struct tagObj {
		dImage* img;
		float x, y;
		bool reverse;
	}OBJECT, *POBJECT;

private:
	//back
	dImage* _background;
	dImage* _back_wall;
	dImage* _back_monsterRat;


	//middle
	dImage* _middle_flag;

	OBJECT _middle_plagueRat;

	OBJECT _middle_ratShield;
	OBJECT _middle_ratBody;
	OBJECT _middle_ratCloak;
	OBJECT _middle_ratSword;

	OBJECT _middle_amorRatBody;
	OBJECT _middle_amorRatHand;



	//front
	dImage* _front_stone;
	dImage* _front_gradient;
	dImage* _front_logo;


	//frame
	float _count;
	int _flagX, _flagY;
	int _ratCloakX, _ratCloakY;


	//button
	BUTTON _start;
	BUTTON _exit;



	bool _change;

public:
	virtual HRESULT init(Player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScene();

	void controlFrame();

	void backInit();
	void middleInit();
	void frontInit();



	void backRender();
	void middleRender();
	void frontRender();
};

