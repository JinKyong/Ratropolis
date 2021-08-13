#pragma once

class ToolTip
{
private:
	dImage* _frame;

	LPWSTR _name;
	LPWSTR _desc;

public:
	HRESULT init(LPCWCHAR name, LPCWCHAR desc);
	void release();
	void update();
	void render(float x, float y);



	LPWSTR getName() { return _name; }
	LPWSTR getDesc() { return _desc; }
};

