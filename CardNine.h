#pragma once
#include"Card.h"
class CardNine : public Card
{
private:
	CellPosition toCell;
public:
	CardNine(const CellPosition& pos);

	CardNine(const CellPosition& pos, Card* c);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual bool IsValidCard()const;

	virtual void Save(ofstream&, ObjectType);

	virtual void Read(ifstream&);

	virtual void EditParameters(Grid*);

	virtual ~CardNine();
};