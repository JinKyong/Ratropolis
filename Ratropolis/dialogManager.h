#pragma once
#include "singletonBase.h"
#include <vector>

class dialogManager : public singletonBase<dialogManager>
{
private:
	typedef vector<LPCWCHAR>			dialog;
	typedef vector<LPCWCHAR>::iterator	dialogIter;

	typedef vector<wstring>				battleLog;
	typedef vector<wstring>::iterator	battleIter;

private:
	//��ȭâ
	dImage* _back;
	dImage* _border;
	dImage* _leftBorder;
	dImage* _rightBorder;


	//��ȭ log�� ���� vector
	LPCWCHAR _currentFileName;
	dialog _storyMetaData;
	int _metaDataNum;

	//��� ��ȣ, ���� ��� ��, �ӵ� ī��Ʈ
	int _scriptNum;
	int _size;
	float _count;

	//���̾�α� ��� ����
	bool _print;



	//���� log�� ���� vector
	battleLog _battleLog;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadMetaData(LPCWCHAR fileName);
	void loadScript();



	void resetTimer();
	//==================  �α� �߰�  ==================//









	bool getPrint() { return _print; }
	void setPrint(bool print) { _print = print; }

	battleLog* getBattleLog() { return &_battleLog; }
};