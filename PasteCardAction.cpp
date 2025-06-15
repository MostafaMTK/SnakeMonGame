#include "PasteCardAction.h"
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
PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

PasteCardAction::~PasteCardAction()
{
}

bool PasteCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Paste Card: click on the destination cell");
	destinationcardPosition = pIn->GetCellClicked();

	if (!destinationcardPosition.IsValidCell())
	{
		return false;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return true;
}

void PasteCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell ! Click to continue ...");
		return;
	}
	Card* destinationcard = NULL;
	Card* sourcecard = pGrid->GetClipboard();
	if (sourcecard)
	{
		switch (sourcecard->GetCardNumber())
		{
		case 1:
			destinationcard = new CardOne(destinationcardPosition, sourcecard);
			break;
		case 2:
			destinationcard = new CardTwo(destinationcardPosition, sourcecard);
			break;
		case 3:
			destinationcard = new CardThree(destinationcardPosition);
			break;
		case 4:
			destinationcard = new CardFour(destinationcardPosition);

			break;
		case 5:
			destinationcard = new CardFive(destinationcardPosition);
			break;
		case 6:
			destinationcard = new CardSix(destinationcardPosition);

			break;
		case 7:
			destinationcard = new CardSeven(destinationcardPosition);

			break;
		case 8:
			destinationcard = new CardEight(destinationcardPosition);

			break;
		case 9:
			destinationcard = new CardNine(destinationcardPosition, sourcecard);

			break;
		case 10:
			destinationcard = new CardTen(destinationcardPosition);

			break;
		case 11:
			destinationcard = new CardEleven(destinationcardPosition);
			break;
		case 12:
			destinationcard = new CardTwelve(destinationcardPosition);
			break;
		case 13:
			destinationcard = new CardThirteen(destinationcardPosition);
			break;

		default:
			break;

		}
	}
	else
	{
		pGrid->PrintErrorMessage("Error: The Clipboard is Empty");
		return;
	}
	bool added = pGrid->AddObjectToCell(destinationcard);
	if (added)
	{
		if (sourcecard->GetPosition().GetCellNum() == -1) delete sourcecard;
		else pGrid->RemoveObjectFromCell(sourcecard->GetPosition());
		pGrid->SetClipboard(NULL);
	}
	// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
	else
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object, Click to continue ...");
		delete destinationcard;
	}
	return;
}