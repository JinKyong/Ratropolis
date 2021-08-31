#pragma once

class WaveBar
{
private:
	dImage* _backBar;
	dImage* _frontBar;
	dImage* _image;

	float _elapsedTime;	//����ð�
	float _duration;	//���ӽð�

	float _x, _y;
	RECT _body;
	float _zoom;

	bool _fin;
	
public:
	HRESULT init(int direct, bool boss = false);
	void release();
	void update();
	void render();






	RECT getBody() { return _body; }

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

