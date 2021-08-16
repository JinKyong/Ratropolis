#pragma once
#include "Card.h"

//=========== Economy ===========//
#include "Card1.h"
#include "Card31.h"
#include "Card32.h"



//=========== Millitary ===========//




//=========== Build ===========//
#include "Card3.h"
#include "Card18.h"


//=========== Technology ===========//









//======================== 카드 도감 ========================//

	namespace CARDLIST {
		Card* card1(int level) { return new Card1(level); }
		Card* card31(int level) { return new Card31(level); }
		Card* card32(int level) { return new Card32(level); }
	}