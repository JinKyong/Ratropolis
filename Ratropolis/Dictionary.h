#pragma once
#include "singletonBase.h"
#include "CardHeader.h"
#include "BuildingHeader.h"
#include <map>

class Dictionary : public singletonBase<Dictionary>
{
private:
	typedef Card*(Dictionary::*funcCard)(int level);
	typedef map<int, funcCard>					cardList;
	typedef map<int, funcCard>::iterator		cardIter;

	typedef Building*(Dictionary::*funcBuilding)(int level);
	typedef map<int, funcBuilding>				buildingList;
	typedef map<int, funcBuilding>::iterator	buildingIter;

	//typedef NPC*(Dictionary::*func)(int level);
	//typedef map<int, func>		NPCList;

private:
	cardList		_cardList;
	buildingList	_buildingList;

public:
	HRESULT init();
	void release();
	
	void addCard(int num, funcCard f);
	Card* makeCard(int num, int level);

	void addBuilding(int num, funcBuilding f);
	Building* makeBuilding(int num, int level);





#pragma region RegisterCard
	void registerCard();					//카드 등록

	void registerCardFrameImage();			//카드 frameImg	(틀)
	void registerCardGemImage();			//카드 gemImg	(보석)
	void registerCardIlluste();				//카드 illust	(그림)
	void registerCardCostImage();			//카드 cost		(비용)
#pragma endregion

#pragma region RegisterBuilding
	void registerBuilding();				//빌딩 등록

	void registerBuildEffect();				//빌드 effect	(생성 이미지)
#pragma endregion



	//======================== 도감 ========================//
#pragma region Card
	Card* card1(int level) { return new Card1(level); }
	Card* card3(int level) { return new Card3(level); }
	Card* card18(int level) { return new Card18(level); }
	Card* card31(int level) { return new Card31(level); }
	Card* card32(int level) { return new Card32(level); }
#pragma endregion

#pragma region Building
	Building* cityHall(int level) { return new CityHall(level); }
	Building* building3(int level) { return new Building3(level); }
	Building* building18(int level) { return new Building18(level); }
#pragma endregion

#pragma region NPC

#pragma endregion

};

