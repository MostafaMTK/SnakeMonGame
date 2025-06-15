#include "CardTwelve.h"

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12;  // set the inherited cardNumber data member with the card number (10 here)
	NumberOf12Cards++;
}

Player* CardTwelve::Owner = nullptr;

int CardTwelve::NumberOf12Cards = 0;
int CardTwelve::SavedCards = 0;

int CardTwelve::Price = 0;

int CardTwelve::Fees = 0;

void CardTwelve::ReadCardParameters(Grid* pGrid)
{
	if (NumberOf12Cards == 1)
	{
		// Get a Pointer to the Input / Output Interfaces
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();

		// Read the Price parameter
		pOut->PrintMessage("Enter Price of The Card ..");
		Price = pIn->GetInteger(pOut);
		if (Price < 0)
		{
			pGrid->PrintErrorMessage("You entered an invalid price, click to continue...");
			return;
		}
		// Read the Fees parameter
		pOut->PrintMessage("Enter Fees to Pay by Passing Players ..");
		Fees = pIn->GetInteger(pOut);
		if (Fees < 0)
			pGrid->PrintErrorMessage("You entered an invalid Fees, click to continue...");
		///Make the needed validations on the read parameters

		// Clear messages
		//pOut->ClearStatusBar();
	}
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	if (Owner == nullptr)
	{
		// Get a Pointer to the Input / Output Interfaces
		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();
		pOut->PrintMessage("Do you want to buy all cells with cardnum " + to_string(cardNumber) + " ? Price: " + to_string(Price) + " ,Fees: " + to_string(Fees) + " (Y/N)");
		string ans;
		do
		{
			ans = pIn->GetSrting(pOut);
			pOut->ClearStatusBar();
			if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES" || ans == "1") ans = "yes";
			else if (ans == "n" || ans == "N" || ans == "no" || ans == "NO" || ans == "0") ans = "no";
			else pGrid->PrintErrorMessage("Error: Wrong Input ! Try again ...");
		} while (!(ans == "yes") && !(ans == "no"));
		if (ans == "yes")
		{
			if (Price <= pPlayer->GetWallet())
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - Price);
				Owner = pPlayer;
				pGrid->PrintErrorMessage("You bought the cards successfully...");
			}
			else pGrid->PrintErrorMessage("Error: You don't have enough money...");
		}
	}
	else
	{
		if (pPlayer != Owner)
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - Fees);
			Owner->SetWallet(Owner->GetWallet() + Fees);
		}
	}
}


bool CardTwelve::IsValidCard() const
{
	if (Price > 0 && Fees > 0) return true;
	return false;
}

void CardTwelve::Save(ofstream& save, ObjectType T)
{
	if (T != Cards) return;
	save << cardNumber << " " << position.GetCellNum();
	if (++SavedCards == 1)
		save << " " << Price << " " << Fees;
	save << "\n";
	if (SavedCards == NumberOf12Cards) SavedCards = 0;
}

void CardTwelve::Read(ifstream& load)
{
	int cellpos, p, f;
	load >> cellpos;
	position = CellPosition::GetCellPositionFromNum(cellpos);
	if (NumberOf12Cards == 1)
	{
		load >> p >> f;
		Price = p;
		Fees = f;
	}
}

void CardTwelve::RemoveOwnership()
{
	Owner = NULL;
}

void CardTwelve::EditParameters(Grid* pGrid)
{
	int prevPrice = Price, prevFees = Fees;
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("Enter Price of The Card ..");
	Price = pIn->GetInteger(pOut);
	// Read the endPos parameter
	pOut->PrintMessage("Enter Fees to Pay by Passing Players ..");
	Fees = pIn->GetInteger(pOut);

	///Make the needed validations on the read parameters

	if (!IsValidCard())
	{
		pGrid->PrintErrorMessage("Error: Invalid Values ...");
		Price = prevPrice;
		Fees = prevFees;
		return;
	}
	pGrid->PrintErrorMessage("Card Edited Successfully ...");
	// Clear messages
	pOut->ClearStatusBar();
}

CardTwelve::~CardTwelve()
{
	NumberOf12Cards--;
}
