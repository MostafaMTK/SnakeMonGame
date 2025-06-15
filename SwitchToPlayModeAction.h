#pragma once
#include"Action.h"
class SwitchToPlayModeAction :public Action
{
public:
	SwitchToPlayModeAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual void Execute();
	~SwitchToPlayModeAction();
};