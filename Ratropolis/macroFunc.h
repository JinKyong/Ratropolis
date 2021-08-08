#pragma once

//============================================
// ## macroFunc ## - 21.04.23
//============================================
inline void pixel(HDC hdc) {
	SetPixel(hdc, 200, 50, RGB(255, 0, 0));
	for (int i = 0; i < 100; i++)
		SetPixel(hdc, 200 + i, 50, RGB(255, 0, 0));
}

//Point
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

//선긋기함수(그려줄DC, 시작좌표X, 시작좌표Y, 끝좌표 X, 끝좌표Y)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2, int width) {
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//사각형
inline void Rectangle(HDC hdc, RECT& rc) {
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
//좌표(x, y)를 LeftTop으로 하는 사각형(width, height)이 생성
inline void RectangleMake(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x, y, x + width, y + height);
}
//좌표(x, y)를 중심으로 하는 사각형(width, height)이 생성
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}


//원
inline void Ellipse(HDC hdc, RECT& rc) {
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
//좌표(x, y)를 LeftTop으로 하는 원(width, height)이 생성
inline void EllipseMake(HDC hdc, int x, int y, int width, int height) {
	Ellipse(hdc, x, y, x + width, y + height);
}
//좌표(x, y)를 중심으로 하는 원(width, height)이 생성
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height) {
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//============================================
// ## macroFunc ## - 21.04.26
//============================================

//RECT
inline RECT RectMake(int x, int y, int width, int height) {
	RECT rc = { x, y, x + width, y + height };

	return rc;
}
inline RECT RectMakeCenter(int x, int y, int width, int height) {
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}


inline D2D1_RECT_F dRectMake(float x, float y, float width, float height) {
	D2D1_RECT_F rc = { x, y, x + width, y + height };

	return rc;
}

inline D2D1_RECT_F dRectMakeCenter(float x, float y, float width, float height) {
	D2D1_RECT_F rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}