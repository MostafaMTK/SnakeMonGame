#include "Ladder.h"
#include "Snake.h"
#include "Player.h"
int Ladder::NumberOfLadders = 0;
Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	NumberOfLadders++;
	///TODO: Do the needed validation
	if (!IsValidLadder()) //if the ladder is invalid set start and end position = toset(-1,-1)
	{
		CellPosition toset;
		position = toset;
		this->endCellPos = toset;
	}
}
bool Ladder::IsValidLadder() const
{
	if (position.IsValidCell() && endCellPos.IsValidCell())
	{
		if (position.HCell() == endCellPos.HCell() && position.VCell() > endCellPos.VCell())
			return true;
	}
	return false;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pPlayer -> MoveToCell (pGrid, endCellPos);

}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

int Ladder::Getnumofladders()
{
	return NumberOfLadders;
}

bool Ladder::IsOverlapping(GameObject* pObj)
{
		if (!pObj) return false;
		if (Ladder* tocheck = dynamic_cast<Ladder*>(pObj))
		{
			if (this->GetPosition().VCell() <= tocheck->GetPosition().VCell() && this->GetPosition().VCell() >= tocheck->GetEndPosition().VCell())
			{
				return true;
			}
			if (this->GetEndPosition().VCell() <= tocheck->GetPosition().VCell() && this->GetEndPosition().VCell() >= tocheck->GetEndPosition().VCell())
			{
				return true;
			}
			if (tocheck->GetPosition().VCell() <= this->GetPosition().VCell() && tocheck->GetPosition().VCell() >= this->GetEndPosition().VCell())
			{
				return true;
			}
			if (tocheck->GetEndPosition().VCell() <= this->GetPosition().VCell() && tocheck->GetEndPosition().VCell() >= this->GetEndPosition().VCell())
			{
				return true;
			}
		}
		else if (Snake* tocheck =dynamic_cast<Snake*>(pObj))
		{
			if (tocheck->GetEndPosition().VCell() == this->position.VCell() || tocheck->GetPosition().VCell() == this->endCellPos.VCell()) return true;
		}
		return false;
}

void Ladder::Save(ofstream& save, ObjectType T)
{
	if (T != Ladders) return;
	save << position.GetCellNum() << " " << endCellPos.GetCellNum() << "\n";
}

void Ladder::Read(ifstream& load)
{
	int Spos, Epos;
	load >> Spos >> Epos;
	position = CellPosition::GetCellPositionFromNum(Spos);
	endCellPos = CellPosition::GetCellPositionFromNum(Epos);
}

Ladder::~Ladder()
{
	NumberOfLadders--;
}
