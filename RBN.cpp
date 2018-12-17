#include "RBN.h"

#include <iostream>

#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <algorithm> 
#include <limits>
using namespace std;

RBN::RBN(int nodeNumber, int inputsToNode, int bondingSiteNumber)
{
	rbnSize= nodeNumber;
	k = inputsToNode;
	b = 0;
	GenerateNodes();
	GenerateNetworkTopology();	
	GenerateInitValue();
	CalculateCycleLenght();
	CalculateTransiant();
	GenerateInteractionGroupInfluence(bondingSiteNumber, -1);
	boundGroup1 = -1;
	boundGroup2 = -1;

	for (int i = 0; i< rbnSize; i++)
	{
		nodeLivelinessCycle0.emplace(i, 0);
		nodeLivelinessTrans0.emplace(i, 0);
		nodeLivelinessCycle1.emplace(i, 0);
		nodeLivelinessTrans1.emplace(i, 0);
		nodeLivelinessCycleTemp.emplace(i, 0);
		nodeLivelinessTransTemp.emplace(i, 0);
	}
	//print_structMatrix();
}

RBN::RBN(int nodeNumber, int inputsToNode, int bondingSiteNumber , std::vector<bool> givenPattern, char rbnName)
{
	rbnSize= nodeNumber;
	k = inputsToNode;
	b = 0;
	symbol = rbnName;
	GenerateNodes();
	GenerateNetworkTopology();
	initPattern = givenPattern;
	CalculateCycleLenght();
	CalculateTransiant();
	GenerateInteractionGroupInfluence(bondingSiteNumber, -1);
	CalculateLiveliness();
	boundGroup1 = -1;
	boundGroup2 = -1;
	boundGroup3 = -1;
	boundGroup4 = -1;
	boundGroup5 = -1;
	boundGroup6 = -1;
	boundGroup7 = -1;
	boundGroup8 = -1;
	
	for (int i = 0; i< rbnSize; i++)
	{
		nodeLivelinessCycle0.emplace(i, 0);
		nodeLivelinessTrans0.emplace(i, 0);
		nodeLivelinessCycle1.emplace(i, 0);
		nodeLivelinessTrans1.emplace(i, 0);
		nodeLivelinessCycleTemp.emplace(i, 0);
		nodeLivelinessTransTemp.emplace(i, 0);
	}
	//print_structMatrix();
}
RBN::RBN(int nodeNumber, int inputsToNode, int bondingSiteNumber , std::vector<bool> givenPattern)
{
	rbnSize= nodeNumber;
	k = inputsToNode;
	b = 0;
	
	GenerateNodes();
	GenerateNetworkTopology();
	initPattern = givenPattern;
	CalculateCycleLenght();
	CalculateTransiant();
	GenerateInteractionGroupInfluence(bondingSiteNumber, -1);
	CalculateLiveliness();
	boundGroup1 = -1;
	boundGroup2 = -1;
	boundGroup3 = -1;
	boundGroup4 = -1;
	boundGroup5 = -1;
	boundGroup6 = -1;
	boundGroup7 = -1;
	boundGroup8 = -1;
	
	for (int i = 0; i < rbnSize; i++)
	{
		nodeLivelinessCycle0.emplace(i, 0);
		nodeLivelinessTrans0.emplace(i, 0);
		nodeLivelinessCycle1.emplace(i, 0);
		nodeLivelinessTrans1.emplace(i, 0);
		nodeLivelinessCycleTemp.emplace(i, 0);
		nodeLivelinessTransTemp.emplace(i, 0);

	}
	//print_structMatrix();
}
//TODO Neeed to correctly asighn rbn size and k not hard code
RBN::RBN(std::vector<string> rbnDefine)
{
	int j;
    rbnSize= 12;
    k = 2;
    b = 0;
	std::vector<int> strutMatrixLine;
    initPattern = std::vector<bool> (12, true);
	//Generate node list
    for(int i = 0; i < 12; i++)
	{

		nodeList.push_back(new Node(rbnDefine[i]));
	}
    // generate topology

    std::map<int, int> influenceMap;

    for(int i =0; i< rbnSize; i++)
    {
        influenceMap.emplace(i, 0);
    }
	for(int i = 12; i < 24; i++)
	{
		std::stringstream ss(rbnDefine[i]);
		while (ss >> j)
		{
			 if (ss.peek() == ',')
                ss.ignore();

			strutMatrixLine.push_back(j);
		}

        for(int k = 0; k < strutMatrixLine.size(); k++)
        {
            influenceMap[strutMatrixLine[k]]++;
        }
		structMatrix.push_back(strutMatrixLine);

        nodeList[i - 12]->LinkNode(nodeList[structMatrix[i - 12][0]]);
        nodeList[i - 12]->LinkNode(nodeList[structMatrix[i - 12][1]]);

		strutMatrixLine.clear();
	}
    nodeInfluence=influenceMap;

    std::stringstream ss(rbnDefine[24]);
    std::string ILString;
    std::vector<int> interactionGroup;

	std::string s = rbnDefine[24];
	std::string delimiter = ";";

	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		std::cout << token << std::endl;
		s.erase(0, pos + delimiter.length());

		std::stringstream ss(token);
		while (ss >> j)
		{
			 if (ss.peek() == ',')
                ss.ignore();

			interactionGroup.push_back(j);
		}

		InteractionGroups.push_back(interactionGroup);
		interactionGroup.clear();
	}
   



}

RBN::RBN(const RBN& other)
{
	rbnSize = other.rbnSize;
	k = other.k;
	b = other.b;
	cycleLength = other.cycleLength;
	transiantLenght = other.transiantLenght;
	initPatternValue = other.initPatternValue;
	structMatrix = other.structMatrix;
	InteractionGroups = other.InteractionGroups;
	initPattern = other.initPattern;
	nextState = other.nextState;
	interfaceConnectionMap = other.interfaceConnectionMap;
	symbol = other.symbol;
	boundGroup1 = other.boundGroup1;
	boundGroup2 = other.boundGroup2;
	boundGroup3 = other.boundGroup3;
	boundGroup4 = other.boundGroup4;
	boundGroup5 = other.boundGroup5;
	boundGroup6 = other.boundGroup6;
	boundGroup7 = other.boundGroup7;
	boundGroup8 = other.boundGroup8;
	uniqueID = other.uniqueID;
	for(int i=0; i < other.nodeList.size(); i++)
	{
		nodeList.push_back(other.nodeList[i]->clone()); // create copies of the nodes
	}

	for(int i = 0 ; i < rbnSize; i ++)
	{
		for(int j = 0 ; j < structMatrix[i].size(); j ++)
		{
			nodeList[i]->LinkNode(nodeList[structMatrix[i][j]]); // use the connection map to find which node an interface node is connected to and connect it
		}
	}
	nodeLivelinessCycle0 = other.nodeLivelinessCycle0;
	nodeLivelinessTrans0 = other.nodeLivelinessTrans0;
	nodeLivelinessCycle1 = other.nodeLivelinessCycle1;
	nodeLivelinessTrans1 = other.nodeLivelinessTrans1;
	nodeLivelinessCycleTemp = other.nodeLivelinessCycleTemp;
	nodeLivelinessTransTemp = other.nodeLivelinessTransTemp;
}
RBN* RBN::clone() const
{
	return new RBN(*this);
}

