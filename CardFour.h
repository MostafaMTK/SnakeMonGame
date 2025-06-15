#pragma once
#include "Card.h"
#include "Snake.h"
class CardFour : public Card
{
public:
	CardFour(const CellPosition& pos); // A Constructor takes card position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player
	//Moves the player forward to the start of the next snake. (If no snakes ahead, do nothing)
	virtual void Read(ifstream&);
	virtual ~CardFour(); // A Virtual Destructor
};