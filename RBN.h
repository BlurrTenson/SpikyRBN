#ifndef IG_RBN
#define IG_RBN

#include <stdlib.h>
#include <fstream>
#include "Node.h"
#include <vector>
#include <list>
#include <map>
#include <string>
/*
 * RBN defines a single RBN network
 *
 * The RBN is composed of a collection of Node instances with
 * a topology defining matrix structMatrix and a defined initial
 * state initPattern from which to calculate cycle length.
 */

class RBN
{
	
public:
	RBN(int , int, int);
	RBN(int , int , int  , std::vector<bool> , char);
	RBN(int , int , int  , std::vector<bool> );
	RBN(std::vector<std::string>);
	RBN(const RBN& );
	RBN* clone() const ;
	~RBN(void);
	void print_structMatrix();
	void print_ToFile(std::ofstream&);
	int GetB();
	int GetCycleLengh();
	int GetTransiantLenght();
	int GetBindingCondition();
	std::vector<std::vector<Node*> > GetInteractionGroupsPtr();
	std::vector<std::vector<int> > GetInteractionGroupsIntex();
	std::vector<Node*> GetNodePtrByIndex(std::vector<int>);

	//Resets the cycle and transient liveliness to 0
	void ResetLivelinessCounters(bool);
	//Increments or decrements the transient liveliness counter depending on current state
	void UpdateTransLivelinessCounter(bool);
	//Increments or decrements the  cycle liveliness counter depending on current state
	void UpdateCycleLivelinessCounter(bool);
	//Gets the calculated cycle liveliness for node with pointer Node*
	int GetCycle0LivelinessPtr(int);
	int GetCycle1LivelinessPtr(int);
	void SetRBNSymbol(char);
	char GetRBNSymbol();
	std::vector<bool> CalculateStep();
	std::vector<bool> GetCurrentState();
	void Advance();
	void RecalcualteProperties();
	void SetInitPattern();
	void SetInitPattern(std::vector<bool>);
	void SetState(std::vector<bool>);
	std::vector<bool> GetInitPattern();
	int Size();
	void CalculateCycleLenght();
	std::vector<std::map < int, int > > CalculateLiveliness();

////////////EXPERIMENTAL , TOO MUCH UGLY STICK/////////////////
	bool CombineWith(RBN, int);
	bool CombineLeastWith(RBN, int);
	bool CombineSingeltonsWith(RBN* );
	bool ThreeWayCombineWith(RBN, int);
	void GenerateInteractionGroupInfluence(int, int);
	void GenerateInteractionGroupLiveliness(int, int);
///////////////////////////////////////////////////////
	void SetUniqueID(int);
	int GetUniqueID();
	int NumberOfBindableSingletons();
	void ConstructRBN();
	void CalculateTransiant();
private:
	void GenerateNetworkTopology();
	void GenerateNodes();
	void GenerateInitConnections();
	void GenerateInitValue();
	void GenerateInteractionGroup(int); //Group the generated nodes together into "interaction groups" ie the spikes 
	void AddBondingNodes();


	std::vector<bool> TimeStep();

	int GetInputValue(std::vector<int>);

	int cycleLength, transiantLenght, bindingCondition, rbnSize, k, b, initPatternValue, boundGroup1, boundGroup2,boundGroup3, boundGroup4,boundGroup5, boundGroup6,boundGroup7, boundGroup8;
	std::vector<std::vector<int> > structMatrix;
	// A vector containing all Interaction Groups. Each interaction group is defined as a vector containing the index of member nodes in the nodeList 
	std::vector<std::vector<int> > InteractionGroups;
	std::vector<bool> initPattern, nextState;
	std::vector<Node*> nodeList;
	std::map<int, int> interfaceConnectionMap; // utility for the copy constructor.
	std::map<int, int> nodeInfluence;
	std::map<int, int> nodeLivelinessTrans0;
	std::map<int, int> nodeLivelinessCycle0;
	std::map<int, int> nodeLivelinessTrans1;
	std::map<int, int> nodeLivelinessCycle1;
	char symbol;
	int uniqueID;
};

#endif
