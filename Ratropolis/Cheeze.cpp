#include "stdafx.h"
#include "Cheeze.h"
#include "Player.h"

Cheeze::Cheeze()
{
	//ī�� ����
	_cardStat.number = 32;					//��ȣ
	_cardStat.rarity = CARD_GRADE_COMMON;	//���
	_cardStat.mainCost = 40;				//���� ���(���)
	_cardStat.subCost =  0;					//���� ���(�ù� or �ǹ�ũ�� ���)
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
	_body = RectMakeCenter(_x, _y, CARDWIDTH, CARDHEIGHT);

	return S_OK;
}

void Cheeze::useCard()
{
	vector<Card*> hands = DECKMANAGER->getCurrentHands();

	int sum = 0;
	for (int i = 0; i < hands.size(); i++) {
		if (hands[i]->getCardStat()->number == _cardStat.number)
			sum += 30;
	}
	_player->changeGold(sum);

	//cost
	Card_Economy::useCard();
}
