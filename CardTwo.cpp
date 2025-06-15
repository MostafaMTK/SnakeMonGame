#include "CardTwo.h"

CardTwo::CardTwo(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
}

CardTwo::CardTwo(const CellPosition& pos, Card* c) : Card(pos)
{
	CardTwo* sc = dynamic_cast<CardTwo*>(c);
	cardNumber = 2; // set the inherited cardNumber data member with the card number (1 here)
	this->walletAmount = sc->walletAmount;
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{

	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("CardTwo: Enter its wallet amount ...");
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardTwo: Enter its wallet amount ..."

	walletAmount = pIn->GetInteger(pOut);//the user might enter invalid amount
	if (!IsValidCard())//checks if the entered amount is valid
		pGrid->PrintErrorMessage("Error: Invalid wallet amount ...");
	// [ Note ]:
	// In CardTwo, the only parameter of CardTwo is the "walletAmount" value to increase player's wallet
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();

}

bool CardTwo::IsValidCard() const
{
	if (walletAmount > 0)//checks if the entered amount is positive integer
		return true;
	else
		return false;
}

void CardTwo::Save(ofstream& save, ObjectType T)
{
	if (T != Cards) return;
	save << cardNumber << " " << position.GetCellNum() << " " << walletAmount << "\n";
}

void CardTwo::Read(ifstream& load)
{
	int cellpos, value;
	load >> cellpos >> value;
	position = CellPosition::GetCellPositionFromNum(cellpos);
	walletAmount = value;
}

void CardTwo::EditParameters(Grid* pGrid)
{
	int prevwalletAmount = walletAmount;
	ReadCardParameters(pGrid);
	if (!IsValidCard())
	{
		walletAmount = prevwalletAmount;
		return;
	}
	pGrid->PrintErrorMessage("Card Edited Successfully ...");
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{


	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Increment the wallet of pPlayer by the walletAmount data member of CardTwo
	pPlayer->SetWallet(pPlayer->GetWallet() + walletAmount);
}