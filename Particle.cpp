#include "Particle.h"
#include <algorithm>
#include <iostream> 
#include <map>

Particle::Particle(std::vector<Particle*> componentParticles, Bond* newBond )
{
	std::vector<RBN*> thisRBN;
	std::vector<Bond*> thisBond;
	for(int i =0; i<componentParticles.size(); i++)
	{
		thisRBN = componentParticles[i]->GetComponentRBNs();
		thisBond = componentParticles[i]->GetExistingBonds();
		Components.insert(Components.end(), thisRBN.begin(), thisRBN.end());
		Bonds.insert(Bonds.end(), thisBond.begin(),thisBond.end());
	}
	Bonds.push_back(newBond);
	
	
	std::vector<InteractionList*> ilInComponent;
	//for each RBN in this particle put that RBNs IL into the IL set for the particle 
	for(int i =0; i< componentParticles.size(); i++)
	{
		ilInComponent = componentParticles[i]->GetAllFreeInteractionLists();
		for(int j =0; j< ilInComponent.size(); j++)
		{
			if(!(newBond->ContainsInteractionList(ilInComponent[j])))
			{
				InteractionLists.push_back(ilInComponent[j]);
			}
		}
	}

	std::random_shuffle ( InteractionLists.begin(), InteractionLists.end() );
	
	//Get all IL involved in bonds
	uID = -1;

}

Particle::Particle(std::vector<RBN*> componentRBNs, std::vector<Bond*> componentBonds, std::vector<InteractionList*> componentInteractionLists)
{
	Components = componentRBNs;
	Bonds = componentBonds;
	InteractionLists = componentInteractionLists;
	std::random_shuffle ( InteractionLists.begin(), InteractionLists.end() );
	uID = -1;

}

Particle::Particle(RBN* atomicRBN )
{

	Components.push_back(atomicRBN);
	std::vector< std::vector <int> > ILIdx = atomicRBN->GetInteractionGroupsIntex();
	for(int itIL =0; itIL < ILIdx.size(); itIL++)
	{
		InteractionLists.push_back(new InteractionList(ILIdx[itIL], atomicRBN));
	}
	std::random_shuffle ( InteractionLists.begin(), InteractionLists.end() );
	uID = atomicRBN->GetUniqueID();
}

Particle::Particle(const Particle& other)
{
	//std::vector<RBN*> Components;
	std::map < RBN*, RBN* > rbnMapping;
	for(int i = 0; i < other.Components.size() ; i++)
	{
		Components.push_back(other.Components[i]->clone());
		rbnMapping.emplace( other.Components[i], Components[i]);
	}
	
	//std::vector<std::vector<Node*> > InteractionLists;
	for(int i = 0; i < other.InteractionLists.size() ; i++)
	{
		InteractionLists.push_back(other.InteractionLists[i]->clone(rbnMapping[other.InteractionLists[i]->GetParentRBN()]));
	}
	std::random_shuffle ( InteractionLists.begin(), InteractionLists.end() );
	//std::vector<Bond*> Bonds;
	for(int i =0; i < other.Bonds.size(); i++)
	{
		Bonds.push_back(other.Bonds[i]->clone(rbnMapping[other.Bonds[i]->GetParticipentA()], rbnMapping[other.Bonds[i]->GetParticipentB()]));
	}
	uID = other.uID;
	hare = other.hare;
	tortoise = other.tortoise;
	power = other.power;
	cycleCounter = other.cycleCounter;
}

Particle* Particle::clone() const
{
	return new Particle(*this);
}

std::vector<std::string> Particle::GetPrettyName()
{
	std::string row = "";
	std::vector<std::string> table;
	for(int i =0; i < Components.size(); i ++)
	{
		row += Components[i]->GetRBNSymbol();
		for(int j =0 ; j < Bonds.size(); j ++)
		{
			if(Bonds[j]->ContainsRBN(Components[i]))
			{
				row += Bonds[j]->GetOther(Components[i])->GetRBNSymbol();
			}
		
		}
		table.push_back(row);
		row = "";
	}
	return table;
}

std::string Particle::GetuID()
{
	return uID;
}

void Particle::setuID(std::string id)
{
	uID = id;
}

