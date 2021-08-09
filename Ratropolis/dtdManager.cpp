#include "stdafx.h"
#include "dtdManager.h"

HRESULT dtdManager::init()
{
	release();

	_clear = true;

	HRESULT hr;

	//Fafctory 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dFactory);

	//Factory가 생성되었으면 RenderTarget 생성
	if (SUCCEEDED(hr)) {
		hr = _dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(_hWnd, SizeU(WINSIZEX, WINSIZEY)),
			&_dRenderTarget);
	}

	//RenderTarget과 호환되는 또 다른 RenderTarget(=BackBuffer) 생성
	//if (SUCCEEDED(hr)) {
	//	hr = _dRenderTarget->CreateCompatibleRenderTarget(SizeF(WINSIZEX, WINSIZEY),
	//		&_dBitRenderTarget);
	//}

	//RenderTarget이 생성되었으면 Brush 생성
	if (SUCCEEDED(hr)) {
		hr = _dRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Black), &_dBrush);
	}

	//Brush가 생성되었으면 Text Factory 생성
	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&_dWFactory)
		);
	}

	//Text Factory가 생성되었으면 Text Format 생성
	if (SUCCEEDED(hr)) {
		hr = _dWFactory->CreateTextFormat(
			L"모리스9",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15,
			L"ko-kr",
			&_dWDefaultFormat
		);
	}

	//Text Format이 생성되었으면 기본값(가운데 정렬) 설정
	/*if (SUCCEEDED(hr)) {
		hr = _dWFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		if (SUCCEEDED(hr)) {
			hr = _dWFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}
	}*/

	//wincodec(이미지 로더)을 사용하기 위함
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	_pastRenderTarget = _currentRenderTarget = NULL;

	return S_OK;
}

void dtdManager::release()
{
	//동적 할당한 객체들 모두 해제
	if (_dFactory)			SAFE_RELEASE2(_dFactory);
	if (_dRenderTarget)		SAFE_RELEASE2(_dRenderTarget);
	if (_dBitRenderTarget)	SAFE_RELEASE2(_dBitRenderTarget);
	if (_dBackRenderTarget) SAFE_RELEASE2(_dBackRenderTarget);
	if (_dUIRenderTarget)	SAFE_RELEASE2(_dUIRenderTarget);

	if (_dBitmap)			SAFE_RELEASE2(_dBitmap);
	if (_dBackBitmap)		SAFE_RELEASE2(_dBackBitmap);
	if (_dUIBitmap)			SAFE_RELEASE2(_dUIBitmap);
	if (_dBrush)			SAFE_RELEASE2(_dBrush);

	if (_dWFactory)			SAFE_RELEASE2(_dWFactory);
	if (_dWDefaultFormat)	SAFE_RELEASE2(_dWDefaultFormat);
	if (_dWCustomFormat)	SAFE_RELEASE2(_dWCustomFormat);
}

void dtdManager::render(float destX, float destY, float width, float height)
{
	if (!_dRenderTarget) return;

	_dRenderTarget->BeginDraw();
	_dRenderTarget->Clear(ColorF(ColorF::Aquamarine));

	//(실제 게임 화면)
	D2D1_RECT_F dest = { destX, destY, destX + width, destY + height };
	D2D1_RECT_F sour = CAMERAMANAGER->getScreen();
	D2D1_RECT_F sourUI = { 0, 0, WINSIZEX, WINSIZEY };

	//배경
	_dRenderTarget->DrawBitmap(_dBackBitmap, dest,
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sour);
	//오브젝트
	_dRenderTarget->DrawBitmap(_dBitmap, dest,
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sour);
	//UI
	_dRenderTarget->DrawBitmap(_dUIBitmap, dest,
		1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourUI);

	//CAMERAMANAGER->fade();

	_dRenderTarget->EndDraw();
}

void dtdManager::beginDraw()
{
	if (_currentRenderTarget) {
		_currentRenderTarget->BeginDraw();
		_currentRenderTarget->Clear();
	}
}

