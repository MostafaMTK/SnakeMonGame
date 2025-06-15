#include "CardSix.h"
CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (5 here)
}

void CardSix::Read(ifstream& load)
{
	int cellpos;
	load >> cellpos;
	position = CellPosition::GetCellPositionFromNum(cellpos);
}

CardSix::~CardSix(void)
{
}


void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Move forward by the same number of steps that you just rolled and moved
	//already. (if you reach a ladder or a snake at the end of moving forward, take it).
	CellPosition tocell = CellPosition::GetCellPositionFromNum(this->position.GetCellNum() - pPlayer->GetjustRolledDiceNum());
	pPlayer->MoveToCell(pGrid, tocell);
}