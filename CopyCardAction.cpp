#include "CopyCardAction.h"
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
CopyCardAction::CopyCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CopyCardAction::~CopyCardAction()
{
}

bool CopyCardAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Copy Card: Click On The Source Cell ...");
	sourcecardPosition = pIn->GetCellClicked();

	if (!sourcecardPosition.IsValidCell())
	{
		return false;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return true;
}

void CopyCardAction::Execute()
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
			switch (SourceCard->GetCardNumber())
			{
			case 1:
				pGrid->SetClipboard(new CardOne(-1, SourceCard));
				break;
			case 2:
				pGrid->SetClipboard(new CardTwo(-1, SourceCard));
				break;
			case 3:
				pGrid->SetClipboard(new CardThree(-1));
				break;
			case 4:
				pGrid->SetClipboard(new CardFour(-1));

				break;
			case 5:
				pGrid->SetClipboard(new CardFive(-1));
				break;
			case 6:
				pGrid->SetClipboard(new CardSix(-1));

				break;
			case 7:
				pGrid->SetClipboard(new CardSeven(-1));

				break;
			case 8:
				pGrid->SetClipboard(new CardEight(-1));

				break;
			case 9:
				pGrid->SetClipboard(new CardNine(-1, SourceCard));

				break;
			case 10:
				pGrid->SetClipboard(new CardTen(-1));

				break;
			case 11:
				pGrid->SetClipboard(new CardEleven(-1));
				break;
			case 12:
				pGrid->SetClipboard(new CardTwelve(-1));
				break;
			case 13:
				pGrid->SetClipboard(new CardThirteen(-1));
				break;

			default:
				break;

			}
			pGrid->PrintErrorMessage("Card Copied Successfully ...");
			return;
	}
	pGrid->PrintErrorMessage("Error: No Source Cards to copy in this position ...");
	return;
}