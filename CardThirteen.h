#pragma once
#include "Card.h"
class CardThirteen : public Card
{
	// CardThirteen Parameters:
	static int Price; //The Card Price of
	static int Fees;  //Fees to pay by passing players
	static int NumberOf13Cards;
	static int SavedCards;
	static Player* Owner;
public:
	CardThirteen(const CellPosition&); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardThirteen which is: Price - Fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThirteen on the passed Player
	// if the Card is not owned asks the player if he wants to buy it 
	// price is deducted from the player�s wallet in case he chooses to buy the cell
	//When a player lands on a cell owned by another player (indicated by the same number), they must pay fees to the cell's owner
	virtual bool IsValidCard() const ;

	virtual void Save(ofstream&, ObjectType);

	virtual void Read(ifstream&);

	virtual void RemoveOwnership();

	virtual void EditParameters(Grid*);

	virtual ~CardThirteen(); // A Virtual Destructor


};

