#pragma once
#include "singletonBase.h"

enum RENDERTARGET_TYPE {
	RENDERTARGET_TYPE_STATIC,
	RENDERTARGET_TYPE_BACKBUFFER,
	RENDERTARGET_TYPE_UI,
	END_RENDERTARGET_TYPE
};

class dtdManager : public singletonBase<dtdManager>
{
private:
	//Factory, RenderTarget
	ID2D1Factory			*_dFactory;
	ID2D1HwndRenderTarget	*_dRenderTarget;
	ID2D1BitmapRenderTarget	*_dBitRenderTarget;
	ID2D1BitmapRenderTarget	*_dBackRenderTarget;
	ID2D1BitmapRenderTarget *_dUIRenderTarget;

	ID2D1BitmapRenderTarget	*_pastRenderTarget;
	ID2D1BitmapRenderTarget	*_currentRenderTarget;

	ID2D1Bitmap				*_dBitmap;
	ID2D1Bitmap				*_dBackBitmap;
	ID2D1Bitmap				*_dUIBitmap;

	//Brush
	ID2D1BitmapBrush		*_dBitmapBrush;
	ID2D1SolidColorBrush	*_dBrush;

	//Text
	IDWriteFactory			*_dWFactory;
	IDWriteTextFormat		*_dWDefaultFormat;
	IDWriteTextFormat		*_dWCustomFormat;

	bool _clear;

public:
	HRESULT init();
	void release();
	void render(float destX, float destY, float width, float height);

	void beginDraw();
	void endDraw();
	void changeRenderTarget(RENDERTARGET_TYPE type);
	void changeRenderTargetPast();

	//사각형
	void Rectangle(D2D1_RECT_F rc);
	void Rectangle(RECT rc);

	//텍스트 출력(front)
	void printTextF(LPCWCHAR text, float x, float y, int width, int height);
	void printTextF(LPCWCHAR text, float x, float y, int width, int height, float size);
	void printTextF(LPCWCHAR text, D2D1_RECT_F rc);
	void printTextF(LPCWCHAR text, D2D1_RECT_F rc, float size);

	//텍스트 출력(backBuffer)
	void printText(LPCWCHAR text, float x, float y, int width, int height);
	void printText(LPCWCHAR text, float x, float y, int width, int height, float size, bool central = false);
	void printText(LPCWCHAR text, D2D1_RECT_F rc);
	void printText(LPCWCHAR text, D2D1_RECT_F rc, float size, bool central = false);


	//각종 변환
	void setRotate(float angle, float x, float y);					//회전
	void setReverse(int axis, float x, float y);					//반전
	void setScale(float sizeX, float sizeY, float x, float y);		//크기조절
	//리셋
	void resetTransform();

	//백버퍼 사이즈 재설정
	void setBackBuffer(float width, float height);

	void resetBrushColor();
	D2D1_COLOR_F getBrushColor() { return _dBrush->GetColor(); }
	void setBrushColor(D2D1_COLOR_F color) { _dBrush->SetColor(color); }

	ID2D1SolidColorBrush* getBrush() { return _dBrush; }

	ID2D1HwndRenderTarget* getRenderTarget() { return _dRenderTarget; }
	ID2D1BitmapRenderTarget* getBitRenderTarget() { return _dBitRenderTarget; }
	ID2D1BitmapRenderTarget* getBackRenderTarget() { return _dBackRenderTarget; }
	ID2D1BitmapRenderTarget* getCurrentRenderTarget() { return _currentRenderTarget; }

	void setClear(bool clear) { _clear = clear; }
	bool getClear() { return _clear; }
};

