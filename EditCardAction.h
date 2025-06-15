#pragma once
#include "Action.h"
class EditCardAction : public Action
{
	CellPosition sourcecardPosition;
public:
	EditCardAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	virtual ~EditCardAction();
};