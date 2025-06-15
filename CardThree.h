#pragma once
#include "Card.h"
#include "Ladder.h"
class CardThree : public Card
{
public:
	CardThree(const CellPosition& pos); // A Constructor takes card position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThree on the passed Player
	//Moves the player forward to the start of the next ladder. (If no ladders ahead, do nothing)       
	virtual void Read(ifstream&);
	virtual ~CardThree(); // A Virtual Destructor
};