char RBN::GetRBNSymbol()
{
	return symbol;
}

//This is hacked together , wont work in general , bound group 1 and 2 are the groups involved in the just created bond , if you want to add
//more then 3 atoms together this will not work , i just couldnt be aresed so ugly stick. 
bool RBN::CombineWith(RBN other, int numberOfLinks)
{
	int oldStructSize = structMatrix.size();
	int oldIGSize = InteractionGroups.size();

	for(int i=0; i < other.nodeList.size(); i++)
	{
		nodeList.push_back(other.nodeList[i]->clone()); // create copies of the nodes
	}

	for(int i = 0; i < other.structMatrix.size(); i++)
	{
		for(int j = 0; j < other.structMatrix[i].size(); j++)
		{
			other.structMatrix[i][j] = other.structMatrix[i][j] + rbnSize;
		}
		structMatrix.push_back(other.structMatrix[i]);
	}
	for(int i = 0; i < other.InteractionGroups.size(); i++)
	{
		for(int j = 0; j < other.InteractionGroups[i].size(); j++)
		{
			other.InteractionGroups[i][j] = other.InteractionGroups[i][j] + rbnSize;
		}
		InteractionGroups.push_back(other.InteractionGroups[i]);
	}
	int bindingGroupIndexThis = -1;
	int bindingGroupIndexOther = -1;
	for(int i=0; i< oldIGSize; i ++)
	{
		
		if(InteractionGroups[i].size() >= numberOfLinks + 1 && i != boundGroup1 && i != boundGroup2 && i != boundGroup3 && i != boundGroup4 && i != boundGroup5 && i != boundGroup6 && i != boundGroup7 && i != boundGroup8)
		{
			bindingGroupIndexThis = i;
			i =  oldIGSize;
		}
	}

	for(int i=oldIGSize; i< InteractionGroups.size(); i ++)
	{
		
		if(InteractionGroups[i].size() >= numberOfLinks + 1 && i != boundGroup1 && i != boundGroup2 && i != boundGroup3 && i != boundGroup4 && i != boundGroup5 && i != boundGroup6 && i != boundGroup7 && i != boundGroup8)
		{
			bindingGroupIndexOther = i;
			i =  InteractionGroups.size();
		}
	}
	if(bindingGroupIndexOther > -1 && bindingGroupIndexThis > -1)
	{
		for (int i = 0; i < numberOfLinks; i ++)
		{
			if (structMatrix[InteractionGroups[bindingGroupIndexThis][i]][0] == InteractionGroups[bindingGroupIndexThis][i+1])
			{
			
				structMatrix[InteractionGroups[bindingGroupIndexThis][i]][0] = InteractionGroups[bindingGroupIndexOther][i+1];
			}else 
			{
				structMatrix[InteractionGroups[bindingGroupIndexThis][i]][1] = InteractionGroups[bindingGroupIndexOther][i+1];
			}

			if (structMatrix[InteractionGroups[bindingGroupIndexOther][i]][0] == InteractionGroups[bindingGroupIndexOther][i+1])
			{
			
				structMatrix[InteractionGroups[bindingGroupIndexOther][i]][0] = InteractionGroups[bindingGroupIndexThis][i+1];
			}else 
			{
				structMatrix[InteractionGroups[bindingGroupIndexOther][i]][1] = InteractionGroups[bindingGroupIndexThis][i+1];
			}
		}
		rbnSize = rbnSize + other.rbnSize;
		initPattern = std::vector<bool> (rbnSize, true );
		if(boundGroup2 ==  -1)
		{
		boundGroup1 = bindingGroupIndexThis;
		boundGroup2 = bindingGroupIndexOther;
		}else if (boundGroup4 == -1)
		{
		boundGroup3 = bindingGroupIndexThis;
		boundGroup4 = bindingGroupIndexOther;
		}else if (boundGroup6 == -1)
		{
		boundGroup5 = bindingGroupIndexThis;
		boundGroup6 = bindingGroupIndexOther;
		}else if (boundGroup8 == -1)
		{
		boundGroup7 = bindingGroupIndexThis;
		boundGroup8 = bindingGroupIndexOther;
		}
		ConstructRBN();
		RecalcualteProperties();
		return true;
	}else
		return false;
	
	
}

void RBN::ConstructRBN()
{
	for(int i = 0;i < structMatrix.size(); i++)
	{
		nodeList[i]->RemoveInputs();
		nodeList[i]->LinkNode(nodeList[structMatrix[i][0]]);
		nodeList[i]->LinkNode(nodeList[structMatrix[i][1]]);
	}
}

int RBN::GetUniqueID()
{
	return uniqueID;
}

void RBN::SetRBNSymbol(char a)
{
	symbol = a;
}

