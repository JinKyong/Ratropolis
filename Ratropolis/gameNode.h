#pragma once

class gameNode
{
private:

public:
	gameNode();
	virtual ~gameNode();


	//HRESULT 마소 전용 반환형식인데
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();			//그리기 함수

	void cursorOnWindow();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};