std::vector<std::string> Particle::GetPrettyStruct()
{
	std::string row = "";
	std::vector<std::string> table;
	std::vector<RBN*>::iterator it;
	for(int i =0; i < Components.size(); i ++)
	{
		row += Components[i]->GetRBNSymbol();
		row += std::to_string(i);
		for(int j =0 ; j < Bonds.size(); j ++)
		{
			if(Bonds[j]->ContainsRBN(Components[i]))
			{
				row += Bonds[j]->GetOther(Components[i])->GetRBNSymbol();
				it = find(Components.begin(), Components.end(), Bonds[j]->GetOther(Components[i]));
				if (it != Components.end())
					row += std::to_string(it - Components.begin());
			}
		
		}
		table.push_back(row);
		row = "";
	}
	return table;
}

int Particle::GetParticleSize()
{
	return Components.size();
}

InteractionList* Particle::GetFreeInteractionList(int minSize)
{
	for(int i =0; i < InteractionLists.size();i++)
	{
		if(InteractionLists[i]->size() >= minSize)
		{
			return InteractionLists[i];
		}		
	}
	return NULL;
}
std::vector<InteractionList*> Particle::GetAllFreeInteractionLists()
{
	return InteractionLists;
}

InteractionList* Particle::GetFreeInteractionList()
{
	for(int i =0; i < InteractionLists.size();i++)
	{
		if(InteractionLists[i]->size() >= 2)
		{
			return InteractionLists[i];
		}		
	}
	return NULL;
}

std::vector<RBN*> Particle::GetComponentRBNs()
{
	return Components;
}
std::vector<Bond*> Particle::GetExistingBonds()
{
	return Bonds;
}


void Particle::BuildParticle()
{
	for(int i =0; i < Bonds.size(); i++)
	{
		Bonds[i]->BuildBond();
	}
}

//TODO Incompleate 
std::vector<Particle*> Particle::BreakBond(Bond* bondPtr)
{
	
	bondPtr->BreakBond();
	
	std::vector<RBN*> lComponents;
	std::vector<Bond*> productBonds;
	std::vector<RBN*> productComponents;
	std::vector<RBN*> rComponents;
	std::vector<InteractionList*> productIL;
	std::vector<Particle*> resultParticles;
	RBN* Component; 
	int BondNumber;
	lComponents.push_back(bondPtr->GetParticipentA());
	rComponents.push_back(bondPtr->GetParticipentB());
	productIL.push_back(bondPtr->GetOriginalStructureA());
	//TODO: There is more code needed here , for each of lComp and rComp I need to find all other RBNs still bonded to them and group them , then build new Particles and return them.
	int itComponents =0;
	for(int i = 0; i< 2; i++)
	{
		while(!(0 == lComponents.size()))
		{
			Component = lComponents.back();
			lComponents.pop_back();
			
			for (int itBonds = 0 ; itBonds < Bonds.size(); itBonds++)
			{
				if ((Bonds[itBonds]->ContainsRBN(Component)) && (Bonds[itBonds] != bondPtr)) 
				{
					productBonds.push_back(Bonds[itBonds]);
					lComponents.push_back(Bonds[itBonds]->GetOther(Component));
					Bonds.erase(Bonds.begin()+ itBonds);
					itBonds--;
				}
			}
			productComponents.push_back(Component);
			for (int itIL = 0; itIL < InteractionLists.size(); itIL++)
			{
				if(InteractionLists[itIL]->GetParentRBN() == Component)
				{
					productIL.push_back(InteractionLists[itIL]);
					InteractionLists.erase(InteractionLists.begin()+ itIL);
					itIL --;
				}
			}

		}

		resultParticles.push_back(new Particle(productComponents, productBonds, productIL));
		productComponents.clear();
		productBonds.clear();
		productIL.clear();
		productIL.push_back(bondPtr->GetOriginalStructureB());
		lComponents = rComponents;
	}

	return   resultParticles;
}

