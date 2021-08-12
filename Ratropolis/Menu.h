#pragma once

class Menu
{
protected:
	float _scrollY;

	bool _hide;

public:
	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void changeScroll(float num);








	float getScrollY() { return _scrollY; }
	void setScrollY(float scrollY) { _scrollY = scrollY; }

	bool getHide() { return _hide; }
	void setHide(bool hide) { _hide = hide; }
};