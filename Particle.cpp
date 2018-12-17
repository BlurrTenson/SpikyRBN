#include "Particle.h"
#include <algorithm>
#include <iostream> 
#include <map>
#include <set>

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
	bondToBreak = NULL;
    nextDecomp = NULL;
	decompPos = NULL;

}

Particle::Particle(std::vector<RBN*> componentRBNs, std::vector<Bond*> componentBonds, std::vector<InteractionList*> componentInteractionLists)
{
	Components = componentRBNs;
	Bonds = componentBonds;
	InteractionLists = componentInteractionLists;
	std::random_shuffle ( InteractionLists.begin(), InteractionLists.end() );
	uID = -1;

	nextDecomp = NULL;
	decompPos = NULL;
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

	nextDecomp = NULL;
	decompPos = NULL;
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

	nextDecomp = NULL;
	decompPos = NULL;
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

int Particle::GetReactorPos() {return reactorPos;}
void Particle::SetReactorPos(int r) {reactorPos = r;}
void Particle::SetDecompTimeAndPos(int time, int pos)
{
	nextDecomp = time;
	decompPos = pos;
	return;
}

std::vector<int> Particle::GetDecompTimeAndPos()
{
	std::vector<int> res;
	res.push_back(nextDecomp);
	res.push_back(decompPos);
	return res;
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

std::vector<InteractionList*> Particle::GetAllInteractionLists()
{
	std::vector<InteractionList*> ILs = InteractionLists;
	for(int i =0; i < Bonds.size(); i++)
	{
		ILs.push_back(Bonds[i]->GetOriginalStructureA());
		ILs.push_back(Bonds[i]->GetOriginalStructureB());
	}
	return ILs;
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


void Particle::CalculateParticleAtTemp(int temp)
{
	for(int i =0; i< Bonds.size(); i++)
	{
		Bonds[i]->BuildBond();
	}
	power = 1;
	cycleCounter =1;
	CalculateCycleLengthAtTemp(temp);
	CalculateTransiantAtTemp(temp);
	CalculateLivelinessAtTemp(temp);
}

void Particle::SetTemp(int temp)
{
	std::bitset<20>bitTemp(temp);
	std::vector<InteractionList*> ILs = GetAllInteractionLists();
	for(int i =0; i< ILs.size(); i++)
	{
		ILs[i]->SetInitialState(bitTemp);
	}
}
int Particle::CalculateCycleLengthAtTemp(int temp)
{
	int cl1;
	SetTemp(temp);
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
	cycleLengthTemp = cl1;
	return cl1;
}

void Particle::CalculateTransiantAtTemp(int temp)
{
	std::vector<bool>  hare, tortoise;
	int mu =0;
	SetTemp( temp );
	hare  = GetCurrentState();
	tortoise = GetCurrentState();
	int cl;
    cl = cycleLengthTemp;
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
    transiantLenghtTemp = mu;
}

void Particle::CalculateLivelinessAtTemp(int temp)
{
	SetTemp( temp );
	std::vector<bool>  currentState ;
	std::map<int, int> nlt;
	std::map<int, int> nlc;
	int cl, tr;
	for (int i = 0; i< Components.size(); i++)
	{
		Components[i]->ResetLivelinessCountersTemp();
	}

    cl = cycleLengthTemp;
    tr = transiantLenghtTemp;
	// Transient Liveliness
	for(int i = 0; i< tr; i++)
	{
		CalculateNextState();
		Sync();
		for (int j = 0; j< Components.size(); j++)
		{
			Components[j]->UpdateTransLivelinessCounterTemp();
		}
	}
	//Cycle Liveliness
	for(int i = 0; i< cl; i++)
	{
		CalculateNextState();
		Sync();
		for (int j = 0; j< Components.size(); j++)
		{
			Components[j]->UpdateCycleLivelinessCounterTemp();
		}
	}

	for (int i = 0; i < InteractionLists.size(); i++)
	{

		InteractionLists[i]->CalculateBindingPropertyTemp();
	}

	for(int i = 0; i< Bonds.size(); i++)
	{

		Bonds[i]->CalculateBindingPropertyTemp();
	}
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

Bond* Particle::GetBondToBreak()
{
	return bondToBreak;
}

void Particle::SetBondToBreak(Bond * b)
{
	bondToBreak = b;
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

bool Particle::operator==(const Particle &rhs) const{
    //particles must be of equal size
    if(this->Components.size() == rhs.Components.size())
    {
        std::multiset<char> thisSymbols, rhsSymbols;

        for( int i = 0; i < this->Components.size(); i++)
        {
            thisSymbols.insert(this->Components[i]->GetRBNSymbol());
            //std::cout << this->Components[i]->GetRBNSymbol() << std::endl;
        }
        for( int i = 0; i < rhs.Components.size(); i++)
        {
            rhsSymbols.insert(rhs.Components[i]->GetRBNSymbol());
            //std::cout << rhs.Components[i]->GetRBNSymbol() << std::endl;
        }


        // particles must contain the same type of atomic particles
        if(thisSymbols == rhsSymbols) {
            std::vector<RBN*> lhs_ComponentsToCheck = this->Components;
            std::vector<Bond*> lhs_BondsToCheck = this->Bonds;
            std::vector<RBN*> rhs_ComponentsToCheck = rhs.Components;
            std::vector<Bond*> rhs_BondsToCheck = rhs.Bonds;

            std::list<Bond*> lhs_BondsCopy(lhs_BondsToCheck.begin(), lhs_BondsToCheck.end());
            RBN* lhs_root = lhs_ComponentsToCheck[0];
            bool endfound = true;
            do {
                endfound = true;
                for (std::list<Bond *>::iterator ittrBond = lhs_BondsCopy.begin(); ittrBond != lhs_BondsCopy.end(); ++ittrBond) {
                    if ((*ittrBond)->ContainsRBN(lhs_root)) {
                        lhs_root = (*ittrBond)->GetOther(lhs_root);
                        lhs_BondsCopy.erase(ittrBond);
                        ittrBond = lhs_BondsCopy.end();
                        endfound = false;
                    }
                }
            }while (!endfound);


            return this->Compare(lhs_root, lhs_ComponentsToCheck, lhs_BondsToCheck, rhs_ComponentsToCheck, rhs_BondsToCheck, &rhs);
        } else {
            return false;
        }

    } else{
        return false;
    }

}

bool Particle::CompareSection(RBN* lhs_current, RBN* rhs_current, std::list<RBN*> lhs_ComponentsToCheck, std::list<Bond*> lhs_BondsToCheck,
                                                        std::list<RBN*> rhs_ComponentsToCheck, std::list<Bond*> rhs_BondsToCheck) const {
    std::vector<Bond*> lhs_Bonds;
    std::vector<Bond*> rhs_Bonds;
    std::vector<int> lhs_idx;
    std::vector<int> rhs_idx;
    //std::cout << "Hello from compare partial \n";
    //keep doing this till either you find a branch or there are no more bonds to check
    do {
        // get all bonds on lhs and rhs containing current nodes
        for (std::list<Bond *>::iterator ittrBond = lhs_BondsToCheck.begin();
             ittrBond != lhs_BondsToCheck.end(); ++ittrBond) {
            if ((*ittrBond)->ContainsRBN(lhs_current)) {
                lhs_Bonds.push_back((*ittrBond));
                ittrBond = lhs_BondsToCheck.erase(ittrBond);

            }
        }
        for (std::list<Bond *>::iterator ittrBond = rhs_BondsToCheck.begin();
             ittrBond != rhs_BondsToCheck.end(); ++ittrBond) {
            if ((*ittrBond)->ContainsRBN(rhs_current)) {
                rhs_Bonds.push_back((*ittrBond));
                ittrBond = rhs_BondsToCheck.erase(ittrBond);
            }
        }
        // both lhs and rhs nodes have to have the same number of bonds
        if (lhs_Bonds.size() != rhs_Bonds.size()) {
            return false;
        }

        if (lhs_Bonds.size() == 1) {
            //if we have only found 1 bond from current we check that the interaction lists are the same for lhs and rhs
            lhs_idx = lhs_Bonds[0]->GetILBelongingTo(lhs_current)->GetParticipentNodesIdx();
            rhs_idx = rhs_Bonds[0]->GetILBelongingTo(rhs_current)->GetParticipentNodesIdx();
            if (lhs_idx != rhs_idx) {
                return false;
            }
            // and update current to the other side of teh bond
            lhs_current = lhs_Bonds[0]->GetOther(lhs_current);
            rhs_current = rhs_Bonds[0]->GetOther(rhs_current);

            lhs_idx = lhs_Bonds[0]->GetILBelongingTo(lhs_current)->GetParticipentNodesIdx();
            rhs_idx = rhs_Bonds[0]->GetILBelongingTo(rhs_current)->GetParticipentNodesIdx();
            // check that the other side of the bond goes to the same interaction lists by index
            // and that the symbols are the same
            if (lhs_idx != rhs_idx || lhs_current->GetRBNSymbol() != rhs_current->GetRBNSymbol()) {
                return false;
            }
            lhs_Bonds.clear();
            rhs_Bonds.clear();
        }
        // if we have found no bonds then there is nothing else to match so return true (everything untill now matched)
        if (lhs_Bonds.size() == 0 && rhs_Bonds.size() == 0) {
            return true;
        }
        // if there is more then one bond to follow check all bonds are the same then call compare partial on each path

    }while(lhs_BondsToCheck.size() >0 && rhs_BondsToCheck.size() >0 && lhs_Bonds.size() <=1 && rhs_Bonds.size() <= 1);


    if(lhs_Bonds.size() > 1)
    {
        std::vector<RBN*> lhs_set;
        std::vector<RBN*> rhs_set;
        //Match pairs of bonds
        for(int i = 0; i < lhs_Bonds.size(); i++) {
            //get lhs interaction list index
            lhs_idx= lhs_Bonds[i]->GetILBelongingTo(lhs_current)->GetParticipentNodesIdx();
            //find a rhs interaction list that matches

            for(int j =0; j < rhs_Bonds.size(); j++)
            {
                rhs_idx= rhs_Bonds[j]->GetILBelongingTo(rhs_current)->GetParticipentNodesIdx();
                //if we find a match
                if(lhs_idx == rhs_idx) {
                    // update current to the other side of teh bond
                    RBN* lhs_possible = lhs_Bonds[i]->GetOther(lhs_current);
                    RBN* rhs_possible = rhs_Bonds[j]->GetOther(rhs_current);

                    lhs_idx= lhs_Bonds[i]->GetILBelongingTo(lhs_possible)->GetParticipentNodesIdx();
                    rhs_idx= rhs_Bonds[j]->GetILBelongingTo(rhs_possible)->GetParticipentNodesIdx();
                    // check that the other side of the bond goes to the same interaction lists by index
                    // and that the symbols are the same
                    if(lhs_idx == rhs_idx && lhs_possible->GetRBNSymbol() == rhs_possible->GetRBNSymbol()) {
                        //check that branch
                        lhs_set.push_back(lhs_possible);
                        rhs_set.push_back(rhs_possible);
                    } else
                    {
                        // if bond sources match but bond destinations don't then fail
                        return false;
                    }
                }
            }
        }
        // now the possible pairs have to equal number of bonds, if they do for each pair we call compare section,
        // if all return true then return true overall
        if(lhs_set.size() == lhs_Bonds.size() && rhs_set.size() == rhs_Bonds.size())
        {
            bool verdict = true;
            for (int i = 0; i < lhs_set.size(); i++) {
                verdict = verdict && CompareSection(lhs_set[i], rhs_set[i], lhs_ComponentsToCheck, lhs_BondsToCheck,
                               rhs_ComponentsToCheck, rhs_BondsToCheck);
            }
            return verdict;
        }else{
            return false;
        }
    }

    std::cout<< "Error program shouldn't get to here";

}

bool Particle::Compare( RBN* lhs_root, std::vector<RBN*> lhs_ComponentsToCheck, std::vector<Bond*> lhs_BondsToCheck,
                                       std::vector<RBN*>rhs_ComponentsToCheck, std::vector<Bond*> rhs_BondsToCheck, const Particle* rhs ) const {
    //std::cout << "Hello from Compare\n";
    std::vector<RBN *> rhs_possibleMatches;
    std::vector<Bond *> lhs_rootBonds;
    std::multiset<char> rhs_BondSymbols, lhs_BondSymbols;
    int rhs_bondNumber = 0;
    //get all bonds that involve lhs_root
    for (int i = 0; i < lhs_BondsToCheck.size(); i++) {
        if (lhs_BondsToCheck[i]->ContainsRBN(lhs_root)) {
            lhs_rootBonds.push_back(lhs_BondsToCheck[i]);
            lhs_BondSymbols.insert(lhs_BondsToCheck[i]->GetOther(lhs_root)->GetRBNSymbol());
        }
    }

    //find all instances of lhs_root in rhs
    for (int i = 0; i < rhs_ComponentsToCheck.size(); i++) {
        //first has to have the same symbol
        if (rhs_ComponentsToCheck[i]->GetRBNSymbol() == lhs_root->GetRBNSymbol()) {
            //find which bonds are involved in this instance
            rhs_bondNumber = 0;
            rhs_BondSymbols.clear();
            for (int j = 0; j < rhs_BondsToCheck.size(); j++) {
                if (rhs_BondsToCheck[j]->ContainsRBN(rhs_ComponentsToCheck[i])) {
                    rhs_BondSymbols.insert(rhs_BondsToCheck[j]->GetOther(rhs_ComponentsToCheck[i])->GetRBNSymbol());
                    rhs_bondNumber++;
                }
            }
            //check if there is an equal number of bonds and bonds go to the same symbols
            if ((rhs_bondNumber == lhs_rootBonds.size()) && (rhs_BondSymbols == lhs_BondSymbols)) {
                rhs_possibleMatches.push_back(
                        rhs_ComponentsToCheck[i]);// if there is add it to the list of possible matches
            }


        }
    }
    if (rhs_possibleMatches.size() != 0) {
        RBN* lhs_current = lhs_root;
        RBN* rhs_current;
        std::list<RBN*> lhs_CL(lhs_ComponentsToCheck.begin(), lhs_ComponentsToCheck.end());
        std::list<RBN*> rhs_CL(rhs_ComponentsToCheck.begin(), rhs_ComponentsToCheck.end());
        std::list<Bond*> lhs_BL(lhs_BondsToCheck.begin(), lhs_BondsToCheck.end());
        std::list<Bond*> rhs_BL(rhs_BondsToCheck.begin(), rhs_BondsToCheck.end());


        for (int i = 0; i < rhs_possibleMatches.size(); i++){
            rhs_current = rhs_possibleMatches[i];
            if (this->CompareSection(lhs_current, rhs_current, lhs_CL, lhs_BL, rhs_CL, rhs_BL))
            {
                return true;
            }
        }

    } else {
        return false;
    }
    return false;
}