std::vector<Particle*> Particle::BreakBonds(std::vector<Bond*> bondset)
{
	Bond* bondPtr;
	std::vector<Bond*> bondsToBreak;
	bondPtr = bondset.back();
	bondset.pop_back();
	bondPtr->BreakBond();
	
	std::vector<RBN*> lComponents;
	std::vector<Bond*> productBonds;
	std::vector<RBN*> productComponents;
	std::vector<RBN*> rComponents;
	std::vector<InteractionList*> productIL;
	std::vector<Particle*> resultParticles;
	std::vector<Particle*> stableSet;
	Particle* interimParticle;
	RBN* Component; 
	int BondNumber;
	lComponents.push_back(bondPtr->GetParticipentA());
	rComponents.push_back(bondPtr->GetParticipentB());
	productIL.push_back(bondPtr->GetOriginalStructureA());
	bondPtr->SetOriginalStructureANull();
	//TODO: There is more code needed here , for each of lComp and rComp I need to find all other RBNs still bonded to them and group them , then build new Particles and return them.
	int itComponents =0;
	for(int i = 0; i< 2; i++)
	{
		while(!(0 == lComponents.size()))
		{
			Component = lComponents.back();
			lComponents.pop_back();
			
			for (int itBonds = 0 ; itBonds < Bonds.size(); itBonds++)
			{
				if ((Bonds[itBonds]->ContainsRBN(Component)) && (Bonds[itBonds] != bondPtr)) 
				{
					for (int itBondsToBreak = 0 ; itBondsToBreak < bondset.size(); itBondsToBreak++)
					{
						//If the current bond is to be broken add it to the list of bonds to break to pass to the new product
						if ((bondset[itBondsToBreak]->ContainsRBN(Component))) 
						{
							bondsToBreak.push_back(bondset[itBondsToBreak]);
							bondset.erase(bondset.begin()+ itBondsToBreak );
						}

					}
					productBonds.push_back(Bonds[itBonds]);
					lComponents.push_back(Bonds[itBonds]->GetOther(Component));
					Bonds.erase(Bonds.begin()+ itBonds);
					itBonds--;
				}
			}
			productComponents.push_back(Component);
			for (int itIL = 0; itIL < InteractionLists.size(); itIL++)
			{
				if(InteractionLists[itIL]->GetParentRBN() == Component)
				{
					productIL.push_back(InteractionLists[itIL]);
					InteractionLists.erase(InteractionLists.begin()+ itIL);
					itIL --;
				}
			}

		}
		interimParticle = new Particle(productComponents, productBonds, productIL);
		if (bondsToBreak.size() > 0)
		{
			stableSet = interimParticle->BreakBonds(bondsToBreak);
			if(stableSet[0] != interimParticle)
			{
				delete interimParticle;
			}
			resultParticles.insert(resultParticles.end(), stableSet.begin(), stableSet.end());
		}else
		{
			resultParticles.push_back(interimParticle);
		}
		bondsToBreak.clear();
		productComponents.clear();
		productBonds.clear();
		productIL.clear();
		productIL.push_back(bondPtr->GetOriginalStructureB());
		bondPtr->SetOriginalStructureBNull();
		lComponents = rComponents;
	}

	


	return   resultParticles;
}


void Particle::CalculateParticle()
{
	for(int i =0; i< Bonds.size(); i++)
	{
		Bonds[i]->BuildBond();
	}
	power = 1;
	cycleCounter =1;
	CalculateCycleLength(true);
	CalculateTransiant(true);
	CalculateLiveliness(true);

	power = 1;
	cycleCounter =1;
	CalculateCycleLength(false);
	CalculateTransiant(false);
	CalculateLiveliness(false);
}

int Particle::CalculateCycleLength(bool initState)
{
	int cl1;
	SetInitState( initState );
	tortoise = GetCurrentState();
	hare = CalculateNextState();
	this->Sync();
	power=1;
	cycleCounter= 1;
	cl1 = this->Step();

	while( NULL == cl1 ) //while both step fucntions are returning NULL ie neither of them has found a cycle lenght
	{
		this->Sync();
		cl1 = this->Step();
	}
	if(initState)
	{
		cycleLength1 = cl1;
	}else
	{
		cycleLength0 = cl1;
	}
	return cl1;
}

