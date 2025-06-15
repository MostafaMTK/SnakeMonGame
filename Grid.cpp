#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Snake.h"

Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	CurrentNumberofPlayers = 4;
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		for (int i = 0; i <= 8; i++)
		{
			if (pNewObject->IsOverlapping(CellList[i][pos.HCell()]->GetGameObject()))
			{
				return false;
			}
		}

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		  ////////
		CellList[pos.VCell()][pos.HCell()]->DeleteGameObject();
		//CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::ClearGrid()
{
	for(int i = 0 ; i<NumVerticalCells ; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (GameObject* pObj = CellList[i][j]->GetGameObject())
				RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
		}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);
	if (newPosition.GetCellNum() == -1) return;
	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

void Grid::SaveAll(ofstream& save, ObjectType T)
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (GameObject* pObj = CellList[i][j]->GetGameObject())
				pObj->Save(save, T);
		}
	}
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}


Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % CurrentNumberofPlayers; // this generates value from 0 to MaxPlayerCount - 1
}

void Grid::ResetData()
{
	CellPosition setcell(1);
	currPlayerNumber = 0;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->ResetPlayer();
		UpdatePlayerCell(PlayerList[i], setcell);
	}
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (Card* pCard = CellList[i][j]->HasCard()) pCard->RemoveOwnership();
		}
	}
	do
	{
		pOut->PrintMessage("Enter The Number of Players: ");
		CurrentNumberofPlayers=pIn->GetInteger(pOut);

	} while (CurrentNumberofPlayers<2 || CurrentNumberofPlayers >MaxPlayerCount);
	pOut->ClearStatusBar();
	for (int i = CurrentNumberofPlayers ; i < MaxPlayerCount; i++) PlayerList[i]->ClearDrawing(pOut);
}

void Grid::Specialcases(Player* pPlayer)
{
	int pnum;
	pOut->PrintMessage("Choose:(1->take money,2->ice,3->poisen,4->lighten,5->fire)");
	int c;
	do
	{
		c = pIn->GetInteger(pOut);
		switch (c)
		{
		case 1:
			pPlayer->SetWallet(pPlayer->GetjustRolledDiceNum() * 10 + pPlayer->GetWallet());
			pOut->ClearStatusBar();
			break;
		case 2:
			do {
				pOut->PrintMessage("Enter the player number you want to freeze");
				pnum = pIn->GetInteger(pOut);
			} while (pnum < 0 || pnum>CurrentNumberofPlayers - 1 || PlayerList[pnum] == pPlayer);
			PlayerList[pnum]->FreezePlayer();
			pOut->ClearStatusBar();
			break;
		case 3:
			do {
				pOut->PrintMessage("Enter the player number you want to poison");
				pnum = pIn->GetInteger(pOut);
			} while (pnum < 0 || pnum>CurrentNumberofPlayers-1 ||PlayerList[pnum]==pPlayer);
			PlayerList[pnum]->PoisonPlayer();
			pOut->ClearStatusBar();
			break;
		case 4:
			for (int i = 0; i < CurrentNumberofPlayers; i++)
			{
				if (PlayerList[i] != pPlayer)
					PlayerList[i]->SetWallet(PlayerList[i]->GetWallet() - 20);
			}
			pOut->ClearStatusBar();
			break;
		case 5:
			do {
				pOut->PrintMessage("Enter the player number you want to fire");
				pnum = pIn->GetInteger(pOut);
			} while (pnum < 0 || pnum>CurrentNumberofPlayers - 1 || PlayerList[pnum] == pPlayer);
			PlayerList[pnum]->FirePlayer();
			pOut->ClearStatusBar();
			break;
		default:
			PrintErrorMessage("Enter a number between 1 and 5");
			break;
		}
	} while (c > 5 || c < 1);

}


// ========= Other Getters =========


GameObject* Grid::GetSourceObject(const CellPosition& sc) const
{
	return CellList[sc.VCell()][sc.HCell()]->GetGameObject();

}

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (Ladder* nl = CellList[i][j]->HasLadder())
				return nl;

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Snake* Grid::GetNextSnake(const CellPosition& position)
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the snake in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a snake, if yes return it
			if (Snake* ns = CellList[i][j]->HasSnake())
				return ns;

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}



// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < CurrentNumberofPlayers; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < CurrentNumberofPlayers-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// 2- Draw players
		for (int i = 0; i < CurrentNumberofPlayers; i++)  // To Change The Players Colors if Freezed or Fired of Iced
		{
			PlayerList[i]->Draw(pOut);
		}

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}