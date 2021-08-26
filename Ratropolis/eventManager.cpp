#include "stdafx.h"
#include "eventManager.h"
#include "Player.h"

HRESULT eventManager::init()
{
	//_eventFrame = IMAGEMANAGER->addDImage("eventFrame", L"img/UI/event/EventFrame2.png", 1260, 582);
	_eventFrame = IMAGEMANAGER->addDImage("eventFrame", L"img/UI/event/EventFrame2.png", 945, 437);
	//_illusteFrame = IMAGEMANAGER->addDImage("eventIllusteFrame", L"img/UI/event/Event_illusteFrame.png", 541, 390);
	_illusteFrame = IMAGEMANAGER->addDImage("eventIllusteFrame", L"img/UI/event/Event_illusteFrame.png", 406, 293);
	_buttonFrame = IMAGEMANAGER->addDImage("eventButtonFrame", L"img/UI/event/EventBtnFrame.png", 725, 68);
	_rope = IMAGEMANAGER->addDImage("eventRope", L"img/UI/event/EventFrameRope.png", 33, 54);

	registerIlluste();

	_x = WINSIZEX / 2 - _eventFrame->getWidth() / 4 + 15;
	_y = WINSIZEY / 3 + 25;

	_type = END_EVENT_TYPE;
	_num = -1;
	_selectedButton = -1;

	_open = false;

	return S_OK;
}

void eventManager::release()
{
	//battleLog 초기화
	battleIter iter = _battleLog.begin();

	for (; iter != _battleLog.end();)
		iter = _battleLog.erase(iter);

	_battleLog.clear();
}

void eventManager::update()
{
	_cursor->updatePosition(_ptMouse.x, _ptMouse.y);
	_cursor->update();
	
	COLLISIONMANAGER->selectButtonWithCursor(_buttonRECT, _cursor->getX(), _cursor->getY());
}

void eventManager::render()
{
	_rope->render(WINSIZEX / 2 - _eventFrame->getWidth() / 2 - _rope->getWidth() / 2 + 150,
		WINSIZEY / 3 + _eventFrame->getHeight() / 2 - 10);
	_rope->render(WINSIZEX / 2 + _eventFrame->getWidth() / 2 - _rope->getWidth() / 2 - 150,
		WINSIZEY / 3 + _eventFrame->getHeight() / 2 - 10);

	_eventFrame->render(WINSIZEX / 2 - _eventFrame->getWidth() / 2, WINSIZEY / 3 - _eventFrame->getHeight() / 2);
	_illuste->render(_x - _illuste->getWidth() / 2, _y - _illuste->getHeight() / 2);
	_illusteFrame->render(_x - _illusteFrame->getWidth() / 2, _y - _illusteFrame->getHeight() / 2);


	//버튼 같은 경우에 선택지 개수에 따라서 출력
	for (int i = 1; i <= _buttonNum; i++) {
		_rope->render(WINSIZEX / 2 - _eventFrame->getWidth() / 2 - _rope->getWidth() / 2 + 150,
			WINSIZEY / 3 + _eventFrame->getHeight() / 2 - 10 + i * (15 + _buttonFrame->getHeight()));
		_rope->render(WINSIZEX / 2 + _eventFrame->getWidth() / 2 - _rope->getWidth() / 2 - 150,
			WINSIZEY / 3 + _eventFrame->getHeight() / 2 - 10 + i * (15 + _buttonFrame->getHeight()));
	}
	for (int i = 0; i < _buttonNum; i++) {
		if (i == _selectedButton) {

		}
		else {
			_buttonFrame->render(WINSIZEX / 2 - _buttonFrame->getWidth() / 2,
				WINSIZEY / 3 + _eventFrame->getHeight() / 2 + 15 + i * (15 + _buttonFrame->getHeight()));
		}
	}

	if (PRINTMANAGER->isDebug()) {
		for (int i = 0; i < _buttonNum; i++)
			DTDMANAGER->Rectangle(_buttonRECT[i]);
	}

	//텍스트 출력
	printText();

	//커서 render
	_cursor->render();
}

