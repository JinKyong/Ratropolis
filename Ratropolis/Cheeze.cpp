#include "stdafx.h"
#include "Cheeze.h"

Cheeze::Cheeze()
{
	//ī�� ����
	_cardStat.number = 32;					//��ȣ
	_cardStat.rarity = CARD_GRADE_COMMON;	//���
	_cardStat.mainCost = 40;				//���� ���(���)
	_cardStat.subCost =  2;					//���� ���(�ù� or �ǹ�ũ�� ���)
	_cardStat.level = 1;					//����(�ִ� 2)

	_cardStat.name = L"ġ��";				//�̸�
	_cardStat.desc = L"ġ��� ġ������ ġ��� ġ� �ƴϴ� �˰�? �𸣰�? ������?";				//����


	//�Ӽ�(ī�� Ű����)
	//_atbList;
}

Cheeze::~Cheeze()
{
}

HRESULT Cheeze::init()
{
	Card_Economy::init();

	_x = 5000;
	_y = 500;
	_body = RectMakeCenter(_x, _y, 400, 600);

	return S_OK;
}
