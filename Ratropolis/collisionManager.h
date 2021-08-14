#pragma once
#include "singletonBase.h"
#include <vector>

class Player;
class Card;
class Building;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Player* _player;

public:
	collisionManager() {};
	~collisionManager() {};

	HRESULT init();
	void release();
	
	//Ŀ���� ���(�ǹ�) �浹(backRT)
	void buildingsWithCursor(Building* building, float x, float y);


	//Ŀ���� ī��(����Ʈ) �浹(UIRT)
	Card* cardListWithCursor(Card* card, float x, float y);		//ī��(����Ʈ)�� Ŀ�� �浹
	Card* selectedCard(vector<Card*> cards, float x, float y);	//ī��(����Ʈ)�� Ŀ��(����) �浹


	//Ŀ���� ī��(�ڵ�) �浹(cardRT)
	void handsWithCursor();				//ī��(�ڵ�)�� Ŀ�� �浹
	bool grabbedCard();					//ī��(�ڵ�) �巡��(����)
	void handsWithUseBox(Card* card);	//ī��(�ڵ�) ���
	void buttonWithCursor();			//��ư ����
};