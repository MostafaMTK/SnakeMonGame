#include "CardFour.h"
CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}

void CardFour::Read(ifstream& load)
{
		int cellpos;
		load >> cellpos;
		position = CellPosition::GetCellPositionFromNum(cellpos);
}

CardFour::~CardFour(void)
{
}


void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Moves the player forward to the start of the next snake. (If no snakes ahead, do nothing)
	if (Snake* NS = pGrid->GetNextSnake(this->GetPosition()))
	{
		pPlayer->MoveToCell(pGrid, NS->GetPosition());
	}
}