#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <bitset>
#include "RBN.h"
#include "Bond.h"
#include "InteractionList.h"
class Particle {
public:
	//takes a vector of creatant particles and the new bond formed between them
	Particle(std::vector<Particle *>, Bond *);

	Particle(std::vector<RBN *>, std::vector<Bond *>, std::vector<InteractionList *>);

	Particle(RBN *);

	Particle(const Particle &);

	Particle *clone() const;

	// Returns an unbound IL of size int or larger, If none found returns empty vector
	InteractionList *GetFreeInteractionList(int);

	// Returns a random unbound IL of atleast size 2, If none found returns empty vector
	InteractionList *GetFreeInteractionList();

	std::vector<InteractionList *> GetAllFreeInteractionLists();

	std::vector<InteractionList *> GetAllInteractionLists();

	std::vector<RBN *> GetComponentRBNs();

	std::vector<Bond *> GetExistingBonds();

	Bond* GetBondToBreak();

	void SetBondToBreak(Bond*);

	int GetParticleSize();

	//Calls all bonds to connect the relevent nodes into the compleate particle
	void BuildParticle();

	std::vector<Particle *> BreakBond(Bond *);

	std::vector<Particle *> BreakBonds(std::vector<Bond *>);

	void CalculateParticle();

	void CalculateParticleAtTemp(int);

	int CalculateCycleLength(bool);

	int CalculateCycleLengthAtTemp(int);

	void CalculateTransiant(bool);

	void CalculateTransiantAtTemp(int);

	void CalculateLiveliness(bool);

	void CalculateLivelinessAtTemp(int);

	std::vector<std::string> GetPrettyName();

	std::vector<std::string> GetPrettyStruct();

	std::string GetuID();

	void setuID(std::string);
	void SetReactorPos(int);
	int GetReactorPos();
	void SetDecompTimeAndPos(int , int);
	std::vector<int> GetDecompTimeAndPos();
	//Ever RBN takes one step along the cycle detection Algorithm
	int Step();

	// Every RBN updates current state to the stored next state
	void Sync();

	// Every RBN calculates what state it will have at the next time step
	std::vector<bool> CalculateNextState();

	// sets the initial state of all rbns to either all true or false
	void SetInitState(bool);

	// Uses temp to set inital state on an interaction list basis to the binary version of the number
	void SetTemp(int);

	// sets the state of nodes in all RBNs to bool pattern, the first N values (where N is number of nodes in RBN) is the state of the nodes in the first RBN in Components,
	// the first value in those N states is the state of the first node in the RBN Nodes list.
	void SetState(std::vector<bool>);

	std::vector<bool> GetCurrentState();

	void DeepDelete();

	// compares a section of structure from current lhs and rhs to next RBN with more then 2 bons
	bool CompareSection(RBN *lhs_current, RBN *rhs_current, std::list<RBN *> lhs_ComponentsToCheck,
						std::list<Bond *> lhs_BondsToCheck,
						std::list<RBN *> rhs_ComponentsToCheck, std::list<Bond *> rhs_BondsToCheck) const;

	bool Compare(RBN *lhs_root, std::vector<RBN *> lhs_ComponentsToCheck, std::vector<Bond *> lhs_BondsToCheck,
				 std::vector<RBN *> rhs_ComponentsToCheck, std::vector<Bond *> rhs_BondsToCheck,
				 const Particle *rhs) const;

	bool operator==(const Particle &rhs) const;

	~Particle(void) {};

private:
	std::vector<RBN *> Components;
	std::vector<Bond *> Bonds;
	std::vector<InteractionList *> InteractionLists;
	std::string name;
	std::vector<bool> hare, tortoise;
	std::string uID;
	Bond* bondToBreak;
    int nextDecomp, decompPos, reactorPos;
	int power, cycleCounter, cycleLength0, transiantLenght0, cycleLength1, transiantLenght1;
	int cycleLengthTemp, transiantLenghtTemp;

};