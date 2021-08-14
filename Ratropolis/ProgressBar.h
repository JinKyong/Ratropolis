#pragma once

class ProgressBar
{
protected:
	dImage* _backBar;
	dImage* _frontBar;

	float _x, _y;
	RECT _body;

	bool _fin;

public:
	HRESULT init(float x, float y);
	void release();
	void update();
	void render();










	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	RECT getBody() { return _body; }

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

