#include "CardOne.h"

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

CardOne::CardOne(const CellPosition& pos, Card* c) : Card(pos)
{
	CardOne* sc = dynamic_cast<CardOne*>(c);
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	this->walletAmount = sc->walletAmount;
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("CardOne: Enter its wallet amount ...");
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	
	walletAmount =pIn->GetInteger(pOut);//the user might enter invalid amount
	if (!IsValidCard())//checks if the entered amount is valid
		pGrid->PrintErrorMessage("Error: Invalid wallet amount ...");
	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();

}

 bool CardOne::IsValidCard() const
{
	 if (walletAmount > 0)//checks if the entered amount is positive integer
		 return true;
	 else
		 return false;
}
 void CardOne::Save(ofstream& save, ObjectType T)
 {
	 if (T != Cards) return;
	 save << cardNumber << " " << position.GetCellNum() << " " << walletAmount << "\n";
 }
 void CardOne::Read(ifstream& load)
 {
	 int cellpos,value;
	 load >> cellpos>>value;
	 position = CellPosition::GetCellPositionFromNum(cellpos);
	 walletAmount = value;
 }

 void CardOne::EditParameters(Grid* pGrid)
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

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	pPlayer->SetWallet(pPlayer->GetWallet() - walletAmount);
}
