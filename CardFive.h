#pragma once
#include "Card.h"
class CardFive :public Card
{
public:
	CardFive(const CellPosition& pos); // A Constructor takes card position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFive on the passed Player
	//Move forward by the same number of steps that you just rolled and moved
   //already. (if you reach a ladder or a snake at the end of moving forward, take it).
	virtual void Read(ifstream&);
	virtual ~CardFive(); // A Virtual Destructor
};
