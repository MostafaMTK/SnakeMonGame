#pragma once
#include "Action.h"
class CutCardAction : public Action
{
	CellPosition sourcecardPosition;
public:
	CutCardAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	virtual ~CutCardAction();
};