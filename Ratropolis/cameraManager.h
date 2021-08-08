#pragma once
#include "singletonBase.h"

#define FADE	1

enum CAMERAFADE {
	FADEOUT = -1,
	NORMAL,
	FADEIN,
	ENDFADE
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	//카메라가 비추는 화면 크기(WINSIZEX, WINSIZEY)와 좌표(left, right, top, bottom)
	D2D1_RECT_F _screen;

	float _backWidth, _backHeight;	//backDC 크기
	float _frontWidth, _frontHeight;	//frontDC 크기


	//fade
	dImage* _fadeScreen;
	float _alpha;
	CAMERAFADE _fade;


	//카메라 설정값
	float _zoom;
	float _count;	//진동할 때 사용하는 count
	float _ratioX;	//중심점 위치 비율 (x)
	float _ratioY;	//중심점 위치 비율 (y)
	float _camY;	//카메라 올리고 내리고
	bool _onMove;	//카메라 올리고 내리고 판별

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	//카메라 위치(screen) 갱신
	void updateScreen(float standardX, float standardY);
	void moveCam(int direct);
	void resetCam();

	//FadeIN, FadeOUT
	void fade();
	void fadeIn();
	void fadeOut();

	//zoom In/Out
	void changeZoom(float num = 0.01);
	void resetZoom();

	//카메라 진동
	void vibrateScreen(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);
	void vibrateScreenOut(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);

	//카메라 출력
	void render(float destX, float destY);

	//카메라 예외처리
	void onWindow(float& x, float& y);

	void setBackScreenSize(float width, float height);

	//============ 접근자 ============//
	D2D1_RECT_F getScreen() { return _screen; }

	//void setFrontScreenSize(float width, float height) { _frontWidth = width, _frontHeight = height; }
	float getBackScreenWidth() { return _backWidth; }
	float getBackScreenHeight() { return _backHeight; }

	float getAlpha() { return _alpha; }

	void setFade(CAMERAFADE fade) { _fade = fade; }
	CAMERAFADE getFade() { return _fade; }

	float getZoom() { return _zoom; }

	void setRatioX(float ratio) { _ratioX = ratio; }
	float getRatioX() { return _ratioX; }
	void setRatioY(float ratio) { _ratioY = ratio; }
	float getRatioY() { return _ratioY; }

	void setCamY(float count) { _camY = count; }
	float getCamY() { return _camY; }

	void setMove(bool b) { _onMove = b; }
	bool getMove() { return _onMove; }
};

