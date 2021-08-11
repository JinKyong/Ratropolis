#pragma once

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

enum CURSOR_TYPE {
	CURSOR_TYPE_DEFAULT,
	CURSOR_TYPE_CLICK,
	CURSOR_TYPE_GRAB,
	CURSOR_TYPE_ATTACK,
	CURSOR_TYPE_MINING,
	END_CURSOR_TYPE
};

class Player
{
private:
	//cursor
	dImage* _cursor[END_CURSOR_TYPE];
	dImage* _currentCursor;

	float _x, _y;
	RECT _body;

	//camera����
	float _camX, _camY;

	DEFAULT_STAT _defaultStat;		//�⺻ ����(��, �ù� ��)
	int _level;						//������ ����

	//���� ī��
	Card* _selectedCard;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playGame();
	void controlMouse();
	void controlKeyboard();

	void changeCursor(CURSOR_TYPE type);

	void changeGold(int num);
	void changeCivil(int num);
	void changeMaxCivil(int num);
	void changeCard(Card* card);





	static DWORD CALLBACK threadCollectTax(LPVOID lpParameter);


	//======================================== ������ ========================================//
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }

	float getCamX() { return _camX; }
	void setCamX(float camX) { _camX = camX; }
	float getCamY() { return _camY; }
	void setCamY(float camY) { _camY = camY; }

	DEFAULT_STAT getDefaultStat() { return _defaultStat; }

	Card* getCard() { return _selectedCard; }
};