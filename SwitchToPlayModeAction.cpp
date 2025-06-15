#include "SwitchToPlayModeAction.h"
#include"Grid.h"
#include "Output.h"
SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) :Action(pApp)
{

}
SwitchToPlayModeAction::~SwitchToPlayModeAction()
{

}
bool SwitchToPlayModeAction::ReadActionParameters()
{
	return true;
}
void SwitchToPlayModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->CreatePlayModeToolBar();
	pGrid->ResetData();
	pGrid->SetEndGame(false);
}