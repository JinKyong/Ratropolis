#pragma once

class dImage
{
public:
	//이미지를 불러올수 있는 종류
	enum DIMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스 파일로부터
		LOAD_FILE,			//이미지 파일로부터
		LOAD_EMPTY,			//빈 비트맵 이미지를 만들어야겠다
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//리소스를 통해서 이미지 처리할땐 얘를 쓴다
		ID2D1Bitmap	*bitMap;//이미지 비트맵
		float x;			//이미지 x좌표
		float y;			//이미지 y좌표
		int width;			//이미지 전체 가로크기
		int height;			//이미지 전체 세로크기
		int currentFrameX;	//현재 프레임 번호(가로)
		int currentFrameY;	//현재 프레임 번호(세로)
		int maxFrameX;		//최대 프레임 번호(가로)
		int maxFrameY;		//최대 프레임 번호(세로)
		int frameWidth;		//1프레임 당 가로크기
		int frameHeight;	//1프레임 당 세로크기
		BYTE loadType;

		tagImageInfo()
		{
			resID = 0;
			bitMap = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	LPWSTR			_fileName;		//파일 이름

	//이미지 로드를 위한 객체
	IWICImagingFactory		*_wicFactory;
	IWICBitmapDecoder		*_bitDecoder;
	IWICBitmapFrameDecode	*_bitFrame;
	IWICFormatConverter		*_wicConverter;

public:
	dImage();
	~dImage();

	HRESULT init(LPCWCHAR fileName, int width, int height);
	HRESULT init(LPCWCHAR fileName, int width, int height, int frameX, int frameY);
	/*				│				│			│			│			│								*/
	/*				│				│			│			│			└──〉	 이미지 프레임 수(y축)		*/
	/*				│				│			│			│											*/
	/*				│				│			│			└──〉	 이미지 프레임 수(x축)					*/
	/*				│				│			│														*/
	/*				│				│			└──〉	 이미지 사이즈(y축)									*/
	/*				│				│																	*/
	/*				│				└──〉	 이미지 사이즈(x축)												*/
	/*				│																					*/
	/*				└──〉 파일명 (ex. L"sample.png" // 반드시 파일명 앞에 L을 붙여 줄 것)					*/
	void release();

	void render(float opacity = 1.0);
	void render(int destX, int destY, float opacity = 1.0);
	void render(int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float opacity = 1.0);
	/*				│			│			│			│			│			│				│					*/
	/*				│			│			│			│			│			│				└──〉	 투명도			*/
	/*				│			│			│			│			│			│									*/
	/*				│			│			│			│			│			└──〉	 이미지에서 복사해올 사이즈(y축)	*/
	/*				│			│			│			│			│												*/
	/*				│			│			│			│			└──〉	 이미지에서 복사해올 사이즈(x축)				*/
	/*				│			│			│			│															*/
	/*				│			│			│			└──〉	 이미지에서 복사해올 시작좌표(y축)							*/
	/*				│			│			│																		*/
	/*				│			│			└──〉	 이미지에서 복사해올 시작좌표(x축)										*/
	/*				│			│																					*/
	/*				│			└──〉	 출력할 좌표(y축)																	*/
	/*				│																								*/
	/*				└──〉 출력할 좌표(x축)																				*/

	void frameRender(int destX, int destY, float opacity = 1.0);
	void frameRender(int destX, int destY, int currentFrameX, int currentFrameY, float opacity = 1.0);
	/*					│			│				│				│					│				*/
	/*					│			│				│				│					└──〉	 투명도		*/
	/*					│			│				│				│									*/
	/*					│			│				│				└──〉	 현재 프레임(y축)					*/
	/*					│			│				│													*/
	/*					│			│				└──〉	 현재 프레임(x축)									*/
	/*					│			│																	*/
	/*					│			└──〉	 출력할 좌표(y축)													*/
	/*					│																				*/
	/*					└──〉 출력할 좌표(x축)																*/
	void frameRender(int destX, int destY, int currentFrameX, int currentFrameY, int sizeX, int sizeY, float opacity = 1.0);


	//===============================================
	// ## 이미지 관련 접근자 설정자 ##
	//=============================================

	inline ID2D1Bitmap* getBitmap() { return _imageInfo->bitMap; }

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline float getWidth() { return _imageInfo->width; }
	inline float getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}


	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline float getFrameWidth() { return _imageInfo->frameWidth; }
	inline float getFrameHeight() { return _imageInfo->frameHeight; }
};

