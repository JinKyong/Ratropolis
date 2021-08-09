#pragma once
#include "singletonBase.h"

class uiManager : public singletonBase<uiManager>
{
private:

private:
	//���� �ù�, ���̺�
	int _gold;			//��
	int _prize;			//�����
	int _tax;			//����
	int _currentCivil;	//���� �ù�
	int _maxCivil;		//��ü �ù�
	int _wave;			//���� ���̺�

	//��
	int _deck;			//���� ���
	int _grave;			//���� ���
	int _remain;		//���� ���

	//��ų
	int _level;			//��ų ����



	//�޴� ����Ʈ

	//���� �޴�


	bool _open;

public:
	HRESULT init();
	void release();
	void update();
	void render();

/*
	UpMenu* addUpMenu(string menuName, UpMenu* menu);
	DownMenu* addDownMenu(string menuName, DownMenu* menu);
	HRESULT changeUpMenu(string menuName);
	HRESULT changeDownMenu(string menuName);*/





	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }
};

