#pragma once
#include "singletonBase.h"
#include <vector>

struct tagIniData
{
	LPCWCHAR subject;
	LPCWCHAR title;
	LPCWCHAR body;
};

class txtData : public singletonBase<txtData>
{
private:
	typedef vector<tagIniData>				arrIniData;
	typedef vector<tagIniData>::iterator	arrIniDataIter;

	typedef vector<arrIniData>				arrIniDatas;
	typedef vector<arrIniData>::iterator	arrIniDatasIter;

private:
	arrIniDatas	_vIniData;
	WCHAR _currentTxt[128];

	txtData() {};
	friend singletonBase<txtData>;

public:
	HRESULT init();
	void release();

	//initData
	void addData(LPCWCHAR subject, LPCWCHAR title, LPCWCHAR body);
	void iniSave(LPCWCHAR fileName);

	LPCWCHAR loadDataString(LPCWCHAR fileName, LPCWCHAR subject, LPCWCHAR title, int size);
	LPCWCHAR loadDataString2(LPCWCHAR fileName, wstring subject, LPCWCHAR title, int size);
	int loadDataInterger(LPCWCHAR fileName, LPCWCHAR subject, LPCWCHAR title);

	//Save
	void txtSave(const char* saveFileName, vector<string> vStr);
	void wtxtSave(const char* saveFileName, vector<LPCWCHAR> vwStr);
	char* vectorArrayCombine(vector<string> vArray);
	LPCWCHAR wvectorArrayCombine(vector<LPCWCHAR> vArray);



	//Load
	vector<string> txtLoad(const char* loadFileName);
	vector<LPCWCHAR> wtxtLoad(LPCWCHAR loadFileName);
	vector<string> charArraySeparation(char charArray[]);
	vector<LPCWCHAR> wcharArraySeparation(WCHAR charArray[]);
};