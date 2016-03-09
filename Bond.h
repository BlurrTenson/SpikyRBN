#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include "Node.h"
#include "RBN.h"
#include "InteractionList.h"
#include <vector>
#include <list>
#include <map>
class Bond
{
public:
	Bond(InteractionList*, InteractionList*, RBN*, RBN*);
	~Bond(void);
	Bond(const Bond& , RBN*, RBN* );
	
	Bond* clone(RBN*, RBN*) const;

	std::map<Node* , int> GetBondingEdgesA();
	std::map<Node* , int> GetBondingEdgesB();
	InteractionList* GetOriginalStructureA();
	InteractionList* GetOriginalStructureB();
	void SetOriginalStructureANull();
	void SetOriginalStructureBNull();
	RBN* GetParticipentA();
	RBN* GetParticipentB();
	//Returns true if this bond involves the RBN input
	bool ContainsRBN(RBN*);
	//REturns the participent RBN that isn't the one passed in
	RBN* GetOther(RBN*);
	bool ContainsInteractionList(InteractionList*);
	//If the RBN* is one of the two participating RBNs it returns the IL belonging to it , else it returns an empty vector
	InteractionList* GetILBelongingTo(RBN*);
	//Builds the bond by moving the relevent IL node inputs Make as many swaps as possible
	void BuildBond();
	//Swap exactly int
	void BuildBond(int);
	void CalculateBindingProperty(bool);
	int GetBindingPropertyA(bool);
	int GetBindingPropertyB(bool);
	void BreakBond();
private:

	InteractionList* OriginalStructureA;
	InteractionList* OriginalStructureB;

	std::vector<std::vector<Node*> > BondStructure;

	RBN* rbnA;
	RBN* rbnB;
	int numberOfSwaps;


};

