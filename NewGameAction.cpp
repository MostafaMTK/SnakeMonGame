#include "NewGameAction.h"
#include "Input.h"
#include "Output.h"
#include"Grid.h"
NewGameAction::NewGameAction(ApplicationManager* pApp) :Action(pApp)
{

}
NewGameAction::~NewGameAction()
{

}
bool NewGameAction::ReadActionParameters()
{
	return true;
}
void NewGameAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	pGrid->PrintErrorMessage("New Game ...");
	pGrid->ResetData();
	pGrid->SetEndGame(false);
}