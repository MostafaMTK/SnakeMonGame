#include "CardSeven.h"
CardSeven::CardSeven(const CellPosition& pos) : Card(pos)
{
	cardNumber = 7;
}
CardSeven::~CardSeven()
{
}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->AdvanceCurrentPlayer();
	pGrid->AdvanceCurrentPlayer();
	pGrid->AdvanceCurrentPlayer();
	pPlayer->DecrementTurnCount();
	pGrid->PrintErrorMessage("Make another RollDice,Please ...");

}

void CardSeven::Read(ifstream& load)
{
	int cellpos;
	load >> cellpos;
	position = CellPosition::GetCellPositionFromNum(cellpos);
}
