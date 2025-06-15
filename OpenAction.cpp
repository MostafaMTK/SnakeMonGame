#include "OpenAction.h"
#include "Output.h"
#include "Input.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
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

OpenAction::OpenAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

bool OpenAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the startPos parameter
	pOut->PrintMessage("Open Grid: Enter The Name of The File ...");
	filename = pIn->GetSrting(pOut);
	load.open("SavedGrids/" + filename + ".txt");
	if (!load.is_open() || load.eof()) return false;
	// Clear messages
	pOut->ClearStatusBar();
	return true;
}

void OpenAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters())
	{
		load.close();
		pGrid->PrintErrorMessage("Error: Invalid File Name ! Click to continue ...");
		return;
	}
	pGrid->ClearGrid();
	int lnum;
	load >> lnum;
	for (int i = 0; i < lnum; i++)
	{
		CellPosition temp;
		Ladder* pLadder = new Ladder(temp,temp);
		pLadder->Read(load);
		pGrid->AddObjectToCell(pLadder);
	}
	int snum;
	load >> snum;
	for (int i = 0; i < snum; i++)
	{
		CellPosition temp;
		Snake* pSnake = new Snake(temp,temp);
		pSnake->Read(load);
		pGrid->AddObjectToCell(pSnake);
	}
	int cnum;
	load >> cnum;
	for (int i = 0; i < cnum; i++)
	{
		CellPosition temp;
		int cardNumber;
		load >> cardNumber;
		Card* pCard = NULL; // will point to the card object type
		switch (cardNumber)
		{
		case 1:
			pCard = new CardOne(temp);
			break;
		case 2:
			pCard = new CardTwo(temp);
			break;
		case 3:
			pCard = new CardThree(temp);
			break;
		case 4:
			pCard = new CardFour(temp);
			break;
		case 5:
			pCard = new CardFive(temp);
			break;
		case 6:
			pCard = new CardSix(temp);
			break;
		case 7:
			pCard = new CardSeven(temp);
			break;
		case 8:
			pCard = new CardEight(temp);
			break;
		case 9:
			pCard = new CardNine(temp);
			break;
		case 10:
			pCard = new CardTen(temp);
			break;
		case 11:
			pCard = new CardEleven(temp);
			break;
		case 12:
			pCard = new CardTwelve(temp);
			break;
		case 13:
			pCard = new CardThirteen(temp);
			break;
			// A- Add the remaining cases

		default:
			break;
		}
		pCard->Read(load);
		pGrid->AddObjectToCell(pCard);
	}

	load.close();
}

OpenAction::~OpenAction()
{

}


