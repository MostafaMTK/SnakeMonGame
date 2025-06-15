#include "SwitchToDesignModeAction.h"
#include"Grid.h"
#include "Output.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) :Action(pApp)
{

}
SwitchToDesignModeAction::~SwitchToDesignModeAction()
{

}
bool SwitchToDesignModeAction::ReadActionParameters()
{
	return true;
}
void SwitchToDesignModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->CreateDesignModeToolBar();
}