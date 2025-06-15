#include "CardThree.h"

CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

void CardThree::Read(ifstream& load)
{
		int cellpos;
		load >> cellpos;
		position = CellPosition::GetCellPositionFromNum(cellpos);

}

CardThree::~CardThree(void)
{
}


void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Moves the player forward to the start of the next ladder. (If no ladders ahead, do nothing)
	if (Ladder* NL = pGrid->GetNextLadder(this->GetPosition()))
	{
		pPlayer->MoveToCell(pGrid, NL->GetPosition());
	}
}