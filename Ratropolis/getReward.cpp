#include "stdafx.h"
#include "eventManager.h"
#include "Player.h"

void eventManager::getReward() {
	//�̺�Ʈ Ÿ��
	if (_type == EVENT_TYPE_FIXED) {
		//�̺�Ʈ ��ȣ
		switch (_num) {
		case 8:
			//��ư ��ȣ
			if (_selectedButton == 0) {
				//ī�� 1�� ����
			}
			else if (_selectedButton == 1) {
				_player->changeGold(200);
			}
			else if (_selectedButton == 2) {
				//������ ���� +1
				_player->changeGoldPercent(-0.5);
			}
			break;
		}
	}
	else {

	}
}