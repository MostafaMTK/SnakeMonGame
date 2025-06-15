#pragma once
#include"Card.h"
class CardEight : public Card
{
public:
	CardEight(const CellPosition& pos);

	virtual void Apply(Grid* pGrid, Player* pPlayer);
	
	virtual void Read(ifstream&);
	
	virtual ~CardEight();
};