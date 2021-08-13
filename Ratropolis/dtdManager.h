#pragma once
#include "singletonBase.h"

enum RENDERTARGET_TYPE {
	RENDERTARGET_TYPE_STATIC,
	RENDERTARGET_TYPE_BACKBUFFER,
	RENDERTARGET_TYPE_UI,
	RENDERTARGET_TYPE_CARD,
	END_RENDERTARGET_TYPE
};

class dtdManager : public singletonBase<dtdManager>
{
private:
	//Factory, RenderTarget(�׷��ִ� ��ü)
	ID2D1Factory			*_dFactory;
	ID2D1HwndRenderTarget	*_dRenderTarget;
	ID2D1BitmapRenderTarget	*_dBitRenderTarget;
	ID2D1BitmapRenderTarget	*_dBackRenderTarget;
	ID2D1BitmapRenderTarget *_dUIRenderTarget;
	ID2D1BitmapRenderTarget *_dCardRenderTarget;

	ID2D1BitmapRenderTarget	*_pastRenderTarget;
	ID2D1BitmapRenderTarget	*_currentRenderTarget;

	//Bitmap(��ȭ��)
	ID2D1Bitmap				*_dBitmap;
	ID2D1Bitmap				*_dBackBitmap;
	ID2D1Bitmap				*_dUIBitmap;
	ID2D1Bitmap				*_dCardBitmap;

	//Brush(��)
	ID2D1BitmapBrush		*_dBitmapBrush;
	ID2D1SolidColorBrush	*_dBrush;

	//Text(��Ʈ ����)
	IDWriteFactory			*_dWFactory;
	IDWriteTextFormat		*_dWDefaultFormat;
	IDWriteTextFormat		*_dWCustomFormat;

	//Device Context
	//int m_dpi = 96;
	//ComPtr<ID2D1Factory1>			_dFactory1;
	//ComPtr<D3D_FEATURE_LEVEL>		_d3FeatureLevel;
	//ComPtr<ID2D1Device>				_dDevice;
	//ComPtr<ID2D1DeviceContext>		_dContext;
	//ComPtr<IDXGISwapChain1>			_d3SwapChain;
	//ComPtr<ID2D1Bitmap1>			_dTargetBitmap;
	//ComPtr<ID3D11Device>			_d3Device;
	//ComPtr<ID3D11DeviceContext>		_d3Context;
	//ComPtr<IDXGIDevice1>			_d3DxgiDevice;

	bool _clear;

public:
	HRESULT init();
	void release();
	void render(float destX, float destY, float width, float height);

	void beginDraw(bool clear = true);
	void endDraw();
	void changeRenderTarget(RENDERTARGET_TYPE type);
	void changeRenderTargetPast();

	//�簢��
	void Rectangle(D2D1_RECT_F rc);
	void Rectangle(RECT rc);

	//�ؽ�Ʈ ���(front)
	void printTextF(LPCWCHAR text, float x, float y, int width, int height);
	void printTextF(LPCWCHAR text, float x, float y, int width, int height, float size);
	void printTextF(LPCWCHAR text, D2D1_RECT_F rc);
	void printTextF(LPCWCHAR text, D2D1_RECT_F rc, float size);

	//�ؽ�Ʈ ���(backBuffer)
	void printText(LPCWCHAR text, float x, float y, int width, int height);
	void printText(LPCWCHAR text, float x, float y, int width, int height, float size, bool centralW = false, bool centralH = false);
	void printText(LPCWCHAR text, D2D1_RECT_F rc);
	void printText(LPCWCHAR text, D2D1_RECT_F rc, float size, bool centralW = false, bool centralH = false);


	//���� ��ȯ
	void setRotate(float angle, float x, float y);					//ȸ��
	void setReverse(int axis, float x, float y);					//����
	void setScale(float sizeX, float sizeY, float x, float y);		//ũ������
	//����
	void resetTransform();

	//���� ȿ��





	//����� ������ �缳��
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

