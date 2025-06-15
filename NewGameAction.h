#pragma once
#include"Action.h"
class NewGameAction : public Action
{
public:
	NewGameAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	~NewGameAction();
};