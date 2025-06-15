#pragma once
#include"Action.h"
class InputDiceValueAction :public Action
{
	int Dicevalue;
public:
	InputDiceValueAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	~InputDiceValueAction();
};

