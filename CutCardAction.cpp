#include "CutCardAction.h"
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
CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CutCardAction::~CutCardAction()
{
}

bool CutCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Cut Card: Click On The Source Cell ...");
	sourcecardPosition = pIn->GetCellClicked();

	if (!sourcecardPosition.IsValidCell())
	{
		return false;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return true;
}

void CutCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid Cell ! Click to continue ...");
		return;
	}
	GameObject* SourceObject = pGrid->GetSourceObject(sourcecardPosition);
	if (Card* SourceCard = dynamic_cast<Card*>(SourceObject))
	{
	Card* prevClipboard = pGrid->GetClipboard();
	if (prevClipboard)
	{
		if (prevClipboard->GetPosition().GetCellNum() == -1) delete prevClipboard;
	}
		pGrid->SetClipboard(SourceCard);
		pGrid->PrintErrorMessage("Cut Card Action Happened Successfully ...");
		//pGrid->RemoveObjectFromCell(sourcecardPosition);
		return;
	}
	pGrid->PrintErrorMessage("Error: No Source Cards to Cut in this position ...");
	return;
}
