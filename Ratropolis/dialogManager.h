#pragma once
#include "singletonBase.h"
#include <vector>

class dialogManager : public singletonBase<dialogManager>
{
private:
	typedef vector<LPCWCHAR>			dialog;
	typedef vector<LPCWCHAR>::iterator	dialogIter;

	typedef vector<wstring>				battleLog;
	typedef vector<wstring>::iterator	battleIter;

private:
	//대화창
	dImage* _back;
	dImage* _border;
	dImage* _leftBorder;
	dImage* _rightBorder;


	//대화 log가 담기는 vector
	LPCWCHAR _currentFileName;
	dialog _storyMetaData;
	int _metaDataNum;

	//대사 번호, 문자 출력 수, 속도 카운트
	int _scriptNum;
	int _size;
	float _count;

	//다이어로그 출력 여부
	bool _print;



	//전투 log가 담기는 vector
	battleLog _battleLog;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadMetaData(LPCWCHAR fileName);
	void loadScript();



	void resetTimer();
	//==================  로그 추가  ==================//









	bool getPrint() { return _print; }
	void setPrint(bool print) { _print = print; }

	battleLog* getBattleLog() { return &_battleLog; }
};