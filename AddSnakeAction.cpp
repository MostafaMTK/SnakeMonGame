#include "AddSnakeAction.h"


#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

bool AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();




	///TODO: Make the needed validations on the read parameters
	if (!startPos.IsValidCell() || !endPos.IsValidCell() || startPos.VCell()== NumVerticalCells-1 || startPos.GetCellNum()==NumVerticalCells*NumHorizontalCells)
	{
		return false;

	}


	// Clear messages
	pOut->ClearStatusBar();
	return true;
}


// Execute the action
void AddSnakeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters())
	{
		pGrid->PrintErrorMessage("Error: Invalid cells ! Click to continue ...");
		return;
	}

		// Create a Snake object with the parameters read from the user
		Snake* pSnake = new Snake(startPos, endPos);
		if (!pSnake->IsValidSnake())//check if this Snake is valid
		{
			delete pSnake;//delete Snake if in valid
			pGrid->PrintErrorMessage("Error: Snake Is Invalid ! Click to continue ...");
			return;
		}
		// We get a pointer to the Grid from the ApplicationManager

	   // Add the card object to the GameObject of its Cell:
		{
			bool added = pGrid->AddObjectToCell(pSnake);

			// if the GameObject cannot be added
			if (!added)
			{
				delete pSnake;
				// Print an appropriate message
				pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			}
			// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction
		}

}