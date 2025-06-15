#include "Snake.h"
#include "Ladder.h"
#include "Player.h"
int Snake::NumberOfSnakes = 0;
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	NumberOfSnakes++;
	///TODO: Do the needed validation
	if (!IsValidSnake()) //if the ladder is invalid set start and end position = toset(-1,-1)
	{
		CellPosition toset;
		position = toset;
		this->endCellPos = toset;
	}
}

bool Snake::IsValidSnake() const
{
	if (position.IsValidCell() && endCellPos.IsValidCell())
	{
		if (position.HCell() == endCellPos.HCell() && position.VCell() < endCellPos.VCell())
			return true;
	}
	return false;
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below



	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pGrid->PrintErrorMessage("You have reached a snake. Click to continue ...");
	pPlayer->MoveToCell(pGrid, endCellPos);

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

int Snake::GetNumberOfSnakes()
{
	return NumberOfSnakes;
}

bool Snake::IsOverlapping(GameObject* pObj)
{
	if (!pObj) return false;
	if (pObj->GetPosition().VCell() == this->endCellPos.VCell() && dynamic_cast<Ladder*>(pObj))
	{
		return true;
	}
		if (Snake* tocheck = dynamic_cast<Snake*>(pObj))
		{
			if (this->GetPosition().VCell() >= tocheck->GetPosition().VCell() && this->GetPosition().VCell() <= tocheck->GetEndPosition().VCell())
			{
				return true;
			}
			if (this->GetEndPosition().VCell() >= tocheck->GetPosition().VCell() && this->GetEndPosition().VCell() <= tocheck->GetEndPosition().VCell())
			{
				return true;
			}
			if (tocheck->GetPosition().VCell() >= this->GetPosition().VCell() && tocheck->GetPosition().VCell() <= this->GetEndPosition().VCell())
			{
				return true;
			}
			if (tocheck->GetEndPosition().VCell() >= this->GetPosition().VCell() && tocheck->GetEndPosition().VCell() <= this->GetEndPosition().VCell())
			{
				return true;
			}
		}
		else if (Ladder* tocheck = dynamic_cast<Ladder*>(pObj))
		{
			if (tocheck->GetEndPosition().VCell() == this->position.VCell()) return true;
		}
	return false;
}

void Snake::Save(ofstream& save, ObjectType T)
{
	if (T != Snakes) return;
	save << position.GetCellNum() << " " << endCellPos.GetCellNum() << "\n";
}

void Snake::Read(ifstream& load)
{
	int Spos, Epos;
	load >> Spos >> Epos;
	position = CellPosition::GetCellPositionFromNum(Spos);
	endCellPos = CellPosition::GetCellPositionFromNum(Epos);
}

Snake::~Snake()
{
	NumberOfSnakes--;
}
