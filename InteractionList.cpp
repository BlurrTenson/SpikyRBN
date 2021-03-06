#include "InteractionList.h"

InteractionList::InteractionList( )
{
	isEmpty= true;
}

InteractionList::InteractionList(std::vector<int> nodeIndex, RBN* rbn )
{

	InteractionListsPtr = rbn->GetNodePtrByIndex(nodeIndex);
	InteractionListIdx = nodeIndex;
	parentRBN = rbn; 
	isEmpty = false;
	bindingProp0 =0;
	bindingProp1 =0;
	for(int itIL = 0; itIL< InteractionListsPtr.size() - 1; itIL++)
	{
		BondingEdges.insert(std::pair<Node*, int>(InteractionListsPtr[itIL],  InteractionListsPtr[itIL]->GetIndexOfInputFrom(InteractionListsPtr[itIL + 1]) ));
		
	}
}

InteractionList::InteractionList(const InteractionList& other , RBN* newParent )
{
	InteractionListIdx = other.InteractionListIdx;
	parentRBN  = newParent;
	isEmpty = other.isEmpty;
	bindingProp0 = other.bindingProp0;
	bindingProp1 = other.bindingProp1;
	InteractionListsPtr = newParent->GetNodePtrByIndex(InteractionListIdx);

	for(int itIL = 0; itIL< InteractionListsPtr.size() - 1; itIL++)
	{
		BondingEdges[InteractionListsPtr[itIL]] = InteractionListsPtr[itIL]->GetIndexOfInputFrom(InteractionListsPtr[itIL + 1]);
//		BondingEdges.insert(std::pair<Node*, int>(InteractionListsPtr[itIL],  InteractionListsPtr[itIL]->GetIndexOfInputFrom(InteractionListsPtr[itIL + 1]) ));
	}

}

InteractionList* InteractionList::clone(RBN* newParent) const
{
	return new InteractionList(*this, newParent );
}

int InteractionList::size()
{
	return InteractionListIdx.size(); 
}

std::vector<Node*> InteractionList::GetParticipentNodes()
{
	return InteractionListsPtr;
}

std::map<Node*, int> InteractionList::GetBondingEdges()
{
	return BondingEdges;
}

void InteractionList::CalculateBindingProperty(bool initState)
{
	std::vector<int> liveliness;
	if(initState)
	{
		bindingProp1 = 0;
		for(int i =0; i<InteractionListsPtr.size(); i++ )
		{
			bindingProp1 = bindingProp1 + parentRBN->GetCycle1LivelinessPtr(InteractionListIdx[i]);
		}
	}else{
		bindingProp0 = 0;
		for(int i =0; i<InteractionListsPtr.size(); i++ )
		{
			bindingProp0 = bindingProp0 + parentRBN->GetCycle0LivelinessPtr(InteractionListIdx[i]);
		}
	}
}

RBN* InteractionList::GetParentRBN()
{
	return parentRBN;
}

int InteractionList::GetNumberOfBondingEdges()
{
	return BondingEdges.size();
}
int InteractionList::GetBindingProperty(bool initState)
{
	if(initState)
	{
		return bindingProp1;
	}else{
		return bindingProp0;
	}
}
InteractionList::~InteractionList(void)
{

}
