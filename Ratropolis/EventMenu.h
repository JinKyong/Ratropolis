#pragma once
#include "Menu.h"

class EventMenu : public Menu
{
private:

public:
	EventMenu();
	~EventMenu();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeScroll(float num);
};

