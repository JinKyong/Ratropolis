#pragma once
#include "singletonBase.h"

class uiManager : public singletonBase<uiManager>
{
private:

private:
	int _gold;

	//�޴� ����Ʈ

	//���� �޴�


	bool _open;

public:
	HRESULT init();
	void release();
	void update();
	void renderDown();
	void renderUp();
/*
	UpMenu* addUpMenu(string menuName, UpMenu* menu);
	DownMenu* addDownMenu(string menuName, DownMenu* menu);
	HRESULT changeUpMenu(string menuName);
	HRESULT changeDownMenu(string menuName);*/





	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }
};

