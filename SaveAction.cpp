#include "SaveAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

bool SaveAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Read the startPos parameter
	pOut->PrintMessage("Save Grid: Enter The Name of The File ...");
	filename = pIn->GetSrting(pOut);

	if (filename == "") return false;
	// Clear messages
	pOut->ClearStatusBar();
	return true;
}

void SaveAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid File Name ! Click to continue ...");
		return;
	}

	save.open("SavedGrids/" + filename + ".txt");
	save << Ladder::Getnumofladders() << "\n";
	pGrid->SaveAll(save, Ladders);
	save << Snake::GetNumberOfSnakes() << "\n";
	pGrid->SaveAll(save, Snakes);
	save << Card::GetNumberOfCards() << "\n";
	pGrid->SaveAll(save, Cards);
	save.close();
}

SaveAction::~SaveAction()
{

}

