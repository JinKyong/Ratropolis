#pragma once

class ToolTip;

enum ATTRIBUTE_TYPE {
	ATTRIBUTE_TYPE_LABOR,
	END_ATTRIBUTE_TYPE
};

class Attribute
{
protected:
	ATTRIBUTE_TYPE _type;

	ToolTip* _toolTip;

	int _value;
	float _duration;

public:
	virtual HRESULT init(int value = 0, float duration = 0);
	virtual void release();
	virtual void update();
	virtual void render();








	ATTRIBUTE_TYPE getType() { return _type; }

	ToolTip* getToolTip() { return _toolTip; }

	int getValue() { return _value; }
	int getDuration() { return _duration; }
};

