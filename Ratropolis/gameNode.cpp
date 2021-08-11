#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	PRINTMANAGER->init();
	STREAMMANAGER->init();
	DTDMANAGER->init();
	CAMERAMANAGER->init();
	TXTDATA->init();
	SOUNDMANAGER->init();
	UIMANAGER->init();
	CARDDICT->init();

	return S_OK;
}

void gameNode::release()
{
	//KillTimer(_hWnd, 1);
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();

	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	PRINTMANAGER->release();
	PRINTMANAGER->releaseSingleton();

	STREAMMANAGER->release();
	STREAMMANAGER->releaseSingleton();

	DTDMANAGER->release();
	DTDMANAGER->releaseSingleton();

	CAMERAMANAGER->release();
	CAMERAMANAGER->releaseSingleton();

	TXTDATA->release();
	TXTDATA->releaseSingleton();

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	UIMANAGER->release();
	UIMANAGER->releaseSingleton();

	CARDDICT->release();
	CARDDICT->releaseSingleton();

	CoUninitialize();

}

void gameNode::update()
{
}

void gameNode::render()
{
}

void gameNode::cursorOnWindow()
{
	RECT rc;
	//윈도우 크기 RECT 생성
	GetClientRect(_hWnd, &rc);

	POINT pt1, pt2;

	//윈도우 LeftTop, RightTop점 좌표
	pt1.x = rc.left;
	pt1.y = rc.top;
	pt2.x = rc.right;
	pt2.y = rc.bottom;

	//변환
	ClientToScreen(_hWnd, &pt1);
	ClientToScreen(_hWnd, &pt2);

	//대입
	rc.left = pt1.x;
	rc.top = pt1.y;
	rc.right = pt2.x;
	rc.bottom = pt2.y;

	//마우스 고정
	ClipCursor(&rc);
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SHORT delta;
	switch (iMessage)
	{
		//윈도우 생성시 호출
	case WM_CREATE:
		//ShowCursor(false);
		break;

		//마우스 움직이면 호출
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;

		//마우스 휠동작시 호출
	case WM_MOUSEWHEEL:
		delta = HIWORD(wParam);
		delta = delta / WHEEL_DELTA;
		CAMERAMANAGER->changeZoom((float)delta / 10);
		break;


	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_ACTIVATEAPP:
		//cursorOnWindow();
		break;

		//윈도우 창 부쉬는(?) 
	case WM_DESTROY:
		//윈도우 종료함수
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}