#include "stdafx.h"
#include "Card_Economy.h"

HRESULT Card_Economy::init()
{
	//이미지 할당
	_frame = IMAGEMANAGER->findDImage("economyFrame");

	char tmp[128];
	sprintf_s(tmp, "card_rarity%d", _cardStat.rarity);
	_gem = IMAGEMANAGER->findDImage(tmp);

	sprintf_s(tmp, "illuste%d", _cardStat.number);
	WCHAR tmp2[128];
	swprintf_s(tmp2, L"img/card/illuste/illuste%d.png", _cardStat.number);
	_illuste = IMAGEMANAGER->addDImage(tmp, tmp2, 340, 250);

	_nameTag = IMAGEMANAGER->findDImage("nameTag");
	_mainCost = IMAGEMANAGER->findDImage("cost_gold");
	_subCost = IMAGEMANAGER->findDImage("cost_civil");

	return S_OK;
}

void Card_Economy::release()
{
}

void Card_Economy::update()
{
	_body = RectMakeCenter(_x, _y, CARDWIDTH, CARDHEIGHT);
}

void Card_Economy::render()
{
	DTDMANAGER->setScale(0.5, 0.5, _x, _y);


	//이미지
	_illuste->render(_x - _illuste->getWidth() / 2, _y - _illuste->getHeight() / 2 - 100);
	_frame->render(_x - _frame->getWidth() / 2, _y - _frame->getHeight() / 2);
	_gem->render(_x - _gem->getWidth() / 2, _y - _gem->getHeight() / 2 + 55);

	//이름태그 및 코스트(+ 스탯)
	_nameTag->render(_x - _nameTag->getWidth() / 2, _body.top + 10);
	_mainCost->render(_body.left - _mainCost->getWidth() / 2 + 40, _body.top - _mainCost->getHeight() / 2 + 55);
	if (_cardStat.subCost > 0)
		_subCost->render(_body.right - _subCost->getWidth() / 2 - 40, _body.top - _subCost->getHeight() / 2 + 55);


	//텍스트
	D2D1_RECT_F tmpRect = dRectMakeCenter(_x, _y + 155, 300, 150);
	DTDMANAGER->printText(_cardStat.desc.c_str(), tmpRect, 25, true);

	//디버깅
	if (PRINTMANAGER->isDebug()) {
		DTDMANAGER->Rectangle(_body);
		WCHAR tmp[128];
		swprintf_s(tmp, L"x : %f", _x);
		DTDMANAGER->printText(tmp, _body.left, _body.top - 30, 300, 200, 25);
		DTDMANAGER->Rectangle(tmpRect);
	}

	DTDMANAGER->setBrushColor(ColorF(ColorF::White));
	DTDMANAGER->printText(_cardStat.name.c_str(), _x, _body.top + 50,
		_nameTag->getWidth(), _nameTag->getHeight(), 45, true);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", _cardStat.mainCost);
	DTDMANAGER->printText(tmp, _body.left + 40, _body.top + 55,
		_mainCost->getWidth(), _mainCost->getHeight(), 45, true);
	if (_cardStat.subCost > 0) {
		swprintf_s(tmp, L"%d", _cardStat.subCost);
		DTDMANAGER->printText(tmp, _body.right - 40, _body.top + 55,
			_subCost->getWidth(), _subCost->getHeight(), 45, true);
	}


	DTDMANAGER->resetBrushColor();
	DTDMANAGER->resetTransform();
}

void Card_Economy::render(float x, float y)
{
	_x = x;
	_y = y;
	_body = RectMakeCenter(_x, _y, CARDWIDTH, CARDHEIGHT);

	DTDMANAGER->setScale(0.4, 0.4, x, y);


	//이미지
	_illuste->render(_x - _illuste->getWidth() / 2, _y - _illuste->getHeight() / 2 - 100);
	_frame->render(_x - _frame->getWidth() / 2, _y - _frame->getHeight() / 2);
	_gem->render(_x - _gem->getWidth() / 2, _y - _gem->getHeight() / 2 + 55);

	//이름태그 및 코스트(+ 스탯)
	_nameTag->render(_x - _nameTag->getWidth() / 2, _body.top + 10);
	_mainCost->render(_body.left - _mainCost->getWidth() / 2 + 40, _body.top - _mainCost->getHeight() / 2 + 55);
	if (_cardStat.subCost > 0)
		_subCost->render(_body.right - _subCost->getWidth() / 2 - 40, _body.top - _subCost->getHeight() / 2 + 55);


	//텍스트
	D2D1_RECT_F tmpRect = dRectMakeCenter(_x, _y + 155, 300, 150);
	DTDMANAGER->printText(_cardStat.desc.c_str(), tmpRect, 25, true);

	//디버깅
	if (PRINTMANAGER->isDebug()) {
		DTDMANAGER->Rectangle(_body);
		WCHAR tmp[128];
		swprintf_s(tmp, L"x : %f", _x);
		DTDMANAGER->printText(tmp, _body.left, _body.top - 30, 300, 200, 25);
		DTDMANAGER->Rectangle(tmpRect);
	}

	DTDMANAGER->setBrushColor(ColorF(ColorF::White));
	DTDMANAGER->printText(_cardStat.name.c_str(), _x, _body.top + 50,
		_nameTag->getWidth(), _nameTag->getHeight(), 45, true);

	WCHAR tmp[128];
	swprintf_s(tmp, L"%d", _cardStat.mainCost);
	DTDMANAGER->printText(tmp, _body.left + 40, _body.top + 55,
		_mainCost->getWidth(), _mainCost->getHeight(), 45, true);
	if (_cardStat.subCost > 0) {
		swprintf_s(tmp, L"%d", _cardStat.subCost);
		DTDMANAGER->printText(tmp, _body.right - 40, _body.top + 55,
			_subCost->getWidth(), _subCost->getHeight(), 45, true);
	}


	DTDMANAGER->resetBrushColor();
	DTDMANAGER->resetTransform();
}

void Card_Economy::useCard()
{
}