//This is hacked together , wont work in general , bound group 1 and 2 are the groups involved in the just created bond , if you want to add
//more then 3 atoms together this will not work , i just couldnt be aresed so ugly stick. 
bool RBN::CombineLeastWith(RBN other, int numberOfLinks)
{
	int oldStructSize = structMatrix.size();
	int oldIGSize = InteractionGroups.size();
	int idxLastThis = 0;
	int idxLastOther = 0;
	for(int i=0; i < other.nodeList.size(); i++)
	{
		nodeList.push_back(other.nodeList[i]->clone()); // create copies of the nodes
	}

	for(int i = 0; i < other.structMatrix.size(); i++)
	{
		for(int j = 0; j < other.structMatrix[i].size(); j++)
		{
			other.structMatrix[i][j] = other.structMatrix[i][j] + rbnSize;
		}
		structMatrix.push_back(other.structMatrix[i]);
	}
	for(int i = 0; i < other.InteractionGroups.size(); i++)
	{
		for(int j = 0; j < other.InteractionGroups[i].size(); j++)
		{
			other.InteractionGroups[i][j] = other.InteractionGroups[i][j] + rbnSize;
		}
		InteractionGroups.push_back(other.InteractionGroups[i]);
	}
	int bindingGroupIndexThis = -1;
	int bindingGroupIndexOther = -1;
	for(int i=0; i< oldIGSize; i ++)
	{
		
		if(InteractionGroups[i].size() >= numberOfLinks + 1 && i != boundGroup1 && i != boundGroup2 && i != boundGroup3 && i != boundGroup4 && i != boundGroup5 && i != boundGroup6 && i != boundGroup7 && i != boundGroup8)
		{
			bindingGroupIndexThis = i;
			i =  oldIGSize;
		}
	}

	for(int i=oldIGSize; i< InteractionGroups.size(); i ++)
	{
		
		if(InteractionGroups[i].size() >= numberOfLinks + 1 && i != boundGroup1 && i != boundGroup2 && i != boundGroup3 && i != boundGroup4 && i != boundGroup5 && i != boundGroup6 && i != boundGroup7 && i != boundGroup8)
		{
			bindingGroupIndexOther = i;
			i =  InteractionGroups.size();
		}
	}
	if(bindingGroupIndexOther > -1 && bindingGroupIndexThis > -1)
	{
		for (int i = 0; i < numberOfLinks; i ++)
		{
			idxLastThis =  InteractionGroups[bindingGroupIndexThis].size() - 2 - i;
			idxLastOther =  InteractionGroups[bindingGroupIndexOther].size() - 2 - i;
			if (structMatrix[InteractionGroups[bindingGroupIndexThis][idxLastThis]][0] == InteractionGroups[bindingGroupIndexThis][idxLastThis+1])
			{
			
				structMatrix[InteractionGroups[bindingGroupIndexThis][idxLastThis]][0] = InteractionGroups[bindingGroupIndexOther][idxLastOther+1];
			}else 
			{
				structMatrix[InteractionGroups[bindingGroupIndexThis][idxLastThis]][1] = InteractionGroups[bindingGroupIndexOther][idxLastOther+1];
			}

			if (structMatrix[InteractionGroups[bindingGroupIndexOther][idxLastOther]][0] == InteractionGroups[bindingGroupIndexOther][idxLastOther+1])
			{
			
				structMatrix[InteractionGroups[bindingGroupIndexOther][idxLastOther]][0] = InteractionGroups[bindingGroupIndexThis][idxLastThis+1];
			}else 
			{
				structMatrix[InteractionGroups[bindingGroupIndexOther][idxLastOther]][1] = InteractionGroups[bindingGroupIndexThis][idxLastThis+1];
			}
		}
		rbnSize = rbnSize + other.rbnSize;
		initPattern = std::vector<bool> (rbnSize, true );
		if(boundGroup2 ==  -1)
		{
		boundGroup1 = bindingGroupIndexThis;
		boundGroup2 = bindingGroupIndexOther;
		}else if (boundGroup4 == -1)
		{
		boundGroup3 = bindingGroupIndexThis;
		boundGroup4 = bindingGroupIndexOther;
		}else if (boundGroup6 == -1)
		{
		boundGroup5 = bindingGroupIndexThis;
		boundGroup6 = bindingGroupIndexOther;
		}else if (boundGroup8 == -1)
		{
		boundGroup7 = bindingGroupIndexThis;
		boundGroup8 = bindingGroupIndexOther;
		}
		RecalcualteProperties();
		return true;
	}else
		return false;
	
	
}
bool RBN::CombineSingeltonsWith(RBN* other)
{
	int oldStructSize = structMatrix.size();
	int oldIGSize = InteractionGroups.size();
	int idxLastThis = 0;
	int idxLastOther = 0;
	for(int i=0; i < other->nodeList.size(); i++)
	{
		nodeList.push_back(other->nodeList[i]->clone()); // create copies of the nodes
	}

	for(int i = 0; i < other->structMatrix.size(); i++)
	{
		for(int j = 0; j < other->structMatrix[i].size(); j++)
		{
			other->structMatrix[i][j] = other->structMatrix[i][j] + rbnSize;
		}
		structMatrix.push_back(other->structMatrix[i]);
	}
	for(int i = 0; i < other->InteractionGroups.size(); i++)
	{
		for(int j = 0; j < other->InteractionGroups[i].size(); j++)
		{
			other->InteractionGroups[i][j] = other->InteractionGroups[i][j] + rbnSize;
		}
		InteractionGroups.push_back(other->InteractionGroups[i]);
	}
	int bindingSingletonIndexThis = -1;
	int bindingSingletonSelfLinkThis = -1;
	int bindingSingletonIndexOther = -1;
	int bindingSingletonSelfLinkOther = -1;
	for(int i=0; i< oldIGSize; i ++)
	{
		
		if(InteractionGroups[i].size() == 1 && i != boundGroup1 && i != boundGroup2 && i != boundGroup3 && i != boundGroup4 && i != boundGroup5 && i != boundGroup6 && i != boundGroup7 && i != boundGroup8)
		{
			if(structMatrix[InteractionGroups[i][0]][0] == InteractionGroups[i][0])  
			{
				bindingSingletonIndexThis = InteractionGroups[i][0];
				bindingSingletonSelfLinkThis = 0;
				i =  oldIGSize;
			}else if (structMatrix[InteractionGroups[i][0]][1] == InteractionGroups[i][0]) 
			{
				bindingSingletonIndexThis = InteractionGroups[i][0];
				bindingSingletonSelfLinkThis = 1;
				i =  oldIGSize;
			}
		}
	}

	for(int i=oldIGSize; i< InteractionGroups.size(); i ++)
	{
		if(InteractionGroups[i].size() == 1 && i != boundGroup1 && i != boundGroup2 && i != boundGroup3 && i != boundGroup4 && i != boundGroup5 && i != boundGroup6 && i != boundGroup7 && i != boundGroup8)
		{
			if(structMatrix[InteractionGroups[i][0]][0] == InteractionGroups[i][0])  
			{
				bindingSingletonIndexOther = InteractionGroups[i][0];
				bindingSingletonSelfLinkOther = 0;
				i =   InteractionGroups.size();
			}else if (structMatrix[InteractionGroups[i][0]][1] == InteractionGroups[i][0]) 
			{
				bindingSingletonIndexOther = InteractionGroups[i][0];
				bindingSingletonSelfLinkOther = 1;
				i =  InteractionGroups.size();
			}
		}
	}
	if(bindingSingletonIndexOther > -1 && bindingSingletonSelfLinkOther > -1 && bindingSingletonIndexThis > -1 && bindingSingletonSelfLinkThis > -1)
	{	
		structMatrix[bindingSingletonIndexThis][bindingSingletonSelfLinkThis] = structMatrix[bindingSingletonIndexOther][bindingSingletonSelfLinkOther];
		structMatrix[bindingSingletonIndexOther][bindingSingletonSelfLinkOther] = bindingSingletonIndexThis;
		rbnSize = rbnSize + other->rbnSize;
		initPattern = std::vector<bool> (rbnSize, true );
		RecalcualteProperties();
		return true;
	}else
		return false;
	
}

