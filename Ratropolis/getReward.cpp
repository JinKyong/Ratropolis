#include "stdafx.h"
#include "eventManager.h"
#include "Player.h"

void eventManager::getReward() {
	//이벤트 타입
	if (_type == EVENT_TYPE_FIXED) {
		//이벤트 번호
		switch (_num) {
		case 8:
			//버튼 번호
			if (_selectedButton == 0) {
				//카드 1장 제거
			}
			else if (_selectedButton == 1) {
				_player->changeGold(200);
			}
			else if (_selectedButton == 2) {
				//지도자 레벨 +1
				_player->changeGoldPercent(-0.5);
			}
			break;
		}
	}
	else {

	}
}