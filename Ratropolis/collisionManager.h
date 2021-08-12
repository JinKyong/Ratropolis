#pragma once
#include "singletonBase.h"
#include <vector>

class Player;
class Card;

class collisionManager : public singletonBase<collisionManager>
{
private:
	Player* _player;

public:
	collisionManager() {};
	~collisionManager() {};

	HRESULT init();
	void release();
	

	Card* cardListWithCursor(vector<Card*> cards, float x, float y);	//ī��(����Ʈ)�� Ŀ�� �浹
	Card* selectedCard(vector<Card*> cards, float x, float y);			//ī��(����Ʈ)�� Ŀ��(����) �浹

	void handsWithCursor();				//ī��(�ڵ�)�� Ŀ�� �浹

	//Ŀ�� ���۽� �浹
	bool grabbedCard();					//ī��(�ڵ�) �巡��(����)
	void handsWithUseBox(Card* card);	//ī��(�ڵ�) ���
	void buttonWithCursor();			//��ư ����
};