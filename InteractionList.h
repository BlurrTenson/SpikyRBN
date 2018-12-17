#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include "RBN.h"
#include "Node.h"
#include <bitset>
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
    std::vector<int> GetParticipentNodesIdx();
	std::map<Node*, int> GetBondingEdges();
	int GetNumberOfBondingEdges();
	RBN* GetParentRBN();
	void CalculateBindingProperty(bool);
    void CalculateBindingPropertyTemp();
	void SetInitialState(std::bitset<20>);
	int GetBindingProperty(bool);
    int GetBindingPropertyTemp();
    int GetNumberNodesWithLivelinessOver(float);
private:
	std::vector<Node*> InteractionListsPtr;
	std::vector<int> InteractionListIdx;
	std::map<Node*, int> BondingEdges;
	RBN* parentRBN;
	bool isEmpty;
	int bindingProp0;
	int bindingProp1;
	int bindingPropTemp;
};

