#include "stdafx.h"
#include "dialogManager.h"

HRESULT dialogManager::init()
{
	/*_back = IMAGEMANAGER->addDImage("dialog_back", L"img/ui/dialog/back.png", 687, 562);
	_border = IMAGEMANAGER->addDImage("dialog_border", L"img/ui/dialog/border.png", 687, 562);
	_leftBorder = IMAGEMANAGER->addDImage("dialog_left_border", L"img/ui/dialog/left_border.png", 687, 562);
	_rightBorder = IMAGEMANAGER->addDImage("dialog_right_border", L"img/ui/dialog/right_border.png", 687, 562);*/

	_currentFileName = NULL;

	_size = 0;
	_count = 0;

	_print = false;

	return S_OK;
}

void dialogManager::release()
{
	//battleLog �ʱ�ȭ
	battleIter iter = _battleLog.begin();

	for (; iter != _battleLog.end();)
		iter = _battleLog.erase(iter);

	_battleLog.clear();
}

void dialogManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		if (_size >= 128) {
			//��������
			loadScript();

			_size = 0;
		}
		else
			_size = 128;
	}
}

void dialogManager::render()
{
	//����ũ�� ����
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= 0.1) {
		if (_size < 128)
			_size++;
		_count = 0;
	}


	//ȭ��������� render
	D2D1_RECT_F screen = CAMERAMANAGER->getScreen();
	_back->render(screen.left, screen.top);
	_border->render(screen.left, screen.top);


	//�ؽ�Ʈ �ҷ�����
	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", _scriptNum);
	WCHAR text[128];
	swprintf_s(text, L"");
	lstrcatW(text, TXTDATA->loadDataString(_currentFileName,
		&_storyMetaData[_metaDataNum][0], tmp, _size));


	//�����ġ ����
	DTDMANAGER->printText(text, screen.left + 344, screen.top + 374, 490, 120, 30);
}

void dialogManager::loadMetaData(LPCWCHAR fileName)
{
	//��Ÿ������ �о�ͼ� ���Ϳ� �־��ֱ�
	_currentFileName = fileName;

	WCHAR dir[256];
	ZeroMemory(dir, sizeof(dir));
	swprintf_s(dir, L"%s.txt", _currentFileName);

	_storyMetaData = TXTDATA->wtxtLoad(dir);
	_metaDataNum = -1;
	_scriptNum = 0;

	//�� �� �о����
	loadScript();

	_print = true;
}

void dialogManager::loadScript()
{
	//��� ������ ��
	if (_metaDataNum + 2 >= _storyMetaData.size()) {
		_print = false;
		return;
	}

	for (_metaDataNum = _metaDataNum + 2; _metaDataNum < _storyMetaData.size(); _metaDataNum++) {
		if ((_storyMetaData[_metaDataNum][0] == L'\r') ||
			(_storyMetaData[_metaDataNum][0] == L'\n')) continue;

		else break;
	}

	_scriptNum++;
}

void dialogManager::resetTimer()
{
	TIMEMANAGER->endTimer();
	TIMEMANAGER->setTimer();
	//UIMANAGER->getCurrentDownMenu()->setHidden(false);
}