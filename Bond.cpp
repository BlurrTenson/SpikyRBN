#include "Bond.h"



Bond::Bond(InteractionList* ilA, InteractionList* ilB, RBN* participentA, RBN* participentB)
{
	OriginalStructureA = ilA;
	OriginalStructureB = ilB;
	rbnA = participentA;
	rbnB = participentB;
	std::vector<Node*> partNodes;

	
	numberOfSwaps = 0;
}
Bond::Bond(const Bond& other , RBN* aNewRBN, RBN* bNewRBN )
{
	this->OriginalStructureA = other.OriginalStructureA->clone(aNewRBN);
	this->OriginalStructureB = other.OriginalStructureB->clone(bNewRBN);

	this->rbnA = aNewRBN;
	this->rbnB = bNewRBN;

	this->numberOfSwaps = other.numberOfSwaps;


}

Bond* Bond::clone(RBN* aRBN, RBN* bRBN) const
{
	return new Bond(*this, aRBN, bRBN);
}

std::map<Node* , int> Bond::GetBondingEdgesA()
{
	return OriginalStructureA->GetBondingEdges();
}
std::map<Node* , int> Bond::GetBondingEdgesB()
{
	return OriginalStructureB->GetBondingEdges();
}
InteractionList* Bond::GetOriginalStructureA()
{
	return OriginalStructureA;
}
InteractionList* Bond::GetOriginalStructureB()
{
	return OriginalStructureB;
}
RBN* Bond::GetParticipentA()
{
	return rbnA;
}
RBN* Bond::GetParticipentB()
{
	return rbnB;
}	
bool Bond::ContainsRBN(RBN* candidate)
{
	if(rbnA == candidate || rbnB == candidate)
	{
		return true;
	}else 
		return false;
}

bool Bond::ContainsInteractionList(InteractionList* candidate)
{
	if(OriginalStructureA == candidate || OriginalStructureB == candidate)
	{
		return true;
	}else 
		return false;
}

InteractionList* Bond::GetILBelongingTo(RBN* candidate)
{
	if(rbnA == candidate )
	{
		return OriginalStructureA;
	}else if( rbnB == candidate){
		return OriginalStructureB;
	}else 
		return NULL;
}

void Bond::BuildBond()
{
	int numberToSwap;
	std::map<Node*, int> BondingEdgesA = OriginalStructureA->GetBondingEdges();
	std::map<Node*, int> BondingEdgesB = OriginalStructureB->GetBondingEdges();
	if(BondingEdgesA.size() < BondingEdgesB.size())
	{
		numberToSwap =  BondingEdgesA.size();
	}else{
		numberToSwap =  BondingEdgesB.size();
	}
	std::vector<Node*> aNodes = OriginalStructureA->GetParticipentNodes();
	std::vector<Node*> bNodes = OriginalStructureB->GetParticipentNodes();
	for(int i =0;i < numberToSwap; i++)
	{
		aNodes[i]->LinkNode(bNodes[i+1], BondingEdgesA[aNodes[i]]);
		bNodes[i]->LinkNode(aNodes[i+1], BondingEdgesB[bNodes[i]]);
	}
	numberOfSwaps = numberToSwap;
}

void Bond::BuildBond(int numberToSwap)
{
	std::map<Node*, int> BondingEdgesA = OriginalStructureA->GetBondingEdges();
	std::map<Node*, int> BondingEdgesB = OriginalStructureB->GetBondingEdges();
	std::vector<Node*> aNodes = OriginalStructureA->GetParticipentNodes();
	std::vector<Node*> bNodes = OriginalStructureB->GetParticipentNodes();
	for(int i =0;i < numberToSwap; i++)
	{
		aNodes[i]->LinkNode(bNodes[i+1], BondingEdgesA[aNodes[i]]);
		bNodes[i]->LinkNode(aNodes[i+1], BondingEdgesB[bNodes[i]]);
	}

	numberOfSwaps = numberToSwap;
}

void Bond::BreakBond()
{
	std::vector<Node*> aNodes = OriginalStructureA->GetParticipentNodes();
	std::vector<Node*> bNodes = OriginalStructureB->GetParticipentNodes();
	std::map<Node*, int> BondingEdgesA = OriginalStructureA->GetBondingEdges();
	std::map<Node*, int> BondingEdgesB = OriginalStructureB->GetBondingEdges();
	for(int i =0;i < numberOfSwaps; i++)
	{
		aNodes[i]->LinkNode(aNodes[i+1], BondingEdgesA[aNodes[i]]);
		bNodes[i]->LinkNode(bNodes[i+1], BondingEdgesB[bNodes[i]]);
	}
}

void Bond::CalculateBindingPropertyTemp()
{
	OriginalStructureA->CalculateBindingPropertyTemp();
	OriginalStructureB->CalculateBindingPropertyTemp();

}
void Bond::CalculateBindingProperty(bool initState)
{
	OriginalStructureA->CalculateBindingProperty(initState);
	OriginalStructureB->CalculateBindingProperty(initState);

}

int Bond::GetBindingPropertyTempA()
{
	return OriginalStructureA->GetBindingPropertyTemp();
}

int Bond::GetBindingPropertyTempB()
{
	return OriginalStructureB->GetBindingPropertyTemp();
}
int Bond::GetBindingPropertyA(bool initState)
{
	return OriginalStructureA->GetBindingProperty(initState);
}

int Bond::GetBindingPropertyB(bool initState)
{
	return OriginalStructureB->GetBindingProperty(initState);
}

void Bond::SetOriginalStructureANull()
{
	OriginalStructureA = NULL;
}

void Bond::SetOriginalStructureBNull()
{
	OriginalStructureB = NULL;
}

RBN* Bond::GetOther(RBN* current)
{
	if (rbnA == current)
	{
		return rbnB;
	}else if(rbnB == current)
	{
		return rbnA;
	}else {
		return NULL; 
	}
}

Bond::~Bond(void)
{
	delete OriginalStructureA;
	delete OriginalStructureB;
}
