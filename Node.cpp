#include "Node.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iostream>

Node::Node(int numberOfInputs)
{
	
	int x = 1 << numberOfInputs;
	for(int i =0 ; i < x; i++)
	{
		if(rand()%2 == 1)
			lookupTable.push_back(true);
		else
			lookupTable.push_back(false);
	}

	if(rand()%2 == 1)
		currentState =true;
	else
		currentState = false;
}

Node::Node(std::string nodeDef)
{
    std::cout << nodeDef << "\n";
    int j;

    for(int i =0; i < nodeDef.size(); i++)
    {
        j = nodeDef[i] - '0';
        if (j == 0 )
            lookupTable.push_back(false);
        else
            lookupTable.push_back(true);
    }
    std::cout << "\n\n";
}

Node::Node(const Node& other)
{
	lookupTable = other.lookupTable;
}

Node* Node::clone() const
{
	return new Node(*this);
}
bool Node::CalculateState(int inputSum)
{
	return lookupTable[inputSum];
	
}

bool Node::CalculateState()
{
	int inputSum= 0;
	for(int i = 0 ; i<inputNodes.size(); i++){
		if(inputNodes[i]->GetState()){
			inputSum = inputSum + (1 << i);
		}
		
	}
	return lookupTable[inputSum];
	
}

bool Node::GetState()
{
	return currentState;
}

void Node::SetState(bool state){
	currentState = state;
}

int Node::GetIndexOfInputFrom(Node* n)
{
	int indexFound = -1;
	for(int i =0; i < inputNodes.size(); i++)
	{
		if(inputNodes[i] == n)
		{
			indexFound = i;
			i = inputNodes.size();
		}
	}
	return indexFound;
}

void Node::LinkNode(Node* n)
{
	inputNodes.push_back(n);
	return;
};

void Node::LinkNode(Node* n, int position)
{
	
	inputNodes[position] = n;
	return;
};

void Node::RemoveInputs()
{
	inputNodes.clear();
}

std::vector<bool> Node::GetLookup()
{
	return lookupTable;
}