//This is hacked together , wont work in general , bound group 1 and 2 are the groups involved in the just created bond , if you want to add
//more then 3 atoms together this will not work , i just couldnt be aresed so ugly stick. 
bool RBN::ThreeWayCombineWith(RBN other, int numberOfLinks)
{
	int oldStructSize = structMatrix.size();
	int oldIGSize = InteractionGroups.size();
	numberOfLinks = 4;
	for(int i=0; i < other.nodeList.size(); i++)
	{
		nodeList.push_back(other.nodeList[i]->clone()); // create copies of the nodes
	}

	for(int i = 0; i < other.structMatrix.size(); i++)
	{
		for(int j = 0; j < other.structMatrix[i].size(); j++)
		{
			other.structMatrix[i][j] = other.structMatrix[i][j] + rbnSize;
		}
		structMatrix.push_back(other.structMatrix[i]);
	}
	for(int i = 0; i < other.InteractionGroups.size(); i++)
	{
		for(int j = 0; j < other.InteractionGroups[i].size(); j++)
		{
			other.InteractionGroups[i][j] = other.InteractionGroups[i][j] + rbnSize;
		}
		InteractionGroups.push_back(other.InteractionGroups[i]);
	}
	int bindingGroupIndexThis1 = boundGroup1;
	int bindingGroupIndexThis2 = boundGroup2;
	int bindingGroupIndexOther = -1;

	for(int i=oldIGSize; i< InteractionGroups.size(); i ++)
	{
		
		if(InteractionGroups[i].size() >= numberOfLinks + 1 && i != boundGroup1 && i != boundGroup2)
		{
			bindingGroupIndexOther = i;
			i =  InteractionGroups.size();
		}
	}
	if(bindingGroupIndexOther > -1 && bindingGroupIndexThis1 > -1 && bindingGroupIndexThis2 > -1)
	{

		// A1 takes input from C1
		if (structMatrix[InteractionGroups[bindingGroupIndexThis1][1]][0] == InteractionGroups[bindingGroupIndexThis1][2])
		{
			
			structMatrix[InteractionGroups[bindingGroupIndexThis1][1]][0] = InteractionGroups[bindingGroupIndexOther][1];
		}else 
		{
			structMatrix[InteractionGroups[bindingGroupIndexThis1][1]][1] = InteractionGroups[bindingGroupIndexOther][1];
		}
		// c0 takes input from A2
		if (structMatrix[InteractionGroups[bindingGroupIndexOther][0]][0] == InteractionGroups[bindingGroupIndexOther][1])
		{
			
			structMatrix[InteractionGroups[bindingGroupIndexOther][0]][0] = InteractionGroups[bindingGroupIndexThis1][2];
		}else 
		{
			structMatrix[InteractionGroups[bindingGroupIndexOther][0]][1] = InteractionGroups[bindingGroupIndexThis1][2];
		}
		
		// B1 takes input from C2
		if (structMatrix[InteractionGroups[bindingGroupIndexThis2][1]][0] == InteractionGroups[bindingGroupIndexThis2][2])
		{
			
			structMatrix[InteractionGroups[bindingGroupIndexThis2][1]][0] = InteractionGroups[bindingGroupIndexOther][2];
		}else 
		{
			structMatrix[InteractionGroups[bindingGroupIndexThis2][1]][1] = InteractionGroups[bindingGroupIndexOther][2];
		}
		// c1 takes input from B2
		if (structMatrix[InteractionGroups[bindingGroupIndexOther][1]][0] == InteractionGroups[bindingGroupIndexOther][2])
		{
			
			structMatrix[InteractionGroups[bindingGroupIndexOther][1]][0] = InteractionGroups[bindingGroupIndexThis2][2];
		}else 
		{
			structMatrix[InteractionGroups[bindingGroupIndexOther][1]][1] = InteractionGroups[bindingGroupIndexThis2][2];
		}
		
		rbnSize = rbnSize + other.rbnSize;
		initPattern = std::vector<bool> (rbnSize, true );
		boundGroup1 = bindingGroupIndexThis1;
		boundGroup2 = bindingGroupIndexOther;
		RecalcualteProperties();
		return true;
	}else
		return false;
	
	
}

RBN::~RBN()
{
	for(int i =0; i< nodeList.size(); i++)
	{
		delete nodeList[i];
	}
}

int RBN::GetB()
{
	return b;
}

int RBN::Size()
{
	return rbnSize;
}

int RBN::GetCycleLengh()
{
	return cycleLength;
}

int RBN::GetTransiantLenght()
{
	return transiantLenght;
}

std::vector<Node*> RBN::GetNodePtrByIndex(std::vector<int> nodeIdx)
{
	std::vector<Node*> nodePtr;
	for(int i = 0; i < nodeIdx.size(); i++)
	{
		nodePtr.push_back(nodeList[nodeIdx[i]]);
	}
	return nodePtr;
}

std::vector<std::vector<Node*> > RBN::GetInteractionGroupsPtr()
{
	std::vector<Node*> interactionList;
	std::vector<std::vector<Node*>> interactionListSet;

	for(int i = 0; i < InteractionGroups.size(); i++)
	{
		for(int j = 0; j<InteractionGroups[i].size(); j++)
		{
			interactionList.push_back(nodeList[InteractionGroups[i][j]]);
		}
		interactionListSet.push_back(interactionList);
		interactionList.clear();
	}
	return interactionListSet;
}

std::vector<std::vector<int> > RBN::GetInteractionGroupsIntex()
{
	return InteractionGroups;
}

