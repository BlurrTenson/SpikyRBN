#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include "RBN.h"
#include "Node.h"
#pragma once
class InteractionList
{
public:
	InteractionList();
	InteractionList(std::vector<int> , RBN*  );
	InteractionList(const InteractionList& , RBN* );
	~InteractionList(void);
	InteractionList* clone(RBN*) const;
	int size();
	std::vector<Node*> GetParticipentNodes();
	std::map<Node*, int> GetBondingEdges();
	int GetNumberOfBondingEdges();
	RBN* GetParentRBN();
	void CalculateBindingProperty(bool);
	int GetBindingProperty(bool);
private: 
	std::vector<Node*> InteractionListsPtr;
	std::vector<int> InteractionListIdx;
	std::map<Node*, int> BondingEdges;
	RBN* parentRBN;
	bool isEmpty;
	int bindingProp0;
	int bindingProp1;
};

