#pragma once
#include "Action.h"
class CopyCardAction : public Action
{
	CellPosition sourcecardPosition;
public:

	CopyCardAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	virtual ~CopyCardAction();
};
