#include "stdafx.h"
#include "Card18.h"
#include "Player.h"
#include "NameTag.h"
#include "Icon_Gold.h"
#include "Icon_Space.h"

Card18::Card18(int level)
{
	//ī�� ����
	_cardStat.number = 18;					//��ȣ
	_cardStat.level = level;				//����(�ִ� 2)
	_cardStat.rarity = CARD_GRADE_RARE;	//���

	//����
	swprintf_s(_cardStat.desc, L"400 ������� ���� �溮 �Ǽ�");

	//�̸�
	_name = new NameTag;
	_name->init(L"��", _cardStat.level);

	//���
	_cost = new Icon_Gold;
	_cost->init(88 + (_cardStat.level - 1) * 44);
	_spaceCost = new Icon_Space;
	_spaceCost->init(_cardStat.level + 1);

	//�Ӽ�(ī�� Ű����)
	//_atbList.push_back(new Labor);
	//for (int i = 0; i < _atbList.size(); ++i)
	//	_atbList[i]->init();
}

Card18::~Card18()
{
}

void Card18::update()
{
	Card_Build::update();
}

void Card18::useCard()
{
	if (!_usable) {
		GAMEMANAGER->getBuildManager()->putBcard();
		return;
	}

	//�ǹ�����
	GAMEMANAGER->getBuildManager()->addWall();

	//cost
	Card_Build::useCard();
	SOUNDMANAGER->play("useCard");
}
