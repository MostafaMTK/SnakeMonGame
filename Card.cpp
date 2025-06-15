#include "Card.h"
int Card::NumberOfCards = 0;

Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
	NumberOfCards++;
}

void Card::SetCardNumber(int cnum)
{
	if (IsValidCard())
	{
		cardNumber = cnum;// needs validation
	}
	else 
		cardNumber = -1;
}
bool Card::IsValidCard() const
{
	if (cardNumber >= 1 && cardNumber <= 13)
		return true;
	return false;
}
int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position,cardNumber);

}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

bool Card::IsOverlapping(GameObject*)
{
	return false;
}

void Card::Save(ofstream& save, ObjectType T)
{
	if (T != Cards) return;
	save << cardNumber << " " << position.GetCellNum() << "\n";
}


void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}
int Card::GetNumberOfCards()
{
	return NumberOfCards;
}

void Card::Read(ifstream& load)
{
	int cellpos;
	load >> cellpos;
	position = CellPosition::GetCellPositionFromNum(cellpos);
}

void Card::RemoveOwnership()
{
	return;
}

void Card::EditParameters(Grid* pGrid)
{
	pGrid->PrintErrorMessage("The Card Has No Parameters to Edit...");
}


Card::~Card()
{
	NumberOfCards--;
}
