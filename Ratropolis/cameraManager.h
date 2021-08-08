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
	//ī�޶� ���ߴ� ȭ�� ũ��(WINSIZEX, WINSIZEY)�� ��ǥ(left, right, top, bottom)
	D2D1_RECT_F _screen;

	float _backWidth, _backHeight;	//backDC ũ��
	float _frontWidth, _frontHeight;	//frontDC ũ��


	//fade
	dImage* _fadeScreen;
	float _alpha;
	CAMERAFADE _fade;


	//ī�޶� ������
	float _zoom;
	float _count;	//������ �� ����ϴ� count
	float _ratioX;	//�߽��� ��ġ ���� (x)
	float _ratioY;	//�߽��� ��ġ ���� (y)
	float _camY;	//ī�޶� �ø��� ������
	bool _onMove;	//ī�޶� �ø��� ������ �Ǻ�

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	//ī�޶� ��ġ(screen) ����
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

	//ī�޶� ����
	void vibrateScreen(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);
	void vibrateScreenOut(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);

	//ī�޶� ���
	void render(float destX, float destY);

	//ī�޶� ����ó��
	void onWindow(float& x, float& y);

	void setBackScreenSize(float width, float height);

	//============ ������ ============//
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

