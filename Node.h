#ifndef IG_NODE
#define IG_NODE

#include <stdlib.h>
#include <string>
#include <vector>
/*
* Node defines an instance of a node in
* the RBN it hold the rule table for that node
* and the nodes current state.
*/


class Node
{
public:
	Node(int);
	Node(std::string);
	Node(const Node&);
	virtual Node* clone() const;
	int GetIndexOfInputFrom(Node*); 
	bool UpdateState(int);
	void SetState(bool);
	bool GetState();
	bool CalculateState(int);
	bool CalculateState();
	void LinkNode(Node*);
	void LinkNode(Node*, int);
	bool currentState;
	void RemoveInputs();
	std::vector<bool> GetLookup();
	std::vector<bool> lookupTable;
	std::vector<Node*> inputNodes;
};

#endif
