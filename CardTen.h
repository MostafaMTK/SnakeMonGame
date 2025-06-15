#pragma once
#include "Card.h"
class CardTen : public Card
{
	// CardTen Parameters:
	static int Price; //The Card Price of
	static int Fees;  //Fees to pay by passing players
	static int NumberOf10Cards;
	static int SavedCards;
	static Player* Owner;
public:
	CardTen(const CellPosition& ); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTen which is: Price - Fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTen on the passed Player
													  // if the Card is not owned asks the player if he wants to buy it 
													  // price is deducted from the player’s wallet in case he chooses to buy the cell
													  //When a player lands on a cell owned by another player (indicated by the same number), they must pay fees to the cell's owner
	virtual bool IsValidCard() const ;

	virtual void Save(ofstream&, ObjectType);

	virtual void Read(ifstream&);

	virtual void RemoveOwnership();

	virtual void EditParameters(Grid*);

	virtual ~CardTen(); // A Virtual Destructor


};

