#pragma once
#include "Action.h"
class PasteCardAction :public Action
{
	CellPosition destinationcardPosition;
public:

	PasteCardAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	virtual ~PasteCardAction();
};