void dtdManager::endDraw()
{
	if (_currentRenderTarget) {
		//Background
		if(_currentRenderTarget == _dBackRenderTarget)
			_currentRenderTarget->GetBitmap(&_dBackBitmap);
		//BackBuffer
		else if (_currentRenderTarget == _dBitRenderTarget)
			_currentRenderTarget->GetBitmap(&_dBitmap);
		//UI
		else if(_currentRenderTarget == _dUIRenderTarget)
			_currentRenderTarget->GetBitmap(&_dUIBitmap);

		_currentRenderTarget->EndDraw();
	}
}

void dtdManager::changeRenderTarget(RENDERTARGET_TYPE type)
{
	if (type >= END_RENDERTARGET_TYPE) return;
	_pastRenderTarget = _currentRenderTarget;

	switch (type) {
	case RENDERTARGET_TYPE_STATIC:
		_currentRenderTarget = _dBackRenderTarget;
		break;

	case RENDERTARGET_TYPE_BACKBUFFER:
		_currentRenderTarget = _dBitRenderTarget;
		break;

	case RENDERTARGET_TYPE_UI:
		_currentRenderTarget = _dUIRenderTarget;
		break;

	default:
		break;
	}
}

void dtdManager::changeRenderTargetPast()
{
	_currentRenderTarget = _pastRenderTarget;
	_pastRenderTarget = NULL;
}

void dtdManager::Rectangle(D2D1_RECT_F rc)
{
	if (_currentRenderTarget)
		_currentRenderTarget->DrawRectangle(rc, _dBrush);
}

void dtdManager::Rectangle(RECT rc)
{
	D2D1_RECT_F rect = { rc.left, rc.top, rc.right, rc.bottom };

	if (_currentRenderTarget)
		_currentRenderTarget->DrawRectangle(rect, _dBrush);
}

void dtdManager::printTextF(LPCWCHAR text, float x, float y, int width, int height)
{
	_dRenderTarget->DrawTextA(text, lstrlenW(text), _dWDefaultFormat, dRectMakeCenter(x, y, width, height), _dBrush);
}

void dtdManager::printTextF(LPCWCHAR text, float x, float y, int width, int height, float size)
{
	if (_dWCustomFormat) {
		if (_dWCustomFormat->GetFontSize() != size) {
			SAFE_RELEASE2(_dWCustomFormat);

			_dWFactory->CreateTextFormat(
				L"모리스9",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				size,
				L"ko-kr",
				&_dWCustomFormat
			);
		}
	}
	else {
		_dWFactory->CreateTextFormat(
			L"모리스9",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"ko-kr",
			&_dWCustomFormat
		);
	}

	_dRenderTarget->DrawTextA(text, lstrlenW(text), _dWCustomFormat, dRectMakeCenter(x, y, width, height), _dBrush);
}

void dtdManager::printTextF(LPCWCHAR text, D2D1_RECT_F rc)
{
	_dRenderTarget->DrawTextA(text, lstrlenW(text), _dWDefaultFormat, rc, _dBrush);
}

void dtdManager::printTextF(LPCWCHAR text, D2D1_RECT_F rc, float size)
{
	if (_dWCustomFormat) {
		if (_dWCustomFormat->GetFontSize() != size) {
			SAFE_RELEASE2(_dWCustomFormat);

			_dWFactory->CreateTextFormat(
				L"모리스9",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				size,
				L"ko-kr",
				&_dWCustomFormat
			);
		}
	}
	else {
		_dWFactory->CreateTextFormat(
			L"모리스9",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"ko-kr",
			&_dWCustomFormat
		);
	}

	_dRenderTarget->DrawTextA(text, lstrlenW(text), _dWCustomFormat, rc, _dBrush);
}

void dtdManager::printText(LPCWCHAR text, float x, float y, int width, int height)
{
	_currentRenderTarget->DrawTextA(text, lstrlenW(text), _dWDefaultFormat, dRectMakeCenter(x, y, width, height), _dBrush);
}