std::vector<bool> RBN::GetCurrentState()
{
	std::vector<bool> currentState;
	for(int i = 0;i < rbnSize; i++){
		currentState.push_back( nodeList[i]->GetState());
	}
	return currentState;
}

void RBN::GenerateInitValue()
{
	initPatternValue = 0;
	initPattern.resize(rbnSize);
	for(int i=0; i<rbnSize; i++)
	{
		initPattern[i] = rand()%2;
		if (initPattern[i]== 1){
			nodeList[i]->SetState(true) ;
			initPatternValue = initPatternValue + (1 << i);
		}else
			nodeList[i]->SetState(false) ;
		
	}

}

void RBN::GenerateNodes()
{
	
	for(int i = 0; i < rbnSize ; i++){
		nodeList.push_back( new Node(k) );
		
	}

	
	return ;
}

void RBN::GenerateNetworkTopology()
{

	GenerateInitConnections();
	//AddBondingNodes();
}


void RBN::GenerateInitConnections()
{
	std::vector<int> selectedInputs;
	selectedInputs.resize(k);
	std::map<int, int> influenceMap;

	for(int i =0; i< rbnSize; i++)
	{
		influenceMap.emplace(i, 0);
	}

	int rndNumber;
	for( int i = 0; i < rbnSize; i++)
	{
		
		for(int j=0; j<k; j++)
		{
			rndNumber = rand() % (rbnSize-1);
			selectedInputs[j] = rndNumber;
			for( int l=0; l<j; l++ )
			{
				if (selectedInputs[l] ==   rndNumber){
					l=j;
					j--;

				}
			}
		}
		for(int j = 0; j< selectedInputs.size(); j++)
		{
			influenceMap[selectedInputs[j]]++; // for each new input to a node increment the input node's influence 
			nodeList[i]->LinkNode(nodeList[selectedInputs[j]]);
		}
		structMatrix.push_back(selectedInputs);


		
	}
	nodeInfluence = influenceMap;
}
std::vector<bool> RBN::GetInitPattern()
{
	return initPattern;
}

void RBN::SetInitPattern()
{
	for(int i =0; i< (rbnSize) ; i++){
		nodeList[i]->SetState(initPattern[i]);
	}
}

void RBN::SetInitPattern(std::vector<bool> newinnit)
{
	initPattern = newinnit;
	SetInitPattern();
}

void RBN::RecalcualteProperties()
{
	CalculateCycleLenght();
	CalculateTransiant();
	CalculateLiveliness();
}

void RBN::AddBondingNodes()
{
	int rndNode, rndInput;
	for(int i = 0; i < b; i++)
	{
		rndNode = rand() % (rbnSize -1);
		rndInput = rand() % (k - 1);

		structMatrix[rndNode][rndInput] = rbnSize +i;
		nodeList[rbnSize+i]->LinkNode(nodeList[rndNode]);
		interfaceConnectionMap[rbnSize+i] = rndNode;

	}
}

void RBN::CalculateCycleLenght()
{
	std::vector<bool> hare, tortoise;

	int cycleCounter =1 ;
	int power =1;
	tortoise = initPattern;
	SetInitPattern();
	hare = TimeStep();
	
	while(tortoise != hare){
		if(power ==  cycleCounter){
			tortoise = hare;
			power = power*2;
			cycleCounter = 0;
		}
		hare = TimeStep();
		cycleCounter += 1;
	}
	
	cycleLength = cycleCounter;



}
void RBN::CalculateTransiant()
{

	std::vector<bool>  hare, tortoise;
	int mu =0;
	hare  = initPattern;
	tortoise = initPattern;
	SetInitPattern();
	for(int i = 0; i< cycleLength; i++)
	{
		hare = TimeStep();
	}
	
	while(tortoise != hare){
		
		SetState(tortoise);
		tortoise = TimeStep();
		SetState(hare);
		hare = TimeStep();
		mu++;
	}
	
	transiantLenght = mu;



}

void RBN::GenerateInteractionGroup(int maxGroupSize)
{
	//Get a working set of the structMatrix , which we can del elements from when we have added them to a group 
	std::vector< std::vector<int> > structList(structMatrix.begin(), structMatrix.end());
	std::vector<int> currentNode;
	
	std::vector<int> interactionGroup;

	int i = 0;
	int prevGroupSize = 0;
	int currentGroupSize = 0;
	int connectedNodeIterator = 0 ;
	int indexOfNext  = 0;

	

	while ( i < structList.size())
	{
		currentNode = structList[i];
		structList[i].clear();
		interactionGroup.push_back(i);
		currentGroupSize = 1;
		while(currentGroupSize < maxGroupSize)
		{
			prevGroupSize = currentGroupSize;
			for(connectedNodeIterator = 0; connectedNodeIterator < k; connectedNodeIterator++)
			{
				indexOfNext = currentNode[connectedNodeIterator];
				if( structList[indexOfNext].size() != 0 )
				{
					currentNode  = structList[indexOfNext];
					structList[indexOfNext].clear() ;
					interactionGroup.push_back(indexOfNext);
					currentGroupSize++;
					connectedNodeIterator = k;
				}
			}
			if(prevGroupSize == currentGroupSize)
			{
				currentGroupSize = maxGroupSize + 1;
			}
		}
		InteractionGroups.push_back(interactionGroup);
		interactionGroup.clear();
		while(i < structList.size() && structList[i].size() == 0 )
		{
			i++;
		}


	}


}

