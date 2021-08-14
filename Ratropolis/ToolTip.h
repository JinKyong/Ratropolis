#pragma once

class ToolTip
{
protected:
	dImage* _frame;

	LPCWCHAR _name;
	LPCWCHAR _desc;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(float x, float y);



	LPCWCHAR getName() { return _name; }
	LPCWCHAR getDesc() { return _desc; }
};

