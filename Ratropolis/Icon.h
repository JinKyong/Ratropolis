#pragma once

class Icon
{
protected:
	dImage* _image;

	int _value;

public:
	virtual HRESULT init(int value);
	virtual void release();
	virtual void update();
	virtual void render(float x, float y);





	int getValue() { return _value; }
	void setValue(int value) { _value = value; }
};