#pragma once
#include "Action.h"
#include <fstream>
class OpenAction : public Action
{
	// Always add action parameters as private data members

// [Action Parameters]
	string filename; // The Name of The File To Save in
	ifstream load; //  to save the data to the file

	// Note: These parameters should be read in ReadActionParameters()

public:

	OpenAction(ApplicationManager* pApp); // A Constructor

	virtual bool ReadActionParameters(); // Reads AddLadderAction action parameters filename

	virtual void Execute(); // Opens the file and saves the data in


	virtual ~OpenAction(); // Virtual Destructor
};

