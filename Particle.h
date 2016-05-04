#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include "RBN.h"
#include "Bond.h"
#include "InteractionList.h"
class Particle
{
public:
	//takes a vector of creatant particles and the new bond formed between them
	Particle(std::vector<Particle*>, Bond* );
	Particle(std::vector<RBN*>, std::vector<Bond*>, std::vector<InteractionList*>);
	Particle(RBN*);
	Particle(const Particle& );
	Particle* clone() const ;
	// Returns an unbound IL of size int or larger, If none found returns empty vector
	InteractionList* GetFreeInteractionList(int);
	// Returns a random unbound IL of atleast size 2, If none found returns empty vector
	InteractionList* GetFreeInteractionList();
	std::vector<InteractionList*> GetAllFreeInteractionLists();
	std::vector<RBN*> GetComponentRBNs();
	std::vector<Bond*> GetExistingBonds();
	int GetParticleSize();
	//Calls all bonds to connect the relevent nodes into the compleate particle
	void BuildParticle();

	std::vector<Particle*> BreakBond(Bond*);
	std::vector<Particle*> BreakBonds(std::vector<Bond*>);
	void CalculateParticle();
	int CalculateCycleLength(bool);
	void CalculateTransiant(bool);
	void CalculateLiveliness(bool);
	std::vector<std::string> GetPrettyName();
	std::vector<std::string> GetPrettyStruct();
	std::string GetuID();
	void setuID(std::string);
	//Ever RBN takes one step along the cycle detection Algorithm
	int Step();
	// Every RBN updates current state to the stored next state
	void Sync();
	// Every RBN calculates what state it will have at the next time step
	std::vector<bool> CalculateNextState();
	// sets the initial state of all rbns to either all true or false 
	void SetInitState(bool);
	// sets the state of nodes in all RBNs to bool pattern, the first N values (where N is number of nodes in RBN) is the state of the nodes in the first RBN in Components, 
	// the first value in those N states is the state of the first node in the RBN Nodes list.
	void SetState(std::vector<bool>);
	std::vector<bool> GetCurrentState();
	void DeepDelete();
	 ~Particle(void){} ;
private:
	std::vector<RBN*> Components;
	std::vector<Bond*> Bonds;
	std::vector<InteractionList* > InteractionLists;
	std::string name;
	std::vector<bool> hare, tortoise;
	std::string uID;
	int power, cycleCounter, cycleLength0, transiantLenght0, cycleLength1, transiantLenght1;
};

