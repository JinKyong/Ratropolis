#pragma once
#include "singletonBase.h"

class uiManager : public singletonBase<uiManager>
{
private:

private:
	D2D1_RECT_F _screen;

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





	D2D1_RECT_F getScreen() { return _screen; }

	bool getOpen() { return _open; }
	void setOpen(bool open) { _open = open; }
};