void RBN::GenerateInteractionGroupInfluence(int maxGroupSize, int minMaxOption)
{
	InteractionGroups.clear();
	//Get a working set of the structMatrix , which we can del elements from when we have added them to a group 
	std::map<int, int> nodeInfluenceCP(nodeInfluence.begin(), nodeInfluence.end());
	int currentNode;
	
	std::vector<int> interactionGroup;
	std::vector<int> currentNodeInputs;
	int i = 0;
	int prevGroupSize = 0;
	int currentGroupSize = 0;
	int connectedNodeIterator = 0 ;
	int indexOfNext  = 0;

	std::vector<pair<int, int>> influencePair;
	for (auto itr = nodeInfluenceCP.begin(); itr != nodeInfluenceCP.end(); ++itr)
		influencePair.push_back(*itr);
	if(minMaxOption == -1)
	{
		std::sort(influencePair.begin(), influencePair.end(), [=](pair<int, int>& a, pair<int, int>& b)
		{
			return a.second < b.second;
		}
		);
	}else
	{
		std::sort(influencePair.begin(), influencePair.end(), [=](pair<int, int>& a, pair<int, int>& b)
		{
			return a.second > b.second;
		}
		);
	}
	while ( influencePair.size() != 0) // while there are still nodes not assigned to an inteaction group
	{
		currentNode = influencePair[i].first; // current node is the node with the highest influence
		nodeInfluenceCP.erase(currentNode); // erase current node from the map of all node- influence pairs 
		interactionGroup.push_back(currentNode); // add current node to interactionGroup
		currentGroupSize = 1; // increment group size
		while(currentGroupSize < maxGroupSize) // while there is space in the interaction group
		{
			currentNodeInputs = structMatrix[currentNode]; // get the inputs to current node
			std::map<int, int>::iterator bestNextNode  = nodeInfluenceCP.end(); // set the best node found so far to none
			int largestInfluenceFound;
			if(!(minMaxOption == -1)) // if we are going largest first
				largestInfluenceFound = -1;
			else
				largestInfluenceFound = std::numeric_limits<int>::max(); // if we are going smallest first
			for(std::vector<int>::iterator it = currentNodeInputs.begin(); it != currentNodeInputs.end(); ++it)// for every input to current node
			{
				
				 
				std::map<int, int>::iterator nextNode  = nodeInfluenceCP.find(*it); // check if it's still in the node influence map 
				if(!(nextNode == nodeInfluenceCP.end())) // if it is still in the map
				{
					if((nextNode->second > largestInfluenceFound) && !(minMaxOption == -1)) // and if that input node has the highest influence found so far and we are looking higer first
					{
						bestNextNode = nextNode; // make it the best one found
						largestInfluenceFound = bestNextNode->second; // note the new highest influence found
					}

					if((nextNode->second < largestInfluenceFound) && (minMaxOption == -1)) // and if that input node has the lowest influence found so far and we are looking lower first
					{
						bestNextNode = nextNode; // make it the best one found
						largestInfluenceFound = bestNextNode->second; // note the new highest influence found
					}
				}
			}

			if(!(minMaxOption == -1)) // if we are going largest first
			{
				if(largestInfluenceFound != -1) // if we have found a sutable next node 
				{
					currentNode = bestNextNode->first; // current node becomes the found next best
					nodeInfluenceCP.erase(currentNode); // erase current node from the map of all node- influence pairs 
					interactionGroup.push_back(currentNode); // add current node to interactionGroup
					currentGroupSize ++ ; // increment group size
				}else // if we didn't find a sutable next node
				{
					currentGroupSize = maxGroupSize + 1; // we exit the while loop 
				}
			}
			if(minMaxOption == -1) // if we are going smallest first
			{
				if(largestInfluenceFound != std::numeric_limits<int>::max()) // if we have found a sutable next node 
				{
					currentNode = bestNextNode->first; // current node becomes the found next best
					nodeInfluenceCP.erase(currentNode); // erase current node from the map of all node- influence pairs 
					interactionGroup.push_back(currentNode); // add current node to interactionGroup
					currentGroupSize ++; // increment group size
				}else // if we didn't find a sutable next node
				{
					currentGroupSize = maxGroupSize + 1; // we exit the while loop 
				}
			}
		}
		InteractionGroups.push_back(interactionGroup); // created interaction group is added to the set 
		interactionGroup.clear();
		influencePair.clear(); // and reorganise the remaining nodes based on influence 
		for (auto itr = nodeInfluenceCP.begin(); itr != nodeInfluenceCP.end(); ++itr)
			influencePair.push_back(*itr);
		if(minMaxOption == -1)
		{
			std::sort(influencePair.begin(), influencePair.end(), [=](pair<int, int>& a, pair<int, int>& b)
			{
				return a.second < b.second;
			}
			);
		}else
		{
			std::sort(influencePair.begin(), influencePair.end(), [=](pair<int, int>& a, pair<int, int>& b)
			{
				return a.second > b.second;
			}
			);
		}
	}

	

}

