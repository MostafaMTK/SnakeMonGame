#pragma once
#include "Card.h"
class CardSeven : public Card
{
public:
	CardSeven(const CellPosition& pos);
	~CardSeven();
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual void Read(ifstream&);
};