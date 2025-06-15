#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum),Freezed(false), Poisoned(0),Fired(0)
{
	this->pCell = pCell;
	this->turnCount = 0;
	
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet > 0)
		this->wallet = wallet;
	else this->wallet = 0;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::SetstepCount(int sC)
{
	if (sC >= 1 && sC <= NumHorizontalCells * NumVerticalCells) stepCount = sC;
}

void Player::ResetturnCount()
{
	turnCount = 0;
}

void Player::DecrementTurnCount()
{
	turnCount--;
}

void Player::ResetPlayer()
{
	SetWallet(100);
	UnFreezePlayer();
	Fired = 0;;
	Poisoned = 0 ;
	SetstepCount(1);
	ResetturnCount();
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	if (Freezed) playerColor = SNOW;
	if (Fired) playerColor = color(255, 128, 0);
	if (Poisoned) playerColor = DARKGREEN;
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	justRolledDiceNum = diceNumber;

	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3)
	{
		pGrid->Specialcases(this);
		turnCount = 0;
		return;
	}
	// 3- Set the justRolledDiceNum with the passed diceNumber

	if (this->IsFired())
	{
		this->wallet -= 20;
		pGrid->PrintErrorMessage("You are still on fire ...##" + to_string(Fired));
		this->UnFirePlayer();
	}
	if (this->IsPoisoned())
	{
		justRolledDiceNum--;
		pGrid->PrintErrorMessage("You will now move " + to_string(justRolledDiceNum) + " ...##" + to_string(Poisoned));
		this->UnPoisonPlayer();
	}
	if (this->IsFreezed())
	{
		pGrid->PrintErrorMessage("Current Player is Frozen ...");
		this->UnFreezePlayer();
		return;
	}


	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	if (!wallet)
	{
		pGrid->PrintErrorMessage("You Don't Have any Money You Won't Move! ...");
		return;
	}
	CellPosition pos = this->GetCell()->GetCellPosition();
	stepCount +=  justRolledDiceNum;
	pos.AddCellNum(justRolledDiceNum);
	if (stepCount >= 100)
	{
		pGrid->SetEndGame(true);
		pos = CellPosition::GetCellPositionFromNum(99);
	}
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, pos);
	// 6- Apply() the game object of the reached cell (if any)
	GameObject* pObj = this->GetCell()->GetGameObject();
	if (pObj) pObj->Apply(pGrid, this);
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (pGrid->GetEndGame())
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage(to_string(playerNum) + " Won ! ... The Game Ended..");
		pOut->DrawPlayerWins(playerNum);
		pIn->GetCellClicked();
		pOut->ClearStatusBar();
	}
}

void Player::MoveToCell(Grid* pGrid, const CellPosition& NewPosition)
{
	// == Here are some guideline steps (numbered below) to implement this function ==

// 1- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, NewPosition);
	stepCount = NewPosition.GetCellNum();
// 2- Apply() the game object of the reached cell (if any)
	GameObject* pObj = this->GetCell()->GetGameObject();
	if (pObj) pObj->Apply(pGrid,this);
// 3- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

}

void Player::FreezePlayer()
{
	Freezed = true;
}

void Player::UnFreezePlayer()
{
	Freezed = false;
}

bool Player::IsFreezed()
{
	return Freezed;
}

void Player::FirePlayer()
{
	Fired = 3;
}

void Player::UnFirePlayer()
{
	if (Fired)
		Fired--;
}

bool Player::IsFired()
{
	return Fired;
}


void Player::PoisonPlayer()
{
	Poisoned = 5;
}

void Player::UnPoisonPlayer()
{
	if(Poisoned)
		Poisoned--;
}

bool Player::IsPoisoned()
{
	return Poisoned;
}


int Player::GetjustRolledDiceNum() const
{
	return justRolledDiceNum;
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}