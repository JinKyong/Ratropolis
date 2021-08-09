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
	dImage* _topHUD;		//�»�� HUD
	dImage* _goldIcon;		//��� ������
	dImage* _ratsIcon;		//�� ������
	dImage* _waveIcon;		//���̺� ������
	//dImage* _poisonIcon;


	//OTHER HUD
	dImage* _defaultHUD;			//�⺻ HUD(�׸� �ڽ�)
	dImage* _defaultHUDHighlite;	//�⺻ HUD ����(�浹 ��)


	//LEFT BOTTOM ICON
	dImage* _playerSkillIcon;		//�÷��̾� ��ų ������
	dImage* _cardBagIcon;			//ī�尡�� ������


	//RIGHT TOP ICON
	dImage* _allCardsIcon;			//��� ī�� ������
	dImage* _advisorIcon;			//������ ������
	dImage* _pauseIcon;				//�Ͻ����� ������
	dImage* _optionIcon;			//�ɼ� ������


	//RIGHT BOTTOM ICON
	dImage* _redrawIcon;			//�ٽ� �̱� ������
	dImage* _cardGraveIcon;			//ī�� ���� ������


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

