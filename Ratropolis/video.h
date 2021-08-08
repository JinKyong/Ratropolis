#pragma once

#include <Vfw.h>	// 비디오 재생 관련 라이브러리
#pragma comment(lib, "vfw32.lib")

class video
{
private:
	const char* _fileName; //파일 이름
	HWND _hWndAVI;
	HINSTANCE _hWndInstance;

public:

	video();
	~video();


	HRESULT init();
	void release();

	HRESULT setVideo(const char* fileName);
	void playVideo();
	void playVideo(D2D1_RECT_F rc);
	void closeVideo(void);
	void deletVideo();
	void langsVideo(const char* fileName);
	void startVideo(const char* fileName);

	long getPosition() { return MCIWndGetPosition(_hWndAVI); }
	long getLength() {return MCIWndGetLength(_hWndAVI); }


};