void dtdManager::printText(LPCWCHAR text, float x, float y, int width, int height, float size, bool central)
{
	if (_dWCustomFormat) {
		if (_dWCustomFormat->GetFontSize() != size) {
			SAFE_RELEASE2(_dWCustomFormat);

			_dWFactory->CreateTextFormat(
				L"모리스9",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				size,
				L"ko-kr",
				&_dWCustomFormat
			);
		}
	}
	else {
		_dWFactory->CreateTextFormat(
			L"모리스9",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"ko-kr",
			&_dWCustomFormat
		);
	}

	if (central) {
		_dWCustomFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		_dWCustomFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	_currentRenderTarget->DrawTextA(text, lstrlenW(text), _dWCustomFormat, dRectMakeCenter(x, y, width, height), _dBrush);

	SAFE_RELEASE2(_dWCustomFormat);
}

void dtdManager::printText(LPCWCHAR text, D2D1_RECT_F rc)
{
	_currentRenderTarget->DrawTextA(text, lstrlenW(text), _dWDefaultFormat, rc, _dBrush);
}

void dtdManager::printText(LPCWCHAR text, D2D1_RECT_F rc, float size, bool central)
{
	if (_dWCustomFormat) {
		if (_dWCustomFormat->GetFontSize() != size) {
			SAFE_RELEASE2(_dWCustomFormat);

			_dWFactory->CreateTextFormat(
				L"모리스9",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				size,
				L"ko-kr",
				&_dWCustomFormat
			);
		}
	}
	else {
		_dWFactory->CreateTextFormat(
			L"모리스9",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"ko-kr",
			&_dWCustomFormat
		);
	}
	
	if (central) {
		_dWCustomFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		_dWCustomFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	_currentRenderTarget->DrawTextA(text, lstrlenW(text), _dWCustomFormat, rc, _dBrush);

	SAFE_RELEASE2(_dWCustomFormat);
}

void dtdManager::setRotate(float angle, float x, float y)
{
	_currentRenderTarget->SetTransform(Matrix3x2F::Rotation(angle, Point2F(x, y)));
}

void dtdManager::setReverse(int axis, float offsetX, float offsetY)
{
	//axis == 0 y축 (좌우 반전)
	//axis == 1 x축 (상하 반전)

	D2D1_MATRIX_3X2_F m;

	if (axis == 0) {
		m._11 = -1; m._12 = 0;
		m._21 = 0; m._22 = 1;
	}
	else if (axis == 1) {
		m._11 = 1; m._12 = 0;
		m._21 = 0; m._22 = -1;
	}
	m._31 = offsetX; m._32 = offsetY;

	_currentRenderTarget->SetTransform(m);
}

void dtdManager::setScale(float sizeX, float sizeY, float x, float y)
{
	_currentRenderTarget->SetTransform(Matrix3x2F::Scale(SizeF(sizeX, sizeY), Point2F(x, y)));
}

void dtdManager::resetTransform()
{
	_currentRenderTarget->SetTransform(Matrix3x2F::Identity());
}

void dtdManager::setBackBuffer(float width, float height)
{
	SAFE_RELEASE2(_dBitRenderTarget);
	SAFE_RELEASE2(_dBackRenderTarget);
	SAFE_RELEASE2(_dUIRenderTarget);

	if (_dRenderTarget) {
		_dRenderTarget->CreateCompatibleRenderTarget(SizeF(width, height), &_dBitRenderTarget);
		_dRenderTarget->CreateCompatibleRenderTarget(SizeF(width, height), &_dBackRenderTarget);
		_dRenderTarget->CreateCompatibleRenderTarget(SizeF(WINSIZEX, WINSIZEY), &_dUIRenderTarget);

		changeRenderTarget(RENDERTARGET_TYPE_BACKBUFFER);
	}
}

void dtdManager::resetBrushColor()
{
	_dBrush->SetColor(ColorF(ColorF::Black));
}