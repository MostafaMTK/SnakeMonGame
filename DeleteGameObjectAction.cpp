#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

DeleteGameObjectAction::~DeleteGameObjectAction()
{
}

bool DeleteGameObjectAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the RPos parameter
	pOut->PrintMessage("Delete Game Object : Click on The Cell of The Object You Want to Delete...");
	RPos = pIn->GetCellClicked();

	///TODO: Make the needed validations on the read parameters
	if (!RPos.IsValidCell())
	{
		return false;
	}

	// Clear messages
	pOut->ClearStatusBar();
	return true;
}


// Execute the action
void DeleteGameObjectAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell ! Click to continue ...");
		return;
	}

	pGrid->RemoveObjectFromCell(RPos);
}
