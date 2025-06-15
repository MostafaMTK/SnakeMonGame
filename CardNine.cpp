#include "CardNine.h"
CardNine::CardNine(const CellPosition& pos) : Card(pos)
{
	cardNumber = 9;
}

CardNine::CardNine(const CellPosition& pos, Card* c) : Card(pos)
{
	CardNine* sc = dynamic_cast<CardNine*>(c);
	cardNumber = 9;
	this->toCell = sc->toCell;
}

CardNine::~CardNine(void)
{
}
void CardNine::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("CardNine: Click on its  specific cell");
	toCell = pIn->GetCellClicked();
	if (!IsValidCard())
		pGrid->PrintErrorMessage("Error: Invalid specific cell ...");
	pOut->ClearStatusBar();
}

bool CardNine::IsValidCard() const
{
	if (toCell.IsValidCell()&&((toCell.VCell()!=position.VCell()||toCell.HCell()!=position.HCell())))
		return true;
	else
		return false;
}

void CardNine::Save(ofstream& save, ObjectType T)
{
	if (T != Cards) return;
	save << cardNumber << " " << position.GetCellNum() << " "  << toCell.GetCellNum() << "\n";
}

void CardNine::Read(ifstream& load)
{
	int cellpos ,SCell;
	load >> cellpos >> SCell;
	position = CellPosition::GetCellPositionFromNum(cellpos);
	toCell = CellPosition::GetCellPositionFromNum(SCell);
}

void CardNine::EditParameters(Grid* pGrid)
{
	CellPosition prevtoCell = toCell;
	ReadCardParameters(pGrid);
	if (!IsValidCard())
	{
		toCell = prevtoCell;
		return;
	}
	pGrid->PrintErrorMessage("Card Edited Successfully ...");
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pPlayer->MoveToCell(pGrid, toCell);

}