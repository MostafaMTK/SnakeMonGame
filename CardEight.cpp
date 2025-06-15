#include "CardEight.h"
CardEight::CardEight(const CellPosition& pos) : Card(pos)
{
	cardNumber = 8;
}

CardEight::~CardEight(void)
{
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pPlayer->FreezePlayer();
}

void CardEight::Read(ifstream& load)
{
	int cellpos;
	load >> cellpos;
	position = CellPosition::GetCellPositionFromNum(cellpos);
}
