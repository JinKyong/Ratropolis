#include "stdafx.h"
#include "dImage.h"

dImage::dImage()
	: _imageInfo(NULL),
	_fileName(NULL),
	_wicFactory(NULL),
	_bitDecoder(NULL),
	_bitFrame(NULL),
	_wicConverter(NULL)
{
}

dImage::~dImage()
{
}

HRESULT dImage::init(LPCWCHAR fileName, int width, int height)
{
	if (_imageInfo != NULL) release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);

	HRESULT hr;

	//WICFactory 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	//WICFactory생성 후 decoder생성(이미지 파일 정보 담은 컨테이너)
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateDecoderFromFilename(_fileName, nullptr,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_bitDecoder);
	}

	//decoder에서 이미지 프레임 추출
	if (SUCCEEDED(hr)) {
		hr = _bitDecoder->GetFrame(0, &_bitFrame);
	}

	//컨버터 생성
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateFormatConverter(&_wicConverter);
	}

	//컨버터에 추출한 이미지 프레임 넣어서 변환
	if (SUCCEEDED(hr)) {
		_wicConverter->Initialize(_bitFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
	}

	//실제 그리기 영역에 비트맵 형식으로 로드
	if (SUCCEEDED(hr)) {
		hr = DTDMANAGER->getRenderTarget()->CreateBitmapFromWicBitmap(_wicConverter, nullptr, &_imageInfo->bitMap);
	}

	return S_OK;
}

HRESULT dImage::init(LPCWCHAR fileName, int width, int height, int frameX, int frameY)
{
	if (_imageInfo != NULL) release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	int len = lstrlenW(fileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, fileName);

	HRESULT hr = E_FAIL;

	//WICFactory 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	//WICFactory생성 후 decoder생성(이미지 파일 정보 담은 컨테이너)
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateDecoderFromFilename(_fileName, nullptr,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_bitDecoder);
	}

	//decoder에서 이미지 프레임 추출
	if (SUCCEEDED(hr)) {
		hr = _bitDecoder->GetFrame(0, &_bitFrame);
	}

	//컨버터 생성
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateFormatConverter(&_wicConverter);
	}

	//컨버터에 추출한 이미지 프레임 넣어서 변환
	if (SUCCEEDED(hr)) {
		_wicConverter->Initialize(_bitFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
	}

	//실제 그리기 영역에 비트맵 형식으로 로드
	if (SUCCEEDED(hr)) {
		hr = DTDMANAGER->getRenderTarget()->CreateBitmapFromWicBitmap(_wicConverter, nullptr, &_imageInfo->bitMap);
	}

	return hr;
}

void dImage::release()
{
	if (_imageInfo)
	{
		//이미지 정보 해제
		SAFE_RELEASE2(_imageInfo->bitMap);
		SAFE_DELETE(_imageInfo);
	}

	SAFE_DELETE(_fileName);
	//이미지 로드용 객체 해제
	SAFE_RELEASE2(_wicFactory);
	SAFE_RELEASE2(_bitDecoder);
	SAFE_RELEASE2(_bitFrame);
	SAFE_RELEASE2(_wicConverter);
}

void dImage::render(float opacity)
{
	D2D1_RECT_F destRect = dRectMake(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::render(float destX, float destY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->width, _imageInfo->height);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	//DTDMANAGER->getBackRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sourWidth, sourHeight);
	//D2D1_RECT_F sourRect = dRectMake(sourX, sourY, sourWidth, sourHeight);

	D2D1_SIZE_F size = _imageInfo->bitMap->GetSize();
	float ratioX = size.width / _imageInfo->width;
	float ratioY = size.height / _imageInfo->height;
	D2D1_RECT_F sourRect = dRectMake(sourX * ratioX, sourY * ratioY, sourWidth * ratioX, sourHeight * ratioY);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::render(D2D1_RECT_F destRECT, D2D1_RECT_F sourRECT, float opacity)
{
	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRECT,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRECT);
}

void dImage::frameRender(float destX, float destY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	D2D1_RECT_F sourRect = dRectMake(
		_imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::frameRender(float destX, float destY, int currentFrameX, int currentFrameY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	//D2D1_RECT_F sourRect = dRectMake(
	//	currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
	//	_imageInfo->frameWidth, _imageInfo->frameHeight);

	D2D1_SIZE_F size = _imageInfo->bitMap->GetSize();
	float ratioX = size.width / _imageInfo->width;
	float ratioY = size.height / _imageInfo->height;
	D2D1_RECT_F sourRect = dRectMake(currentFrameX * _imageInfo->frameWidth * ratioX, currentFrameY * _imageInfo->frameHeight * ratioY,
		_imageInfo->frameWidth * ratioX, _imageInfo->frameHeight * ratioY);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::frameRender(float destX, float destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sizeX, sizeY);
	D2D1_RECT_F sourRect = dRectMake(
		currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	DTDMANAGER->getCurrentRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}