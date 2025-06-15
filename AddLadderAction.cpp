#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

bool AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	///TODO: Make the needed validations on the read parameters
	if (!startPos.IsValidCell() || !endPos.IsValidCell()|| startPos.VCell() == 0 || startPos.GetCellNum()==1)
	{
		return false;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return true;
}


// Execute the action
void AddLadderAction::Execute() 
{
	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if(!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid cells ! Click to continue ...");
		return;
	}

	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);
	if (!pLadder->IsValidLadder())//check if this ladder is valid
	{
		delete pLadder;   //delete ladder if invalid
		pGrid->PrintErrorMessage("Error: Ladder Is Invalid ! Click to continue ...");
		return;
	}
	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		delete pLadder;
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
