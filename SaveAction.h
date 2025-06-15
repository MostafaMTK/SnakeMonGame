#pragma once
#include "Action.h"
#include <fstream>
class SaveAction : public Action
{
	// Always add action parameters as private data members

// [Action Parameters]
	string filename; // The Name of The File To Save in
	ofstream save; //  to save the data to the file

	// Note: These parameters should be read in ReadActionParameters()

public:

	SaveAction(ApplicationManager* pApp); // A Constructor

	virtual bool ReadActionParameters(); // Reads AddLadderAction action parameters filename

	virtual void Execute(); // Opens the file and saves the data in


	virtual ~SaveAction(); // Virtual Destructor
};

