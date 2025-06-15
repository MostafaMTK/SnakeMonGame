#include "EditCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
EditCardAction::EditCardAction(ApplicationManager* pApp) :Action(pApp)
{

}
bool EditCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Click On The Source To Edit");
	sourcecardPosition = pIn->GetCellClicked();
	if (!sourcecardPosition.IsValidCell())
	{
		return false;
	}
	pOut->ClearStatusBar();
	return true;
}
void EditCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell ! Click to continue ...");
		return;
	}
	GameObject* SourceObject = pGrid->GetSourceObject(sourcecardPosition);
	if (Card* source = dynamic_cast<Card*>(SourceObject))
	{
		source->EditParameters(pGrid);
	}
	else
		pGrid->PrintErrorMessage("Error:Cell has no cards! Click to continue ...");
}
EditCardAction::~EditCardAction()
{

}