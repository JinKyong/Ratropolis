#pragma once
#include "Menu.h"

class Player;

class InGameMenu
{
private:
	Player* _player;

//Images
private:
	//LEFT TOP HUD
	dImage* _topHUD;		//좌상단 HUD
	dImage* _goldIcon;		//골드 아이콘
	dImage* _ratsIcon;		//쥐 아이콘
	dImage* _waveIcon;		//웨이브 아이콘
	//dImage* _poisonIcon;


	//OTHER HUD
	dImage* _defaultHUD;			//기본 HUD(네모 박스)
	dImage* _defaultHUDHighlite;	//기본 HUD 강조(충돌 시)


	//LEFT BOTTOM ICON
	dImage* _playerSkillIcon;		//플레이어 스킬 아이콘
	dImage* _cardBagIcon;			//카드가방 아이콘


	//RIGHT TOP ICON
	dImage* _allCardsIcon;			//모든 카드 아이콘
	dImage* _advisorIcon;			//조언자 아이콘
	dImage* _pauseIcon;				//일시정시 아이콘
	dImage* _optionIcon;			//옵션 아이콘


	//RIGHT BOTTOM ICON
	dImage* _redrawIcon;			//다시 뽑기 아이콘
	dImage* _cardGraveIcon;			//카드 무덤 아이콘


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayer(Player* player);

	void leftTopRender();
	void leftBottomRender();
	void rightTopRender();
	void rightBottomRender();
};

