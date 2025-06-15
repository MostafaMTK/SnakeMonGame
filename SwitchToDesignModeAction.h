#pragma once
#include"Action.h"
class SwitchToDesignModeAction :public Action
{
public:
	SwitchToDesignModeAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	~SwitchToDesignModeAction();
};