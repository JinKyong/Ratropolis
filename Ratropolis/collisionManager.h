#pragma once
#include "singletonBase.h"
#include "Button.h"
#include <vector>

class Player;
class Card;
class Building;
class WaveBar;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Player* _player;

	collisionManager() {};
	friend singletonBase<collisionManager>;

public:	
	HRESULT init();
	void release();
	
	//Ŀ���� ���(�ǹ�) �浹(backRT)
	void buildingsWithCursor(Building* building, float x, float y);
	bool spaceWithCursor(RECT space, float x, float y);
	void selectedButtonSnE(float x, float y);			//Shop & Evnet ��ư ����


	//Ŀ���� ī��(����Ʈ) �浹(UIRT)
	Card* cardListWithCursor(Card* card, float x, float y);		//ī��(����Ʈ)�� Ŀ�� �浹
	Card* selectedCard(vector<Card*> cards, float x, float y);	//ī��(����Ʈ)�� Ŀ��(����) �浹
	void selectedButtonUI(float x, float y);					//UI��ư ����
	void barWithCursor(float x, float y);			//���̺� �ٿ� Ŀ�� �浹


	//Ŀ���� ��ư(�̺�Ʈ) �浹(cardRT)
	void selectButtonWithCursor(RECT* button, float x, float y);	//��ư(�̺�Ʈ)�� Ŀ�� �浹


	//Ŀ���� ī��(�ڵ�) �浹(cardRT)
	void handsWithCursor(float x, float y);				//ī��(�ڵ�)�� Ŀ�� �浹
	bool grabbedCard(float x, float y);					//ī��(�ڵ�) �巡��(����)
	void handsWithUseBox(Card* card, float x, float y);	//ī��(�ڵ�) ���

	void buttonWithCursor(PBUTTON button, float x, float y);	//��ư �浹
};