void RBN::GenerateInteractionGroupLiveliness(int maxGroupSize, int minMaxOption)
{
	InteractionGroups.clear();
	//Get a working set of the structMatrix , which we can del elements from when we have added them to a group 
	std::map<int, int> nodeLiveCP(nodeLivelinessCycle0.begin(), nodeLivelinessCycle0.end());
	int currentNode;
	
	std::vector<int> interactionGroup;
	std::vector<int> currentNodeInputs;
	int i = 0;
	int prevGroupSize = 0;
	int currentGroupSize = 0;
	int connectedNodeIterator = 0 ;
	int indexOfNext  = 0;

	std::vector<pair<int, int>> livelinessPair;
	for (auto itr = nodeLiveCP.begin(); itr != nodeLiveCP.end(); ++itr)
		livelinessPair.push_back(*itr);
	if(minMaxOption == -1)
	{
		std::sort(livelinessPair.begin(), livelinessPair.end(), [=](pair<int, int>& a, pair<int, int>& b)
		{
			return a.second < b.second;
		}
		);
	}else
	{
		std::sort(livelinessPair.begin(), livelinessPair.end(), [=](pair<int, int>& a, pair<int, int>& b)
		{
			return a.second > b.second;
		}
		);
	}
	while ( livelinessPair.size() != 0) // while there are still nodes not assigned to an inteaction group
	{
		currentNode = livelinessPair[i].first; // current node is the node with the highest influence
		nodeLiveCP.erase(currentNode); // erase current node from the map of all node- influence pairs 
		interactionGroup.push_back(currentNode); // add current node to interactionGroup
		currentGroupSize = 1; // increment group size
		while(currentGroupSize < maxGroupSize) // while there is space in the interaction group
		{
			currentNodeInputs = structMatrix[currentNode]; // get the inputs to current node
			std::map<int, int>::iterator bestNextNode  = nodeLiveCP.end(); // set the best node found so far to none
			int largestLivelinessFound;
			if(!(minMaxOption == -1)) // if we are going largest first
				largestLivelinessFound = std::numeric_limits<int>::min();
			else
				 largestLivelinessFound = std::numeric_limits<int>::max(); // if we are going smallest first
			
			for(std::vector<int>::iterator it = currentNodeInputs.begin(); it != currentNodeInputs.end(); ++it)// for every input to current node
			{
				
				 
				std::map<int, int>::iterator nextNode  = nodeLiveCP.find(*it); // check if it's still in the node influence map 
				if(!(nextNode == nodeLiveCP.end())) // if it is still in the map
				{
					if((nextNode->second > largestLivelinessFound) && !(minMaxOption == -1)) // and if that input node has the highest influence found so far and we are looking higer first
					{
						bestNextNode = nextNode; // make it the best one found
						largestLivelinessFound = bestNextNode->second; // note the new highest influence found
					}

					if((nextNode->second < largestLivelinessFound) && (minMaxOption == -1)) // and if that input node has the lowest influence found so far and we are looking lower first
					{
						bestNextNode = nextNode; // make it the best one found
						largestLivelinessFound = bestNextNode->second; // note the new highest influence found
					}
				}
			}
			if(!(minMaxOption == -1)) // if we are going largest first
			{
				if(largestLivelinessFound != std::numeric_limits<int>::min()) // if we have found a sutable next node 
				{
					currentNode = bestNextNode->first; // current node becomes the found next best
					nodeLiveCP.erase(currentNode); // erase current node from the map of all node- influence pairs 
					interactionGroup.push_back(currentNode); // add current node to interactionGroup
					currentGroupSize = 1; // increment group size
				}else // if we didn't find a sutable next node
				{
					currentGroupSize = maxGroupSize + 1; // we exit the while loop 
				}
			}
			if(minMaxOption == -1) // if we are going smallest first
			{
				if(largestLivelinessFound != std::numeric_limits<int>::max()) // if we have found a sutable next node 
				{
					currentNode = bestNextNode->first; // current node becomes the found next best
					nodeLiveCP.erase(currentNode); // erase current node from the map of all node- influence pairs 
					interactionGroup.push_back(currentNode); // add current node to interactionGroup
					currentGroupSize = 1; // increment group size
				}else // if we didn't find a sutable next node
				{
					currentGroupSize = maxGroupSize + 1; // we exit the while loop 
				}
			}
		}
		InteractionGroups.push_back(interactionGroup); // created interaction group is added to the set 
		interactionGroup.clear();
		livelinessPair.clear(); // and reorganise the remaining nodes based on influence 
		for (auto itr = nodeLiveCP.begin(); itr != nodeLiveCP.end(); ++itr)
			livelinessPair.push_back(*itr);
		if(minMaxOption == -1)
		{
			std::sort(livelinessPair.begin(), livelinessPair.end(), [=](pair<int, int>& a, pair<int, int>& b)
			{
				return a.second < b.second;
			}
			);
		}else
		{
			std::sort(livelinessPair.begin(), livelinessPair.end(), [=](pair<int, int>& a, pair<int, int>& b)
			{
				return a.second > b.second;
			}
			);
		}
	}

	

}

int RBN::NumberOfBindableSingletons()
{
	int numberFound = 0;
	for(int i = 0; i < InteractionGroups.size(); i++)
	{
		if(InteractionGroups[i].size() == 1)
		{
			if((structMatrix[InteractionGroups[i][0]][0] == InteractionGroups[i][0]) || (structMatrix[InteractionGroups[i][0]][1] == InteractionGroups[i][0]) )
			{
				numberFound++;
			}
		}
	}
	return numberFound;
}
// Liveliness as just Number of 1 states in cycle OLD
//std::vector<std::map < int, int > > RBN::CalculateLiveliness()
//{
//	SetInitPattern();
//	std::vector<bool>  currentState ;
//	std::map<int, int> nlt;
//	std::map<int, int> nlc;
//	for (int i = 0; i< rbnSize; i++)
//	{
//		nlt.emplace(i, 0);
//		nlc.emplace(i, 0);
//		
//	}
//	for(int i = 0; i< transiantLenght; i++)
//	{
//		currentState = TimeStep();
//		for (int j = 0; j < currentState.size(); j++)
//		{
//			if(currentState[j] == true)
//			{
//				nlt[j]++;
//			}
//		}
//	}
//	for(int i = 0; i< cycleLength; i++)
//	{
//		currentState = TimeStep();
//		for (int j = 0; j < currentState.size(); j++)
//		{
//			if(currentState[j] == true)
//			{
//				nlc[j]++;
//			}
//		}
//	}
//
//	std::vector<std::map < int, int >> rbnLiveliness;
//	rbnLiveliness.push_back(nlt);
//	rbnLiveliness.push_back(nlc);
//	nodeLivelinessTrans = nlt;
//	nodeLivelinessCycle = nlc;
//	return rbnLiveliness;
//}

//Returns the overall Binding Condition for this particle
int RBN::GetBindingCondition()
{
	return bindingCondition;
}

//Resets the TEMPERATURE cycle and transient liveliness to 0
void RBN::ResetLivelinessCountersTemp()
{
    for (std::map<int,int>::iterator it= nodeLivelinessTransTemp.begin(); it!=nodeLivelinessTransTemp.end(); ++it)
    {
        it->second = 0;
    }
    for (std::map<int,int>::iterator it= nodeLivelinessCycleTemp.begin(); it!=nodeLivelinessCycleTemp.end(); ++it)
    {
        it->second = 0;
    }
}
//Resets the cycle and transient liveliness to 0
void RBN::ResetLivelinessCounters(bool initState)
{
	if(initState)
	{
	 for (std::map<int,int>::iterator it= nodeLivelinessTrans1.begin(); it!=nodeLivelinessTrans1.end(); ++it)
	 {
		 it->second = 0; 
	 }
	  for (std::map<int,int>::iterator it= nodeLivelinessCycle1.begin(); it!=nodeLivelinessCycle1.end(); ++it)
	 {
		 it->second = 0; 
	 }
	}else{
	 for (std::map<int,int>::iterator it= nodeLivelinessTrans0.begin(); it!=nodeLivelinessTrans0.end(); ++it)
	 {
		 it->second = 0; 
	 }
	  for (std::map<int,int>::iterator it= nodeLivelinessCycle0.begin(); it!=nodeLivelinessCycle0.end(); ++it)
	 {
		 it->second = 0; 
	 }
	}
}

