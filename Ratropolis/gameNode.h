#pragma once

class gameNode
{
private:
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();



	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();			//�׸��� �Լ�

	void cursorOnWindow();

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};