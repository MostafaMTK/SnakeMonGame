#pragma once
#include "Card.h"

class CardTwo : public Card
{
	// CardTwo Parameters:
	int walletAmount; // the wallet value needed to increase the player's wallet

public:
	CardTwo(const CellPosition& pos); // A Constructor takes card position

	CardTwo(const CellPosition& pos, Card* c);

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTwo which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo on the passed Player
	// by incrementing the player's wallet by the walletAmount data member
	virtual bool IsValidCard()const;   //checks if the amount added is valid                                             

	virtual void Save(ofstream&, ObjectType);

	virtual void Read(ifstream&);

	virtual void EditParameters(Grid*);

	virtual ~CardTwo(); // A Virtual Destructor
};