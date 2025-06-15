#pragma once

#include "Action.h"

class DeleteGameObjectAction : public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition RPos; // 1- The position of the cell to remove the object from

	// Note: These parameters should be read in ReadActionParameters()

public:

	DeleteGameObjectAction(ApplicationManager* pApp); // A Constructor

	virtual bool ReadActionParameters(); // Reads DeleteGameObjectAction action parameters (RPos)

	virtual void Execute(); // Deletes The Object


	virtual ~DeleteGameObjectAction(); // Virtual Destructor

};