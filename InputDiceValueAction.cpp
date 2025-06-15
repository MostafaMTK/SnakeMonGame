#include "InputDiceValueAction.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
#include"Player.h"
InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) :Action(pApp)
{

}
InputDiceValueAction::~InputDiceValueAction()
{

}
bool InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();



	pOut->PrintMessage("Enter A Dice Value ...");
	Dicevalue = pIn->GetInteger(pOut);
	while (Dicevalue < 1 || Dicevalue>6)
	{
		pOut->PrintMessage("Invalid Dice Value,Please Enter A number between 1 and 6");
		Dicevalue = pIn->GetInteger(pOut);
	}
	pOut->DrawDiceValue(Dicevalue);
	pIn->GetCellClicked(); 
	pOut->ClearStatusBar();
	return true;
}
void  InputDiceValueAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (pGrid->GetEndGame())
	{
		pOut->PrintMessage("Game Is Over ...");
		pOut->DrawPlayerWins(4);
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
		return;
	}

	Player* pPlayer = pGrid->GetCurrentPlayer();
		ReadActionParameters();
		pPlayer->Move(pGrid, Dicevalue);

	pGrid->AdvanceCurrentPlayer();
}