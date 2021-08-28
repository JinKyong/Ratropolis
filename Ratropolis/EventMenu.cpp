#include "stdafx.h"
#include "EventMenu.h"

EventMenu::EventMenu()
{
	_back = IMAGEMANAGER->addDImage("darkBackground", L"img/UI/DarkBack.png", WINSIZEX, WINSIZEY);
}

EventMenu::~EventMenu()
{
}

HRESULT EventMenu::init()
{
	_scrollY = 0;
	_hide = true;

	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	UIMANAGER->setOpen(true);

	return S_OK;
}

void EventMenu::release()
{
	EVENTMANAGER->setOpen(false);
}

void EventMenu::update()
{

	EVENTMANAGER->update();
}

void EventMenu::render()
{
	_back->render(0, _scrollY, 0.8);

	//_illuste->render(WINSIZEX / 2 - _illuste->getWidth() / 2, WINSIZEY / 2 - _illuste->getHeight() / 2);
	EVENTMANAGER->render();
}

void EventMenu::changeScroll(float num)
{

}