void Particle::CalculateTransiant(bool initState)
{

	std::vector<bool>  hare, tortoise;
	int mu =0;
	SetInitState( initState );
	hare  = GetCurrentState();
	tortoise = GetCurrentState();
	int cl;
	if(initState)
	{
		 cl = cycleLength1;
	}else
	{
		 cl = cycleLength0;
	}
	for(int i = 0; i< cl; i++)
	{
		hare = CalculateNextState();
		Sync();
	}
	
	while(tortoise != hare){
		
		SetState(tortoise);
		tortoise = CalculateNextState();
		SetState(hare);
		hare = CalculateNextState();
		mu++;
	}
	if(initState)
	{
		 transiantLenght1 = mu;
	}else
	{
		 transiantLenght0 = mu;
	}
	
}

void Particle::CalculateLiveliness(bool initState)
{
	SetInitState( initState );
	std::vector<bool>  currentState ;
	std::map<int, int> nlt;
	std::map<int, int> nlc;
	int cl, tr;
	for (int i = 0; i< Components.size(); i++)
	{
		Components[i]->ResetLivelinessCounters(initState);
	}

	if(initState)
	{
		 cl = cycleLength1;
		 tr = transiantLenght1;
	}else
	{
		 cl = cycleLength0;
		 tr = transiantLenght0;
	}
	// Transient Liveliness
	for(int i = 0; i< tr; i++)
	{
		CalculateNextState();
		Sync();
		for (int j = 0; j< Components.size(); j++)
		{
			Components[j]->UpdateTransLivelinessCounter(initState);
		}
	}
	//Cycle Liveliness
	for(int i = 0; i< cl; i++)
	{
		CalculateNextState();
		Sync();
		for (int j = 0; j< Components.size(); j++)
		{
			Components[j]->UpdateCycleLivelinessCounter(initState);
		}
	}
	
	for (int i = 0; i < InteractionLists.size(); i++)
	{
		
			InteractionLists[i]->CalculateBindingProperty(initState);
	}

	for(int i = 0; i< Bonds.size(); i++)
	{
		
			Bonds[i]->CalculateBindingProperty(initState);
	}
}

void Particle::SetState( std::vector<bool> newState)
{
	int newStateIndex= 0;
	std::vector<bool> newSubState;
	for(int i = 0; i < Components.size(); i++)
	{

		for( int j = 0; j< Components[i]->Size() ; j++){
			newSubState.push_back(newState[j+newStateIndex]);
		}
		newStateIndex = newStateIndex+Components[i]->Size();
		Components[i]->SetState(newSubState);
		newSubState.clear();
	}
}

int Particle::Step()
{

	if(tortoise != hare){
		if(power ==  cycleCounter){
			tortoise = hare;
			power = power*2;
			cycleCounter = 0;
		}
		hare = this->CalculateNextState();
		cycleCounter += 1;
		return NULL;
	}else{
		this->CalculateNextState();
		return cycleCounter;
	};
}

void Particle::Sync()
{
	for(int i = 0; i < Components.size(); i++)
	{
		Components[i]->Advance();
	}
}

std::vector<bool> Particle::CalculateNextState()
{
	std::vector<bool> compositeState;
	std::vector<bool> tempVector;
	for(int i = 0; i < Components.size(); i++)
	{
		tempVector = Components[i]->CalculateStep();
		compositeState.insert(compositeState.end(), tempVector.begin(), tempVector.end());
	}
	return compositeState;
}

void Particle::SetInitState(bool initVal)
{
	for(int i = 0; i < Components.size(); i++)
	{
		Components[i]->SetState(std::vector<bool>(Components[i]->Size() , initVal ));
	}
}

std::vector<bool> Particle::GetCurrentState()
{
	std::vector<bool> currentState, partialState;
	for(int i = 0; i < Components.size(); i++)
	{
		partialState = Components[i]->GetCurrentState();
		currentState.insert(currentState.end(), partialState.begin(), partialState.end());
	}
	return currentState;
}

void Particle::DeepDelete(void)
{
	
	for(int i = 0; i< Bonds.size(); i++)
	{
		delete Bonds[i];
	}
	for(int i = 0; i< InteractionLists.size(); i++)
	{
		delete InteractionLists[i];
	}
	for(int i = 0; i< Components.size(); i++)
	{
		delete Components[i];
	}
}