void RBN::UpdateTransLivelinessCounterTemp()
{
	vector<bool> currentState = GetCurrentState();
	for (int j = 0; j < currentState.size(); j++)
	{
		if(currentState[j] == true)
		{
				nodeLivelinessTransTemp[j] = nodeLivelinessTransTemp[j] + 1;
		}else
		{
				nodeLivelinessTransTemp[j] = nodeLivelinessTransTemp[j] - 1;
		}
	}
}
//Increments or decrements the transient liveliness counter depending on current state
void RBN::UpdateTransLivelinessCounter(bool initState)
{
	vector<bool> currentState = GetCurrentState();
	for (int j = 0; j < currentState.size(); j++)
		{
			if(currentState[j] == true)
			{
				if(initState)
				{
					nodeLivelinessTrans1[j] = nodeLivelinessTrans1[j] + 1;
				}else
				{
					nodeLivelinessTrans0[j] = nodeLivelinessTrans0[j] + 1;
				}
			}else 
			{
				if(initState)
				{
					nodeLivelinessTrans1[j] = nodeLivelinessTrans1[j] - 1;
				}else
				{
					nodeLivelinessTrans0[j] = nodeLivelinessTrans0[j] - 1;
				}
			}
		}
}

void RBN::UpdateCycleLivelinessCounterTemp()
{
	vector<bool> currentState = GetCurrentState();
	for (int j = 0; j < currentState.size(); j++)
	{
		if(currentState[j] == true)
		{
				nodeLivelinessCycleTemp[j] = nodeLivelinessCycleTemp[j] + 1;
		}else
		{
				nodeLivelinessCycleTemp[j] = nodeLivelinessCycleTemp[j] - 1;
		}
	}

}
//Increments or decrements the  cycle liveliness counter depending on current state
void RBN::UpdateCycleLivelinessCounter(bool initState)
{
	vector<bool> currentState = GetCurrentState();
	for (int j = 0; j < currentState.size(); j++)
		{
			if(currentState[j] == true)
			{
				if(initState)
				{
					nodeLivelinessCycle1[j] = nodeLivelinessCycle1[j] + 1;
				}else
				{
					nodeLivelinessCycle0[j] = nodeLivelinessCycle0[j] + 1;
				}
			}else 
			{
				if(initState)
				{
					nodeLivelinessCycle1[j] = nodeLivelinessCycle1[j] - 1;
				}else
				{
					nodeLivelinessCycle0[j] = nodeLivelinessCycle0[j] - 1;
				}
			}
		}
	
}


int RBN::GetCycle1LivelinessTempPtr(int key)
{
	return nodeLivelinessCycleTemp[key];
}
int RBN::GetCycle1LivelinessPtr(int key)
{
	return nodeLivelinessCycle1[key];
}

int RBN::GetCycle0LivelinessPtr(int key)
{
	return nodeLivelinessCycle0[key];
}

//Liveliness liveliness with magnitude and directions (1) counted as (1), (0 )counted as (-1) 
std::vector<std::map < int, int > > RBN::CalculateLiveliness()
{
	SetInitPattern(std::vector<bool> (nodeList.size(), true ));
	std::vector<bool>  currentState ;
	std::map<int, int> nlt;
	std::map<int, int> nlc;
	for (int i = 0; i< rbnSize; i++)
	{
		nlt.emplace(i, 0);
		nlc.emplace(i, 0);
		
	}
	for(int i = 0; i< transiantLenght; i++)
	{
		currentState = TimeStep();
		for (int j = 0; j < currentState.size(); j++)
		{
			if(currentState[j] == true)
			{
				nlt[j]++;
			}else 
			{
				nlt[j]--;
			}
		}
	}
	this->bindingCondition = 0;
	for(int i = 0; i< cycleLength; i++)
	{
		currentState = TimeStep();
		for (int j = 0; j < currentState.size(); j++)
		{
			if(currentState[j] == true)
			{
				nlc[j]++;
				bindingCondition++;
			}else 
			{
				nlc[j]--;
				bindingCondition--;
			}
		}
	}

	std::vector<std::map < int, int >> rbnLiveliness;
	rbnLiveliness.push_back(nlt);
	rbnLiveliness.push_back(nlc);
	nodeLivelinessTrans0 = nlt;
	nodeLivelinessCycle0 = nlc;
	return rbnLiveliness;
}

void RBN::SetState(std::vector<bool> statePattern)
{
	for(int i= 0; i<rbnSize; i++){

		nodeList[i]->SetState(statePattern[i]);
		
	}
}

std::vector<bool> RBN::TimeStep()
{
	std::vector<bool> updatedState;

	for(int i= 0; i<rbnSize; i++){

		if (nodeList[i]->CalculateState()){
			
			updatedState.push_back(true);
		}else {
			updatedState.push_back(false);		
		}
		
	}

	for(int i= 0; i<rbnSize; i++){

		nodeList[i]->SetState(updatedState[i]);
		
	}
	return updatedState;
}

void RBN::SetUniqueID(int a)
{
	uniqueID =a;
}


std::vector<bool> RBN::CalculateStep()
{

	nextState.clear();	
	for(int i= 0; i<rbnSize; i++){

		if (nodeList[i]->CalculateState()){
			nextState.push_back(true);
		}else {
			nextState.push_back(false);		
		}
		
	}

	return nextState;

}

void RBN::Advance()
{
	for(int i= 0; i<rbnSize; i++){

		nodeList[i]->SetState(nextState[i]);
		
	}
}

int RBN::GetInputValue(std::vector<int> connectedNodes)
{
	int multiplier = k-1;
	int patternValue = 0;

	for(int i = 0 ; i<k; i++){
		if(nodeList[connectedNodes[i]]->GetState()){
			patternValue = patternValue + (1 << i);
		}
		
	}
	return patternValue;
}


void RBN::print_structMatrix()
{

	for( int i=0; i < rbnSize; i++)
	{
		for(int j=0; j<k; j++)
		{
			cout << structMatrix[i][j];
		}
		cout << endl;
	}

}


void RBN::print_ToFile(std::ofstream &outFile)
{
	
	
	std::vector<bool> lookup;
	for(int i = 0; i < nodeList.size(); i++)
	{
		lookup = nodeList[i]->GetLookup();
		for(int j = 0; j < lookup.size(); j++)
		{
			outFile << lookup[j];
		}
		outFile << endl;
	}

	for( int i=0; i < rbnSize; i++)
	{
		for(int j=0; j<k; j++)
		{
			outFile << structMatrix[i][j] << ',';
		}
		outFile << endl;
	}

	for( int i=0; i < InteractionGroups.size(); i++)
	{
		for(int j=0; j< InteractionGroups[i].size(); j++)
		{
			outFile << InteractionGroups[i][j] << ',';
		}
		outFile<< ';';
	}
	outFile << endl;


}