void eventManager::printText()
{
	WCHAR dir[256];
	ZeroMemory(dir, sizeof(dir));
	swprintf_s(dir, L"data/%s", _currentFileName);

	D2D1_RECT_F tmpRECT;

	//제목
	//DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
	tmpRECT = dRectMakeCenter(WINSIZEX / 2 - 5 + 1, WINSIZEY / 3 - _eventFrame->getHeight() / 2 + 38 + 1, 280, 60);
	DTDMANAGER->printText(TXTDATA->loadDataString(dir, L"제목", L"1", 128), tmpRECT, 35, true, true);
	DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
	tmpRECT = dRectMakeCenter(WINSIZEX / 2 - 5, WINSIZEY / 3 - _eventFrame->getHeight() / 2 + 38, 280, 60);
	DTDMANAGER->printText(TXTDATA->loadDataString(dir, L"제목", L"1", 128), tmpRECT, 35, true, true);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(tmpRECT);


	//내용
	WCHAR tmp[256];
	ZeroMemory(tmp, sizeof(tmp));

	for (int i = 1; i <= _scriptNum; i++) {
		if (i > 1)
			lstrcatW(tmp, L"\n");
		WCHAR script[128];
		swprintf_s(script, L"%d", i);
		lstrcatW(tmp, TXTDATA->loadDataString(dir, L"내용", script, 128));

		if (i < _scriptNum)
			lstrcatW(tmp, L"\n");
	}
	DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
	tmpRECT = dRectMakeCenter(WINSIZEX / 2 + _eventFrame->getWidth() / 4 - 23, WINSIZEY / 3 + 25, 370, 250);
	DTDMANAGER->printText(tmp, tmpRECT, 18, true, true);

	if (PRINTMANAGER->isDebug())
		DTDMANAGER->Rectangle(tmpRECT);

	//버튼
	for (int i = 1; i <= _buttonNum; i++) {
		WCHAR select[128];
		int size1, size2;
		swprintf_s(select, L"버튼%d", i);

		ZeroMemory(tmp, sizeof(tmp));
		lstrcatW(tmp, TXTDATA->loadDataString(dir, select, L"1", 128));
		lstrcatW(tmp, L" ");
		size1 = lstrlenW(tmp);

		lstrcatW(tmp, TXTDATA->loadDataString(dir, select, L"2", 128));
		lstrcatW(tmp, L" ");
		size2 = lstrlenW(tmp);

		lstrcatW(tmp, TXTDATA->loadDataString(dir, select, L"3", 128));

		DTDMANAGER->setBrushColor(ColorF(ColorF::Black));
		tmpRECT = dRectMake(WINSIZEX / 2 - _buttonFrame->getWidth() / 2 + 70 + 1,
			WINSIZEY / 3 + _eventFrame->getHeight() / 2 + 35 + (i - 1) * (15 + _buttonFrame->getHeight()) + 1, 580, 40);
		DTDMANAGER->printText(tmp, tmpRECT, 20, false, true);

		//총 3번 쓴다
		tmpRECT = dRectMake(tmpRECT.left - 1, tmpRECT.top - 1, 580, 40);
		DTDMANAGER->setBrushColor(ColorF(ColorF::Red));
		DTDMANAGER->printText(tmp, tmpRECT, 20, false, true);

		WCHAR tmp2[128];
		ZeroMemory(tmp2, sizeof(tmp2));
		wcsncpy_s(tmp2, tmp, size2);

		DTDMANAGER->setBrushColor(ColorF(ColorF::SpringGreen));
		DTDMANAGER->printText(tmp2, tmpRECT, 20, false, true);

		ZeroMemory(tmp2, sizeof(tmp2));
		wcsncpy_s(tmp2, tmp, size1);

		DTDMANAGER->setBrushColor(ColorF(ColorF::GhostWhite));
		DTDMANAGER->printText(tmp2, tmpRECT, 20, false, true);

		DTDMANAGER->resetBrushColor();
		if (PRINTMANAGER->isDebug())
			DTDMANAGER->Rectangle(tmpRECT);
	}
}

void eventManager::loadEvent(int num, int type)
{
	//커서 등록
	_cursor = GAMEMANAGER->getPlayer()->getCursor();

	char tmp[128];

	_type = type;
	_num = num;

	if (_type == EVENT_TYPE_RANDOM) {
		sprintf_s(tmp, "eventIlluste_random%d", _num);
		swprintf_s(_currentFileName, L"eventScript_random%d", _num);
	}
	else {
		sprintf_s(tmp, "eventIlluste_fixed%d", _num);
		swprintf_s(_currentFileName, L"eventScript_fixed%d", _num);
	}

	//일러스트
	_illuste = IMAGEMANAGER->findDImage(tmp);

	//텍스트
	loadMetaData();

	_open = true;
}

void eventManager::loadMetaData()
{
	WCHAR dir[256];
	ZeroMemory(dir, sizeof(dir));
	swprintf_s(dir, L"data/%s.txt", _currentFileName);

	_eventMetaData = TXTDATA->wtxtLoad(dir);
	_scriptNum = _wtoi(_eventMetaData[EVENT_META_SCRIPTNUM]);
	_buttonNum = _wtoi(_eventMetaData[EVENT_META_BUTTONNUM]);
	
	for (int i = 0; i < _buttonNum; i++) {
		_buttonRECT[i] = RectMake(WINSIZEX / 2 - _buttonFrame->getWidth() / 2 + 15,
			WINSIZEY / 3 + _eventFrame->getHeight() / 2 + 15 + i * (15 + _buttonFrame->getHeight()) + 10,
			_buttonFrame->getWidth() - 30, _buttonFrame->getHeight() - 10);
	}
}

void eventManager::registerIlluste()
{
	char tmp[128];
	WCHAR tmp2[128];

	//fixed event
	for (int i = 0; i < 38; i++) {
		sprintf_s(tmp, "eventIlluste_fixed%d", i);
		swprintf_s(tmp2, L"img/UI/event/Event_Illust_Fixed_%d.png", i);
		IMAGEMANAGER->addDImage(tmp, tmp2, 375, 275);
	}

	//random event
	for (int i = 0; i < 60; i++) {
		sprintf_s(tmp, "eventIlluste_random%d", i);
		swprintf_s(tmp2, L"img/UI/event/Event_Illust_Random_%d.png", i);
		IMAGEMANAGER->addDImage(tmp, tmp2, 375, 275);
	}
}
