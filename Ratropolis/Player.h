#pragma once
#include "Cursor.h"

class Card;

typedef struct tagDefaultStatus {
	int gold;			//��
	int prize;			//�����
	int tax;			//����
	int currentCivil;	//���� �ù�
	int maxCivil;		//��ü �ù�
	int wave;			//���� ���̺�
	//int poison;			//������
}DEFAULT_STAT;

class Player
{
private:
	Cursor* _cursor;

	//camera����
	float _camX, _camY;

	DEFAULT_STAT _defaultStat;		//�⺻ ����(��, �ù� ��)
	int _level;						//������ ����
	float _count;					//���� ī��Ʈ

	//���� ī��
	Card* _selectedCard;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playGame();
	void controlKeyboard();

	void changeGold(int num);
	void changeCivil(int num);
	void changeMaxCivil(int num);
	void changeCard(Card* card);




	//======================================== ������ ========================================//
	Cursor* getCursor() { return _cursor; }

	float getCamX() { return _camX; }
	void setCamX(float camX) { _camX = camX; }
	float getCamY() { return _camY; }
	void setCamY(float camY) { _camY = camY; }

	DEFAULT_STAT getDefaultStat() { return _defaultStat; }

	Card* getCard() { return _selectedCard; }
	void setCard(Card* card) { _selectedCard = card; }
};