#pragma once
#include "singletonBase.h"
#include <vector>

class Cursor;

enum EVENT_TYPE {
	EVENT_TYPE_FIXED,
	EVENT_TYPE_RANDOM,
	END_EVENT_TYPE
};

enum EVENT_META {
	EVENT_META_NULL,
	EVENT_META_SCRIPTNUM,
	EVENT_META_BUTTONNUM,
	END_EVENT_META
};


class eventManager : public singletonBase<eventManager>
{
private:
	typedef vector<LPCWCHAR>			dialog;
	typedef vector<LPCWCHAR>::iterator	dialogIter;

	typedef vector<wstring>				battleLog;
	typedef vector<wstring>::iterator	battleIter;

private:
	Cursor* _cursor;

	//�� ���� �̹��� ���
	dImage* _eventFrame;
	dImage* _illusteFrame;
	dImage* _buttonFrame;
	dImage* _rope;

	//�Ϸ���Ʈ ��ġ(����) & ��ư �浹��Ʈ
	float _x, _y;
	RECT _buttonRECT[3];

	//�̺�Ʈ ����
	dImage* _illuste;
	int _type;
	int _num;
	int _selectedButton;


	//��ȭ log�� ���� vector
	WCHAR _currentFileName[128];
	dialog _eventMetaData;
	int _scriptNum;
	int _buttonNum;


	//�̺�Ʈ ������
	bool _open;

	//���� log�� ���� vector
	battleLog _battleLog;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void printText();

	void loadEvent(int num, int type = EVENT_TYPE_FIXED);
	void loadMetaData();

	void registerIlluste();

	//==================  �α� �߰�  ==================//






	int getSelectedButton() { return _selectedButton; }
	void setSelectedButton(int button) { _selectedButton = button; }

	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }

	battleLog* getBattleLog() { return &_battleLog; }
};