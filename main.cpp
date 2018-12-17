
#include <stdlib.h>
#include <iostream> 
#include <fstream>
#include "RBN.h"
#include "Node.h"
#include "Particle.h"
#include<sstream>
#include "Bond.h"
#include "InteractionList.h"
#include <string>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <time.h>

using namespace std;
//testing virtual folders

std::string concatNumbers(int first, int second)
{
	ostringstream sStream;
	sStream << first << ':';
	sStream << second;


	istringstream iStream(sStream.str());

	std::string out;

	iStream >> out;
	return out;

}
void LivelinessRBNRandInit()
{
	std::vector< std::map<int, int> > liveliness;
	RBN rbnTest = RBN(10, 3, 0);
	ofstream file1;
	file1.open("LivelinessRandInit10_3");
	for(int j = 0 ; j< 10000; j++)
	{
		liveliness = rbnTest.CalculateLiveliness();
		for(int i = 0 ; i < liveliness[0].size() ; i++ )
		{
			file1 << " , ";
			file1  << liveliness[0][i]  ;
			
		}

		file1 << " ; " ;

		for(int i = 0 ; i < liveliness[1].size() ; i++ )
		{
			file1 << " , ";
			file1 << liveliness[1][i]  ;
		}
		
		file1 << '\n';

		rbnTest = RBN(10, 3, 0);
		cout << "Test Number : " << j << "\n";
	}
	file1.close();
	file1.open("LivelinessRandInit20_3");
	rbnTest = RBN(20, 3, 0);
	for(int j = 0 ; j< 10000; j++)
	{
		liveliness = rbnTest.CalculateLiveliness();
		for(int i = 0 ; i < liveliness[0].size() ; i++ )
		{
			file1 << " , ";
			file1  << liveliness[0][i]  ;
			
		}

		file1 << " ; " ;

		for(int i = 0 ; i < liveliness[1].size() ; i++ )
		{
			file1 << " , ";
			file1 << liveliness[1][i]  ;
		}
		
		file1 << '\n';

		rbnTest = RBN(20, 3, 0);
		cout << "Test Number : " << j << "\n";
	}
	file1.close();
	file1.open("LivelinessRandInit30_3");
	rbnTest = RBN(30, 3, 0);
	for(int j = 0 ; j< 10000; j++)
	{
		liveliness = rbnTest.CalculateLiveliness();
		for(int i = 0 ; i < liveliness[0].size() ; i++ )
		{
			file1 << " , ";
			file1  << liveliness[0][i]  ;
			
		}

		file1 << " ; " ;

		for(int i = 0 ; i < liveliness[1].size() ; i++ )
		{
			file1 << " , ";
			file1 << liveliness[1][i]  ;
		}
		
		file1 << '\n';

		rbnTest = RBN(30, 3, 0);
		cout << "Test Number : " << j << "\n";
	}
}

void InteractionGroupLiveliness()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("GroupLivelinessOneInit12_Max_12");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	for(int k = 0; k < 10000; k++)
	{
		RBN* rbnTest = new RBN(12, 2, 12, InitOne);
		
		liveliness = rbnTest->CalculateLiveliness();
		cycleLiveliness = liveliness[1];
		interactionGroups = rbnTest->GetInteractionGroupsIntex();

	
		file1 << interactionGroups.size();
		file1 << ";";
		for(int i  = 0; i < interactionGroups.size(); i++)
		{
			for(int j = 0; j <12 ; j++)
			{
				if(j < interactionGroups[i].size())
				{
				file1 << cycleLiveliness[interactionGroups[i][j]];
				file1 << ",";
				}else 
				{
					file1 << "A,";
				}
			}
		
			file1 << ";";
		}
		file1 << "\n";
		cout << "Test Number : " << k << "\n";
	}
	file1.close();
	return;
}

void InteractionGroupBindLiveliness()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("BoundLeast_1_GroupLivelinessOneInit12_2NEW");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	int fails  = 0 ;
	for(int k = 0; k < 5000; k++)
	{
		RBN rbnA = RBN(12, 2, 4, InitOne);
		RBN rbnB = RBN(12, 2, 4, InitOne);
		if (rbnA.CombineLeastWith(rbnB, 1) )
		{
			liveliness = rbnA.CalculateLiveliness();
			cycleLiveliness = liveliness[1];
			interactionGroups = rbnA.GetInteractionGroupsIntex();
			cout << "Success \n";

			file1 << interactionGroups.size();
			file1 << ";";
			for(int i  = 0; i < interactionGroups.size(); i++)
			{
				for(int j = 0; j <4 ; j++)
				{
					if(j < interactionGroups[i].size())
					{
					file1 << cycleLiveliness[interactionGroups[i][j]];
					file1 << ",";
					}else 
					{
						file1 << "A,";
					}
				}
		
				file1 << ";";
			}
			file1 << "\n";
			cout << "Test Number : " << k << "\n";
		}
		else
			fails ++;
	}
	file1 << "Number Failed " << fails;
	file1.close();
}

void InteractionGroupBind3Liveliness()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("Bound3_1Pair_GroupLivelinessOneInit12_2NEW");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	int fails  = 0 ;
	for(int k = 0; k < 3333; k++)
	{
		RBN rbnA = RBN(12, 2, 5, InitOne);
		RBN rbnB = RBN(12, 2, 5, InitOne);
		RBN rbnC = RBN(12, 2, 5, InitOne);
		if (rbnA.CombineWith(rbnB, 1) )
		{
			if (rbnA.ThreeWayCombineWith(rbnC, 2) ){
				liveliness = rbnA.CalculateLiveliness();
				cycleLiveliness = liveliness[1];
				interactionGroups = rbnA.GetInteractionGroupsIntex();
				cout << "Success \n";

				file1 << interactionGroups.size();
				file1 << ";";
				for(int i  = 0; i < interactionGroups.size(); i++)
				{
					for(int j = 0; j <5 ; j++)
					{
						if(j < interactionGroups[i].size())
						{
						file1 << cycleLiveliness[interactionGroups[i][j]];
						file1 << ",";
						}else 
						{
							file1 << "A,";
						}
					}
		
					file1 << ";";
				}
				file1 << "\n";
				cout << "Test Number : " << k << "\n";
				}
			else
				fails ++;
		}
		else
			fails ++;
	}
	file1 << "Number Failed " << fails;
	file1.close();
}
void InteractionGroupBindNLiveliness()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("Bound5_1_GroupLivelinessOneInit12_2");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	int fails  = 0 ;
	for(int k = 0; k < 3333; k++)
	{
		RBN rbnA = RBN(12, 2, 5, InitOne);
		RBN rbnB = RBN(12, 2, 5, InitOne);
		RBN rbnC = RBN(12, 2, 5, InitOne);
		RBN rbnD = RBN(12, 2, 5, InitOne);
		RBN rbnE = RBN(12, 2, 5, InitOne);
		if (rbnA.CombineWith(rbnB, 1) )
		{
			if (rbnA.CombineWith(rbnC, 1) ){
				if (rbnA.CombineWith(rbnD, 1) ){
					if (rbnA.CombineWith(rbnE, 1) ){
						liveliness = rbnA.CalculateLiveliness();
						cycleLiveliness = liveliness[1];
						interactionGroups = rbnA.GetInteractionGroupsIntex();
						cout << "Success \n";

						file1 << interactionGroups.size();
						file1 << ";";
						for(int i  = 0; i < interactionGroups.size(); i++)
						{
							for(int j = 0; j <5 ; j++)
							{
								if(j < interactionGroups[i].size())
								{
								file1 << cycleLiveliness[interactionGroups[i][j]];
								file1 << ",";
								}else 
								{
									file1 << "A,";
								}
							}
		
							file1 << ";";
						}
						file1 << "\n";
						cout << "Test Number : " << k << "\n";
				
					}
					else
					fails ++;
				}
				else
					fails ++;
			}
			else
				fails ++;
		}
		else
			fails ++;
	}
	file1 << "Number Failed " << fails;
	cout << "Number Failed " << fails;
	file1.close();
}

void InteractionGroupMaxSizePossible()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("LargestInteractionListMax_12_LeastLive");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	int largestSize = 0;
	vector<int>* largestVector = 0;
	for(int k = 0; k < 10000; k++)
	{
		RBN *rbnTest = new RBN(12, 2, 12, InitOne);
		//rbnTest->GenerateInteractionGroupInfluence(12, -1);
		rbnTest->GenerateInteractionGroupLiveliness(12, -1);
		liveliness = rbnTest->CalculateLiveliness();
		cycleLiveliness = liveliness[1];
		interactionGroups = rbnTest->GetInteractionGroupsIntex();

		largestSize = 0;
		largestVector = 0;
		for( int i=0; i<interactionGroups.size(); ++i) {
			if(interactionGroups[i].size() > largestSize) {
				largestSize = interactionGroups[i].size();
				largestVector = &interactionGroups[i];
			}
		}
		
		file1 << interactionGroups.size();
		file1 << ",";
		file1 << largestVector->size();
		file1 << ";";
		file1 << "\n";
		cout << "Test Number : " << k << "\n";
	}
	file1.close();
	return;
}

void NumberOfBindableSingletons()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("NumberOfNaturalyOccuringSingletons_MostInf");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	int numberSingletonsFound  = 0 ;
	for(int k = 0; k < 10000; k++)
	{
		RBN *rbnA = new RBN(12, 2, 4, InitOne);
		rbnA->GenerateInteractionGroupInfluence(4, 1);
		numberSingletonsFound = rbnA->NumberOfBindableSingletons();
		file1 << numberSingletonsFound << "\n";
		cout << numberSingletonsFound << "\n";
		numberSingletonsFound = 0;
		
	}
	
	file1.close();
}


void InteractionGroupBindSingleton()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("SingeltonBind");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	int numberSingletonsFound  = 0 ;
	RBN *rbnA ;
	RBN *rbnB ;
	for(int k = 0; k < 5000; k++)
	{
		do{  rbnA = new RBN(12, 2, 4, InitOne);
			numberSingletonsFound = rbnA->NumberOfBindableSingletons();
		}while(numberSingletonsFound < 1 );

		numberSingletonsFound = 0;

		do{  rbnB = new RBN(12, 2, 4, InitOne);
			numberSingletonsFound = rbnB->NumberOfBindableSingletons();
		}while(numberSingletonsFound < 1 );

		if (rbnA->CombineSingeltonsWith(rbnB) )
		{
			liveliness = rbnA->CalculateLiveliness();
			cycleLiveliness = liveliness[1];
			interactionGroups = rbnA->GetInteractionGroupsIntex();
			std::cout << "Success \n";

			file1 << interactionGroups.size();
			file1 << ";";
			for(int i  = 0; i < interactionGroups.size(); i++)
			{
				for(int j = 0; j <4 ; j++)
				{
					if(j < interactionGroups[i].size())
					{
					file1 << cycleLiveliness[interactionGroups[i][j]];
					file1 << ",";
					}else 
					{
						file1 << "A,";
					}
				}
		
				file1 << ";";
			}
			file1 << "\n";
			std::cout << "Test Number : " << k << "\n";
		}
		
			
	}
	
	file1.close();
}

void InteractionGroupLiveliness_NewBindingProp()
{
	srand(14);
	std::vector<bool> InitOne (12, true );
	ofstream file1;
	file1.open("NewBindingProp12_Max_12_LeastLive");
	std::vector< std::map<int, int> > liveliness;
	std::vector< std::vector<int> > interactionGroups;
	std::map<int, int> cycleLiveliness;
	for(int k = 0; k < 10000; k++)
	{
		RBN* rbnTest = new RBN(12, 2, 12, InitOne);
		
		liveliness = rbnTest->CalculateLiveliness();
		cycleLiveliness = liveliness[1];
		
		//rbnTest->GenerateInteractionGroupInfluence(12, -1);
		rbnTest->GenerateInteractionGroupLiveliness(12, -1);
		interactionGroups = rbnTest->GetInteractionGroupsIntex();
		file1 << interactionGroups.size();
		file1 << ";";
		for(int i  = 0; i < interactionGroups.size(); i++)
		{
			for(int j = 0; j <12 ; j++)
			{
				if(j < interactionGroups[i].size())
				{
				file1 << cycleLiveliness[interactionGroups[i][j]];
				file1 << ",";
				}else 
				{
					file1 << "A,";
				}
			}
		
			file1 << ";";
		}
		file1 << "\n";
		cout << "Test Number : " << k << "\n";
	}
	file1.close();
	return;
}

void ExpOnePartialBP()
// Binding probability is a function of the Interaction Lists involved in binding
{

}

void ExpOneTotalBP()
// Binding probability is a funciton of the Total Binding Property of the involved particles 
{
}

void ExpOneNoSC()
//  No stability condition is used. 
{

}

std::vector<int> ParticleTests()
{
	srand(16);
	std::vector<bool> InitOne (12, true );
	std::vector<int> clList;
	for(int i = 0; i < 10000; i++)
	{
		RBN* rbnTestA = new RBN(12, 2, 12, InitOne);
		RBN* rbnTestB = new RBN(12, 2, 12, InitOne);
		InteractionList* ilA;
		InteractionList* ilB;
		std::vector<Particle*> particlesInvolved;
	
		Bond* testBond;

		Particle* testParticleA = new Particle(rbnTestA);
		Particle* testParticleB = new Particle(rbnTestB);

		ilA = testParticleA->GetFreeInteractionList(4);
		ilB = testParticleB->GetFreeInteractionList(4);
		if(!(ilA == NULL || ilB == NULL))
		{		
			testBond = new Bond(ilA, ilB, rbnTestA, rbnTestB);
		
			particlesInvolved.push_back(testParticleA);
			particlesInvolved.push_back(testParticleB);

			Particle* testParticleAB = new Particle(particlesInvolved, testBond);

			testParticleAB->BuildParticle();

			clList.push_back(testParticleAB->CalculateCycleLength(true)) ;
		}
	}
	return clList;
	
	
}
std::vector<int> OldTestCL()
{
	srand(16);
	std::vector<int> clList;
	std::vector<bool> InitOne (12, true );
	for(int i = 0; i < 10000; i++)
	{
		RBN* rbnA = new RBN(12, 2, 4, InitOne);
		RBN* rbnB = new RBN(12, 2, 4, InitOne);
		if(rbnA->CombineWith(*rbnB, 3))
		{
			rbnA->CalculateCycleLenght();
			clList.push_back(rbnA->GetCycleLengh() );

		}else {
			
		}
	}
	return clList;
}		

void TestingBindingProp()
{
	srand(668431); //14, 34357, 8267209, 668431
	std::vector<bool> InitOne (12, true );
	ofstream fileCC;
	ofstream fileSC;
	ofstream filePF;
	ofstream filePB;
	ofstream fileF;
	ofstream fileSize;
	fileCC.open("BM4_CC");
	fileSC.open("BM4_SC");
	filePF.open("BM4_PForward");
	filePB.open("BM4_PBack");
	fileF.open("BM4_Fail");
	fileSize.open("BM4_Sizes");
	Particle* particleA;
	Particle* particleB;
	Particle* particleAB;
	InteractionList* ilAc;
	InteractionList* ilBc;
	std::vector<Particle*> Reactor;
	std::vector<Particle*> involvedParticles;
	std::vector<Particle*> genResults;
	RBN* rbnA;
	Bond* possibleBond;
	char name = 'A';
	int Aidx, Bidx;
	int CC , ProbForward, ProbBack , SC, possibleSwaps, numberToSwap, PBP0A, PBP0B, PBP0AB, PBP1A, PBP1B, PBP1AB, fail;
	for(int i =0; i< 28; i++)
	{
		rbnA = new RBN(12, 2, 12, InitOne, (name + i));
		Reactor.push_back(new Particle(rbnA));
	}
	fail = 0;
	for(int generation = 0; generation< 50; generation++)
	{
		while(genResults.size() <= 20)
		{
			involvedParticles.clear();
			Aidx = rand() % Reactor.size();
			Bidx = rand() % Reactor.size();

			particleA = Reactor[Aidx]->clone();
			particleB = Reactor[Bidx]->clone();

			particleA->CalculateParticle();
			particleB->CalculateParticle();

			ilAc = particleA->GetFreeInteractionList();
			ilBc = particleB->GetFreeInteractionList();
			if(ilAc != NULL && ilBc != NULL)
			{
				// Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
				CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
				PBP0A = abs(ilAc->GetBindingProperty(false));
				PBP0B = abs(ilBc->GetBindingProperty(false));
				PBP1A = abs(ilAc->GetBindingProperty(true));
				PBP1B = abs(ilBc->GetBindingProperty(true));
				//cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
				//cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
				if(ilAc->GetNumberOfBondingEdges() > ilBc->GetNumberOfBondingEdges())
				{
					possibleSwaps = ilBc->GetNumberOfBondingEdges();
				}else
				{
					possibleSwaps = ilAc->GetNumberOfBondingEdges();
				}
				//If Possible swaps - Collision Criterion < 0 then no reaction can happen  
				if((possibleSwaps - abs(CC)) > 0 )
				{

					//Otherwise Possible Swaps - collision Criterion = Number to swap
					numberToSwap = possibleSwaps - abs(CC);
					// Create a bond which makes NumberToSwap swaps between ilA and ilB
					possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN());
				
					involvedParticles.push_back(particleA);
					involvedParticles.push_back(particleB);

					// Create new composit particle
					particleAB = new Particle(involvedParticles, possibleBond);
				
					// Calculate new particle
					particleAB->CalculateParticle();

					// Calculate Stability Criterion PBP0(A') + PBP0(B')
					SC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);

					PBP0AB = abs(ilAc->GetBindingProperty(false))+ abs(ilBc->GetBindingProperty(false));
					PBP1AB = abs(ilAc->GetBindingProperty(true))+ abs(ilBc->GetBindingProperty(true));

					//Calculate Forward and Backward Binding Probability 
					//cout << "0AB : " << PBP0AB << " 1AB : " << PBP1AB << "\n \n";
					ProbForward = (PBP1A + PBP1B + PBP1AB) - (PBP0A + PBP0B);
					ProbBack = (PBP1A + PBP1B + PBP1AB) - PBP0AB;

					//Add to reactor
					genResults.push_back(particleAB);
					fileCC << CC << ",";
					fileSC<< SC << ",";
					filePF<< ProbForward << ",";
					filePB<< ProbBack << ",";
					fileSize << particleAB->GetParticleSize() << ",";
				
				}else
				{
					fail++;
					delete particleA;
					delete particleB;
					delete ilAc;
					delete ilBc;
				}
			}
		}
		fileCC <<"\n";
		fileSC<< "\n";
		filePF<< "\n";
		filePB<< "\n";
		fileF<< fail << "\n";
		fileSize<< "\n";
		fail = 0;
		Reactor.insert(Reactor.end(), genResults.begin(), genResults.end() );
		genResults.clear();
		cout << "Generation "<< generation <<" Done \n";
	}
	cout << "Exp Done \n";
	cin.get();

}

std::vector<Particle*> CheckStability(Particle* particleAB)
{
	// Calculate new particle
	particleAB->CalculateParticle();
	std::vector<Bond*> currentBonds;
	std::vector<Bond*> BondsToBreak;
	std::vector<Particle*> productParticles;
	std::vector<Particle*> newProductParticles;
	std::vector<Particle*> partialProduct;
	currentBonds = particleAB->GetExistingBonds();
	for(int i = 0; i < currentBonds.size(); i++ )
	{
		if ((currentBonds[i]->GetBindingPropertyA(false) + currentBonds[i]->GetBindingPropertyB(false)) != 0)
		{
			BondsToBreak.push_back(currentBonds[i]);
		}
	}

	if (BondsToBreak.size() == 0)
	{
		productParticles.push_back(particleAB);
		return productParticles;
	}else
	{
		productParticles = particleAB->BreakBonds(BondsToBreak); //new Particleptr

		delete particleAB;

		for(int i = 0; i < productParticles.size(); i++ )
		{

			partialProduct = CheckStability(productParticles[i]);
			newProductParticles.insert(newProductParticles.end(), partialProduct.begin(), partialProduct.end());
		}
		for(int i = 0; i < BondsToBreak.size(); i++)
		{
			delete BondsToBreak[i];
			BondsToBreak[i] = NULL;
		}
		return newProductParticles;
	}

}
int TempStability(Particle* particleAB) {
	// Calculate new particle
	particleAB->CalculateParticle();
	std::vector<Bond *> currentBonds;
	Bond *BondsToBreak;
	std::vector<Particle *> productParticles;
	std::vector<Particle *> newProductParticles;
	std::vector<Particle *> partialProduct;
	currentBonds = particleAB->GetExistingBonds();
	std::pair<int, Particle*> breakPair;
	int tauEarlest, current, bondsToBreakCount;
	tauEarlest = 100000;
    current = 100000;
	float totalBondSize, CC_AB, CC_B, numberOverA, numberOverB, prob, currentF ;

    bondsToBreakCount = 0;
	//Check each bond against stability condition
	for (int i = 0; i < currentBonds.size(); i++) {
		if ((currentBonds[i]->GetBindingPropertyTempA() + currentBonds[i]->GetBindingPropertyTempB()) != 0) {
			totalBondSize = ((float) currentBonds[i]->GetOriginalStructureA()->GetParticipentNodesIdx().size()
							 + (float) currentBonds[i]->GetOriginalStructureB()->GetParticipentNodesIdx().size());
			CC_AB = currentBonds[i]->GetBindingPropertyTempA() + currentBonds[i]->GetBindingPropertyTempB();
			CC_AB = CC_AB / totalBondSize;
			numberOverA = currentBonds[i]->GetOriginalStructureA()->GetNumberNodesWithLivelinessOver(CC_AB);
			numberOverB = currentBonds[i]->GetOriginalStructureB()->GetNumberNodesWithLivelinessOver(CC_AB);
			prob = (numberOverA + numberOverB) / totalBondSize;
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			currentF = (1/prob)* log(1/r);
			//cout << currentF << endl;
			if(isinf( (1/prob)* log(1/r)) == 0){
				current = (int) currentF* 10 ; // togive particles a little more life
				//cout << current << endl;
				if (tauEarlest > current) {
					tauEarlest = current;
					BondsToBreak = (currentBonds[i]);
					bondsToBreakCount++;
				}
			}
		}
	}
   	if (bondsToBreakCount == 0){
		particleAB->SetBondToBreak(NULL);
		return -1;
	}else{
		particleAB->SetBondToBreak(BondsToBreak);

		return tauEarlest;
	}
}
std::vector<Particle*> BreakUnstable(Particle* BondsToBreak){
	//cout << "breaking unstable" << endl;
	std::vector<Bond*> breakList;
	std::vector<Particle*> productParticles, returnParticles;
    //If there are bonds to break , figure out which bond needs to be broken
    breakList.push_back(BondsToBreak->GetBondToBreak());
    productParticles = BondsToBreak->BreakBonds(breakList); //new Particleptr
	for(int i = 0; i < breakList.size(); i++)
		{
			delete BondsToBreak[i].GetBondToBreak();
		}
    return productParticles;
}


std::vector<float> ReactorInstance(std::vector<Particle*> Reac, int reacNumber)
{
	 //14, 34357, 8267209, 668431
	std::vector<Particle*> Reactor = Reac;
	Reactor.reserve(2000);
	std::vector<bool> InitOne (12, true );
	ofstream file;
	Particle* particleA;
	Particle* particleB;
	Particle* particleAB;
	InteractionList* ilAc;
	InteractionList* ilBc;
	std::vector<Particle*> involvedParticles;
	std::vector<Particle*> productParticles;
	std::vector<Particle*> genResults;
	std::vector<Bond*> currentBonds;
	std::vector<Bond*> BondsToBreak;
	std::vector<Bond*> existingBonds;
	std::vector<float> Results;
	std::vector<std::vector<bool> > BondPossible;
	
	for(int i  = 0; i < 20; i++)
	{
		BondPossible.push_back(std::vector<bool> (20, false ));
	}



	std::vector<std::string> bondsExisting ;
	std::vector<std::string> bondsNew;
	std::vector<std::string> productStructure;
	RBN* rbnA;
	Bond* possibleBond;
	
	int Aidx, Bidx;
	int CC , ProbForward, ProbBack , SC, possibleSwaps, numberToSwap, PBP0A, PBP0B, PBP0AB, PBP1A, PBP1B, PBP1AB, fail;
	bool reactionSuccess = false;
	int numberSuccessful = 0; 
	fail = 0;
	std::string productString;
	for(int attempt = 0; attempt< 1000; attempt++)
	{
			//cout << attempt << "\n";
			involvedParticles.clear();
			Aidx = rand() % Reactor.size();
			Bidx = rand() % Reactor.size();

			particleA = Reactor[Aidx]->clone(); //New PA
			particleB = Reactor[Bidx]->clone(); //New PB

			particleA->CalculateParticle();
			particleB->CalculateParticle();

			ilAc = particleA->GetFreeInteractionList();
			ilBc = particleB->GetFreeInteractionList();
			if(ilAc != NULL && ilBc != NULL)
			{
				// Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
				CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
				PBP0A = abs(ilAc->GetBindingProperty(false));
				PBP0B = abs(ilBc->GetBindingProperty(false));
				//cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
				//cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
				if(CC == 0)
				{
					// Create a bond which makes NumberToSwap swaps between ilA and ilB
					possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond
				
					involvedParticles.push_back(particleA);
					involvedParticles.push_back(particleB);

					// Create new composit particle
					particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
					delete particleA;
					delete particleB;
					
					productParticles = CheckStability(particleAB);
					
					
					for(int i  = 0; i < productParticles.size(); i++)
					{
						if(productParticles[i]->GetParticleSize() == 1)
						{
							productParticles[i]->DeepDelete();
							delete productParticles[i];
							productParticles[i] = NULL;
						}else{
							for(int j = 0; j< Reactor.size(); j++)
							{
								if(productParticles[i]->GetParticleSize() == Reactor[j]->GetParticleSize())
								{
									if(productParticles[i]->GetExistingBonds().size() == Reactor[j]->GetExistingBonds().size())
									{
										bondsExisting = Reactor[j]->GetPrettyName();
										bondsNew = productParticles[i]->GetPrettyName();
										std::sort(bondsExisting.begin(), bondsExisting.end());
										std::sort(bondsNew.begin(), bondsNew.end());
										if (bondsExisting == bondsNew)
										{
											productParticles[i]->DeepDelete();
											delete productParticles[i];
											productParticles[i] = NULL;
											j = Reactor.size();
										
										}
									}
								}
							}
						}
					}

					for( int i = 0; i< productParticles.size(); i++)
					{
						if(productParticles[i] != NULL)
						{
							existingBonds = productParticles[i]->GetExistingBonds();
							for(int j = 0; j < existingBonds.size(); j++)
							{
								if(existingBonds[j]->ContainsInteractionList(ilAc))
								{
									if(existingBonds[j]->ContainsInteractionList(ilBc))
									{
										reactionSuccess = true;
										//Bond made still exists
										BondPossible[existingBonds[j]->GetParticipentA()->GetRBNSymbol() - 'A'][existingBonds[j]->GetParticipentB()->GetRBNSymbol() - 'A'] = true;
										BondPossible[existingBonds[j]->GetParticipentB()->GetRBNSymbol() - 'A'][existingBonds[j]->GetParticipentA()->GetRBNSymbol() - 'A'] = true;
									}
								}
							}
							
							Reactor.push_back(productParticles[i]);
							if(reacNumber > -1)
							{
								productString  = productString + "," + std::to_string(Reactor.size()- 1);
								productStructure = productParticles[i]->GetPrettyStruct();
								file.open("productsR_"+ std::to_string(reacNumber) , ios::app);
								file << std::to_string(Reactor.size()- 1) << endl;
								for(int structIdx = 0; structIdx < productStructure.size(); structIdx++)
								{
									file << productStructure[structIdx] << endl;
								}
								file << endl;
								file.close();
							}
						}
					}
					if(reacNumber > -1 && productString.length() > 0 )
					{
						file.open("reactionsR_" + std::to_string(reacNumber), ios::app );
						file << std::to_string(Aidx) << "," << std::to_string(Bidx) << "-";
						file << productString << endl;
						file.close();
						productString.clear();
					}
					if(reactionSuccess)
					{
						numberSuccessful++;
					}
					reactionSuccess = false;
					//fileCC << CC << ",";
					///fileSC<< SC << ",";
					//filePF<< ProbForward << ",";
					//filePB<< ProbBack << ",";
					//fileSize << particleAB->GetParticleSize() << ",";
				}else
				{
					fail++;
					particleA->DeepDelete();
					particleB->DeepDelete();
					delete particleA;
					delete particleB;
					
				}
				
			}else
			{
				fail++;
				particleA->DeepDelete();
				particleB->DeepDelete();
				delete particleA;
				delete particleB;
					
			}
	}
	Results.push_back(Reactor.size() - 20);
	 
	std::vector<float> s_sizes;
	std::vector<float> st_sizes;
	std::map<char, int> numberParticles;
	for(int i = 0; i< 20; i++)
	{
		numberParticles.insert(std::pair<char, int> ('A'+i , 0));
	}
	float S_total = 0;
	float St_total = 0;
	float bonds_per_particle= 0;
	std::vector<std::string> st_list;
	float mean;
	float st_mean;
	float deviation;
	
	///TODO Get The Pretty 
	for(int i = 20; i< Reactor.size(); i++)
	{
		S_total += Reactor[i]->GetParticleSize();
		s_sizes.push_back( Reactor[i]->GetParticleSize() );

		st_list = Reactor[i]->GetPrettyName();
		for(int j = 0; j< st_list.size(); j++)
		{
			St_total += st_list[j].size() - 1 ;
			numberParticles[st_list[j].at(0)]++;
		}
		st_mean = St_total/ st_list.size();

		deviation = 0;

		for(int j = 0; j< st_list.size(); j++)
		{
			deviation +=  pow((st_list[j].size() - 1 - st_mean), 2);
		}

		st_sizes.push_back(deviation/ st_list.size());
		St_total = 0;
	}

	mean = S_total /( Reactor.size() - 20);
	deviation =0;
	for(int i = 0; i< s_sizes.size(); i++)
	{
		deviation += pow((s_sizes[i] - mean), 2);
	}
	Results.push_back(deviation / (Reactor.size() - 20));

	St_total = 0;
	for(int i = 0; i< st_sizes.size(); i++)
	{
		St_total += st_sizes[i];
	}
	
	Results.push_back(St_total / (Reactor.size() - 20));
	
	Results.push_back(numberSuccessful);
	
	int numberPossible = 0;

	for(int i  = 0; i < 20; i++)
	{
		for(int j  = 0; j < 20; j++)
		{
			if(BondPossible[i][j]){
				numberPossible++;
			}
		}
		Results.push_back(numberPossible);
		numberPossible = 0;
	}

	for(int i = 20; i< Reactor.size(); i++)
	{
		Reactor[i]->DeepDelete();
		delete Reactor[i];
	}
	Reactor.clear();
	Reactor.shrink_to_fit();

	for (std::map<char,int>::iterator it=numberParticles.begin(); it!=numberParticles.end(); ++it)
	{
		Results.push_back(it->second);
	}
	
	return Results;
}

void nonMassConcerving(std::vector<Particle*> Reac, int reacNumber)
{
    //14, 34357, 8267209, 668431
    std::vector<Particle*> Reactor;
    Reactor.reserve(2000);
    std::vector<bool> InitOne (12, true );
    ofstream file;
    Particle* particleA;
    Particle* particleB;
    Particle* particleAB;
    InteractionList* ilAc;
    InteractionList* ilBc;
    std::vector<Particle*> involvedParticles;
    std::vector<Particle*> productParticles;
    std::vector<Particle*> genResults;
    std::vector<Bond*> currentBonds;
    std::vector<Bond*> BondsToBreak;
    std::vector<Bond*> existingBonds;
    std::vector<float> Results;
    std::vector<std::vector<bool> > BondPossible;

    for(int i  = 0; i < 20; i++)
    {
        BondPossible.push_back(std::vector<bool> (20, false ));
    }


	std::vector<int> ILvalues;
	std::vector<InteractionList*> allILs, partialILs;
    std::vector<std::string> bondsExisting ;
    std::vector<std::string> bondsNew;
    std::vector<std::string> productStructure;
    RBN* rbnA;
    Bond* possibleBond;
	std::string productString, aString, bString;
	std::map<int, std::vector<std::vector<std::string>>> uniqueParticles;
	std::map<int, std::vector<std::vector<std::string>>>::iterator UPittr ;
	std::vector<std::vector<std::string>> initialSet, searchSet;
    int Aidx, Bidx, noILChanged;
    int CC , ProbForward, ProbBack , SC, possibleSwaps, numberToSwap, PBP0A, PBP0B, PBP0AB, PBP1A, PBP1B, PBP1AB, fail;
    bool reactionSuccess = false;
	bool matchFound = false;
    int numberSuccessful = 0;
	int progress = 0;
    fail = 0;

	file.open("/home/mike/Phd/nonMC_IL/nMC_AtomicIL_" + std::to_string(reacNumber) + "", ios::app);
	for(int i = 0; i< Reac.size(); i++)
	{
		initialSet.push_back(Reac[i]->GetPrettyName());
		Reac[i]->CalculateParticle();
		file << Reac[i]->GetPrettyName()[0] << ";";
		allILs.clear();
		allILs = Reac[i]->GetAllInteractionLists();
		for (int k = 0; k < allILs.size(); k++){
			file << allILs[k]->GetBindingProperty(false) << ",";
		}
		file << endl;
		Reac[i]->setuID(concatNumbers(1, i + 1));

		Reactor.push_back(Reac[i]->clone());


	}
	file.close();
	uniqueParticles.emplace(1, initialSet);

    for(int attempt = 0; attempt< 5000; attempt++)
    {
		progress++;
		if ((progress % 1000 )== 0){
			cout << "Reactor" << reacNumber << " Progress: " <<progress/1000 << endl;
		}
        //cout << attempt << "\n";
        involvedParticles.clear();
        Aidx = rand() % Reactor.size();
        Bidx = rand() % Reactor.size();

        particleA = Reactor[Aidx]->clone(); //New PA
        particleB = Reactor[Bidx]->clone(); //New PB
		aString = particleA->GetuID();
		bString = particleB->GetuID();
        particleA->CalculateParticle();
        particleB->CalculateParticle();

        ilAc = particleA->GetFreeInteractionList();
        ilBc = particleB->GetFreeInteractionList();
        if(ilAc != NULL && ilBc != NULL)
        {
            // Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
            CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
            PBP0A = abs(ilAc->GetBindingProperty(false));
            PBP0B = abs(ilBc->GetBindingProperty(false));
            //cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
            //cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
            if(CC == 0)
            {
				// Get all Interaction lists
				allILs = particleA->GetAllInteractionLists();
				partialILs = particleB->GetAllInteractionLists();
				allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
				partialILs.clear();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for(int i  = 0; i < allILs.size(); i++)                {
					ILvalues.push_back(allILs[i]->GetBindingProperty(false));
				}
                // Create a bond which makes NumberToSwap swaps between ilA and ilB
                possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                involvedParticles.push_back(particleA);
                involvedParticles.push_back(particleB);

                // Create new composit particle
                particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                delete particleA;
                delete particleB;

                productParticles = CheckStability(particleAB);

				noILChanged = 0;
				for(int i  = 0; i < allILs.size(); i++){

					if ((ILvalues[i] - allILs[i]->GetBindingProperty(false)) != 0) {
						noILChanged++;

					}
				}
				ILvalues.clear();
				allILs.clear();


                for(int i  = 0; i < productParticles.size(); i++)
                {
					UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());

					if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
						searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];

						bondsNew = productParticles[i]->GetPrettyName();
						std::sort(bondsNew.begin(), bondsNew.end());
						for (int j = 0; j < searchSet.size(); j++) {
							bondsExisting = searchSet[j];
							std::sort(bondsExisting.begin(), bondsExisting.end());
							if (bondsExisting == bondsNew) { //if the particle has already been discoverd
								productParticles[i]->setuID(
										concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
								j = searchSet.size(); //jump out of the for loop
								matchFound = true; // set match to true

							}
						}
						if (!matchFound) //if the particle is new
						{

							searchSet.push_back(bondsNew);
							productParticles[i]->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
							uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

							file.open("/home/mike/Phd/nonMC_IL/nMCproducts_" + std::to_string(reacNumber), ios::app);
							std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

							file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
							for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
							{
								file <<prettystructure[structIdx] << endl;
							}
							file << endl;

							file.close();

						}
					} else { // if no particles of this size have been found insert a new pair into the map
						searchSet.push_back(productParticles[i]->GetPrettyName());
						productParticles[i]->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
						uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
						file.open("/home/mike/Phd/nonMC_IL/nMCproducts_" + std::to_string(reacNumber), ios::app);
						std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

						file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
						for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
						{
							file <<prettystructure[structIdx] << endl;
						}
						file << endl;

						file.close();
					}
					searchSet.clear();
					matchFound = false;
					productString = productString + " , " + productParticles[i]->GetuID();

                    if(productParticles[i]->GetParticleSize() == 1)
                    {
                        productParticles[i]->DeepDelete();
                        delete productParticles[i];
                        productParticles[i] = NULL;
                    }else{
                        for(int j = 0; j< Reactor.size(); j++)
                        {
                            if(productParticles[i]->GetParticleSize() == Reactor[j]->GetParticleSize())
                            {
                                if(productParticles[i]->GetExistingBonds().size() == Reactor[j]->GetExistingBonds().size())
                                {
                                    bondsExisting = Reactor[j]->GetPrettyName();
                                    bondsNew = productParticles[i]->GetPrettyName();
                                    std::sort(bondsExisting.begin(), bondsExisting.end());
                                    std::sort(bondsNew.begin(), bondsNew.end());
                                    if (bondsExisting == bondsNew)
                                    {
                                        productParticles[i]->DeepDelete();
                                        delete productParticles[i];
                                        productParticles[i] = NULL;
                                        j = Reactor.size();

                                    }
                                }
                            }
                        }
                    }
                }

                for( int i = 0; i< productParticles.size(); i++)
                {
                    if(productParticles[i] != NULL)
                    {
                        existingBonds = productParticles[i]->GetExistingBonds();
                        for(int j = 0; j < existingBonds.size(); j++)
                        {
                            if(existingBonds[j]->ContainsInteractionList(ilAc))
                            {
                                if(existingBonds[j]->ContainsInteractionList(ilBc))
                                {
                                    reactionSuccess = true;
                                    //Bond made still exists
                                    BondPossible[existingBonds[j]->GetParticipentA()->GetRBNSymbol() - 'A'][existingBonds[j]->GetParticipentB()->GetRBNSymbol() - 'A'] = true;
                                    BondPossible[existingBonds[j]->GetParticipentB()->GetRBNSymbol() - 'A'][existingBonds[j]->GetParticipentA()->GetRBNSymbol() - 'A'] = true;
                                }
                            }
                        }

                        Reactor.push_back(productParticles[i]);

                    }
                }

                if(reactionSuccess)
                {
                    numberSuccessful++;
                }
                reactionSuccess = false;
                //fileCC << CC << ",";
                ///fileSC<< SC << ",";
                //filePF<< ProbForward << ",";
                //filePB<< ProbBack << ",";
                //fileSize << particleAB->GetParticleSize() << ",";
				file.open("/home/mike/Phd/nonMC_IL/nMCreactions_" + std::to_string(reacNumber), ios::app);
				file << noILChanged << "| ";
				file << aString << "," << bString << "-";
				file << productString << endl;
				file.close();
				productString.clear();
            }else
            {
                fail++;
                particleA->DeepDelete();
                particleB->DeepDelete();
                delete particleA;
                delete particleB;

            }

        }else
        {
            fail++;
            particleA->DeepDelete();
            particleB->DeepDelete();
            delete particleA;
            delete particleB;

        }
    }

	for(int i = 0; i< Reactor.size(); i++)
	{
		Reactor[i]->DeepDelete();
		delete Reactor[i];
	}
	Reactor.clear();
	Reactor.shrink_to_fit();
}



void MassConservingReactor(std::vector<Particle*> Reac, int reacNumber, int runNumber)
{
    std::vector<Particle*> involvedParticles, productParticles, Reactor;
    Particle* particleA, *particleB, *particleAB, *swapParticle;
    InteractionList* ilAc, *ilBc;
    Bond* possibleBond;
	std::string productString, aString, bString;
	std::vector<std::string> productStructure, bondsNew, bondsExisting;
	ofstream file;
	std::map<int, std::vector<Particle*>> uniqueParticles;
	std::map<int, std::vector<Particle*>>::iterator UPittr ;
	std::vector<Particle*> initialSet, searchSet;
	std::vector<int> ILvalues;
	std::vector<InteractionList*> allILs, partialILs;
    std::string ilChangeString;
	int recordCounter, UniqueSucess;
	bool matchFound = false;
    std::string filePath = "/home/mike/Phd/Paper/MC/";
    int CC , rndIdx;
    file.open(filePath + "MC_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
	for(int i = 0; i< Reac.size(); i++)
	{
		initialSet.push_back(Reac[i]->clone());
        Reac[i]->CalculateParticle();
        file << Reac[i]->GetPrettyName()[0] << ";";
        allILs.clear();
        allILs = Reac[i]->GetAllInteractionLists();
        for (int k = 0; k < allILs.size(); k++){
            file << allILs[k]->GetBindingProperty(false) << ",";
        }
        file << endl;
		Reac[i]->setuID(concatNumbers(1, i + 1));
		for(int j =0; j <200; j++) {
			Reactor.push_back(Reac[i]->clone());

		}
	}
    file.close();
	uniqueParticles.emplace(1, initialSet);


	UniqueSucess = 0;
	random_shuffle(Reactor.begin(), Reactor.end());
	recordCounter = 0;
	for(int attempt = 0; attempt<100000; attempt++) {

		recordCounter++;
		if (recordCounter == 10000){
			file.open(filePath+"MC_Sucesses_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
			file << UniqueSucess << ',';
            file.close();
            file.open(filePath + "MC_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << '--'<< endl;
            file.close();
			recordCounter = 0;
			UniqueSucess = 0;
		}


		involvedParticles.clear();
		particleA = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		particleB = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		aString = particleA->GetuID();
		bString = particleB->GetuID();
		particleA->CalculateParticle();
		particleB->CalculateParticle();


		ilAc = particleA->GetFreeInteractionList();
		ilBc = particleB->GetFreeInteractionList();
		if (ilAc != NULL && ilBc != NULL) {

			// Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
			CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
			//cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
			//cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
			if (CC == 0) {

                // Get all Interaction lists
				allILs = particleA->GetAllInteractionLists();
				partialILs = particleB->GetAllInteractionLists();
				allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
				partialILs.clear();
                ILvalues.clear();
                //Get IL values before bonding to be compared with values after bonding
                //to see if bonding resulted in meaningful change
                for(int i  = 0; i < allILs.size(); i++)                {
                    ILvalues.push_back(allILs[i]->GetBindingProperty(false));
                }


				// Create a bond which makes NumberToSwap swaps between ilA and ilB
				possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

				involvedParticles.push_back(particleA);
				involvedParticles.push_back(particleB);

				// Create new composit particle
				particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
				delete particleA;
				delete particleB;

				productParticles = CheckStability(particleAB);

                //For each product particle
				for (int i = 0; i < productParticles.size(); i++) {
                    //put it randomly back in the reactor
					rndIdx = rand() % Reactor.size(); //get rand index
					swapParticle = Reactor[rndIdx]; //take out particle at idx
					Reactor[rndIdx] = productParticles[i]; // replace with one product
					Reactor.push_back(swapParticle); // push back particle to back

                    //get a pointer to reference particles of that size
					UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());

					if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                        //get a search set of all reference particles of that size
						searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                        //For each particle in the reference set
						for (int j = 0; j < searchSet.size(); j++) {
							if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
								productParticles[i]->setuID(
										concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
								j = searchSet.size(); //jump out of the for loop
								matchFound = true; // set match to true

							}
						}
						if (!matchFound) //if the particle is new but the size has been seen before
						{
							UniqueSucess++;

                            //give it a unique id
							productParticles[i]->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            //put the new reference set for that size back in the unique particles reference set
							uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

							file.open(filePath + "MC_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
							std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

							file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
							for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
							{
								file <<prettystructure[structIdx] << endl;
							}
							file << endl;

							file.close();

						}
					} else { // if no particles of this size have been found insert a new pair into the map
                        UniqueSucess++;

                        //give the product a uid
						productParticles[i]->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                        //clone the particle
                        searchSet.push_back(productParticles[i]->clone());
                        //put particel in reference set
						uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
						file.open(filePath +"MC_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
						std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

						file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
						for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
						{
							file <<prettystructure[structIdx] << endl;
						}
						file << endl;

						file.close();
					}
					searchSet.clear();
					matchFound = false;
					productString = productString + " , " + productParticles[i]->GetuID();
				}
                //After bonding compare bonding property
                std::map<InteractionList*, int> noILChanged ;

                for(int i  = 0; i < allILs.size(); i++){

                    if ((ILvalues[i] - allILs[i]->GetBindingProperty(false)) != 0) {
                        noILChanged.emplace(std::make_pair(allILs[i], 1));

                    }else{
                        noILChanged.emplace(std::make_pair(allILs[i], 0));
                    }
                }

                int ilsChanged = 0;
                for(int i = 0; i < productParticles.size(); i++) {
                    partialILs = productParticles[i]->GetAllInteractionLists();
                    ilsChanged = 0;
                    for(int j  =0; j<partialILs.size(); j++){
                        ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                    }
                    ilChangeString.append(std::to_string(ilsChanged) + ", ");

                }
                ILvalues.clear();
                allILs.clear();
                partialILs.clear();
				file.open(filePath + "MC_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                file << ilChangeString << "| ";
				file << aString << "," << bString << "-";
				file << productString << endl;
				file.close();
                ilChangeString.clear();
				productString.clear();

			} else { // if CC isn't met replace particleA and B randomly into the reactor
				rndIdx = rand() % Reactor.size(); //get rand index
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleA; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back

				rndIdx = rand() % Reac.size(); //get rand index
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleB; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
			}

		} else { // if there are no interaction lists free replace A and B randomly.
			rndIdx = rand() % Reactor.size(); //get rand index
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleA; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back

			rndIdx = rand() % Reac.size(); //get rand index
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleB; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
		}
	}
	std::vector<std::string> reacUids;
	for (int i = 0; i < Reactor.size(); i++)
	{
		reacUids.push_back(Reactor[i]->GetuID());
	}

	std::sort(reacUids.begin(), reacUids.end());

	file.open(filePath + "MC_Contents_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
	std::string currentUid = reacUids[0];
	int count = 0;
	for (int i = 0; i < reacUids.size(); i++)
	{
		if(currentUid == reacUids[i]) {
			count++;
		}else
		{
			file << currentUid << " , " << count << endl;
			count = 1;
			currentUid = reacUids[i];
		}
	}
	file.close();

    for(auto v : Reactor)
    {
        v->DeepDelete();
        delete v;
    }
    for(auto v : uniqueParticles)
    {
        for(auto p: v.second) {
            p->DeepDelete();
        }

    }
    uniqueParticles.clear();

}

void FlowReactor(std::vector<Particle*> Reac, int reacNumber, int runNumber)
{

    std::vector<Particle*> involvedParticles, productParticles, Reactor;
    Particle* particleA, *particleB, *particleAB, *swapParticle;
    InteractionList* ilAc, *ilBc;
    Bond* possibleBond;
    std::string productString, aString, bString;
    std::vector<std::string> productStructure, bondsNew, bondsExisting;
    ofstream file;
    std::map<int, std::vector<Particle*>> uniqueParticles;
    std::map<int, std::vector<Particle*>>::iterator UPittr ;
    std::map<char, int> feedSet;
    std::vector<Particle*> inflow;
    std::vector<RBN*> componentRBNs;
    std::vector<Particle*> initialSet, searchSet;
    std::vector<int> ILvalues;
    std::vector<InteractionList*> allILs, partialILs;
    std::string ilChangeString;
    int recordCounter, UniqueSucess, particlesToAdd, totalMass, massToRemove;
    bool matchFound = false;
    std::string filePath = "/home/mike/Phd/Paper/FlowF/";
    int CC , rndIdx;
    file.open(filePath + "FF_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    for(int i = 0; i< Reac.size(); i++)
    {
        initialSet.push_back(Reac[i]->clone());
        Reac[i]->CalculateParticle();

        feedSet.emplace(std::make_pair('A'+i, 0));
        file << Reac[i]->GetPrettyName()[0] << ";";
        allILs.clear();
        allILs = Reac[i]->GetAllInteractionLists();
        for (int k = 0; k < allILs.size(); k++){
            file << allILs[k]->GetBindingProperty(false) << ",";
        }
        file << endl;
        Reac[i]->setuID(concatNumbers(1, i + 1));
        for(int j =0; j <200; j++) {
            Reactor.push_back(Reac[i]->clone());

        }
    }
    file.close();
    uniqueParticles.emplace(1, initialSet);


    UniqueSucess = 0;
    random_shuffle(Reactor.begin(), Reactor.end());
    recordCounter = 0;
    for(int attempt = 0; attempt<100000; attempt++) {

        recordCounter++;
        if(recordCounter == 5000|| recordCounter == 10000){
            //cout << "Inflow of food" << endl ;
            //for each atomic particle
            totalMass = 0;
            for (int partc =0; partc < Reac.size(); partc++)
            {
                //add as many to the inflow as is required by feedset
                totalMass = totalMass + feedSet['A'+partc];

            }

            for (int partc =0; partc < Reac.size(); partc++)
            {
                float ratio =
                particlesToAdd = ((float)((float)feedSet['A'+partc] / (float)totalMass) *400);

                for(int infIttr =0; infIttr < particlesToAdd; infIttr++)
                {
                    inflow.push_back(Reac[partc]->clone());
                }

            }
            massToRemove = inflow.size();
            //cout << massToRemove<< endl;
            int psize = 0;
            while(massToRemove > 0)
            {

                swapParticle = Reactor.back(); //take out particle at back

                psize = swapParticle->GetComponentRBNs().size();
                massToRemove = massToRemove - psize;
                Reactor.pop_back(); // remove from list
                swapParticle->DeepDelete();
                delete swapParticle;


            }

            Reactor.insert(Reactor.end(), inflow.begin(), inflow.end());
            // if we overshot the mass
            if(massToRemove < 0 ){
                for(massToRemove; massToRemove == 0; massToRemove++){
                    rndIdx = rand() % inflow.size(); //get rand index
                    Reactor.push_back(inflow[rndIdx]->clone());
                }
            }
            //cout << Reactor.size() << endl;
            inflow.clear();
            for(int charIttr = 0; charIttr < 20; charIttr++)
            {
                feedSet['A'+charIttr] = 0;
            }
            random_shuffle(Reactor.begin(), Reactor.end());


        }
        if (recordCounter == 10000){
            file.open(filePath+"FF_Sucesses_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << UniqueSucess << ',';
            file.close();
            file.open(filePath + "FF_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << '--'<< endl;
            file.close();
            recordCounter = 0;
            UniqueSucess = 0;
        }


        involvedParticles.clear();
        particleA = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        particleB = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        aString = particleA->GetuID();
        bString = particleB->GetuID();
        particleA->CalculateParticle();
        particleB->CalculateParticle();


        ilAc = particleA->GetFreeInteractionList();
        ilBc = particleB->GetFreeInteractionList();
        if (ilAc != NULL && ilBc != NULL) {

            // Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
            CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
            //cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
            //cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
            if (CC == 0) {

                // Get all Interaction lists
                allILs = particleA->GetAllInteractionLists();
                partialILs = particleB->GetAllInteractionLists();
                allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
                partialILs.clear();
                ILvalues.clear();

                componentRBNs = particleA->GetComponentRBNs();
                for(auto rbns : componentRBNs)
                {
                    feedSet[rbns->GetRBNSymbol()] = feedSet[rbns->GetRBNSymbol()] + 1;
                }
                componentRBNs = particleB->GetComponentRBNs();
                for(auto rbns : componentRBNs)
                {
                    feedSet[rbns->GetRBNSymbol()] = feedSet[rbns->GetRBNSymbol()] + 1;
                }
                componentRBNs.clear();
                //Get IL values before bonding to be compared with values after bonding
                //to see if bonding resulted in meaningful change
                for(int i  = 0; i < allILs.size(); i++)                {
                    ILvalues.push_back(allILs[i]->GetBindingProperty(false));
                }


                // Create a bond which makes NumberToSwap swaps between ilA and ilB
                possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                involvedParticles.push_back(particleA);
                involvedParticles.push_back(particleB);

                // Create new composit particle
                particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                delete particleA;
                delete particleB;

                productParticles = CheckStability(particleAB);

                //For each product particle
                for (int i = 0; i < productParticles.size(); i++) {
                    //put it randomly back in the reactor
                    rndIdx = rand() % Reactor.size(); //get rand index
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = productParticles[i]; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back

                    //get a pointer to reference particles of that size
                    UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());

                    if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                        //get a search set of all reference particles of that size
                        searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                        //For each particle in the reference set
                        for (int j = 0; j < searchSet.size(); j++) {
                            if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
                                productParticles[i]->setuID(
                                        concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
                                j = searchSet.size(); //jump out of the for loop
                                matchFound = true; // set match to true

                            }
                        }
                        if (!matchFound) //if the particle is new but the size has been seen before
                        {
                            UniqueSucess++;

                            //give it a unique id
                            productParticles[i]->setuID(
                                    concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            //put the new reference set for that size back in the unique particles reference set
                            uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

                            file.open(filePath + "FF_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                            std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                            file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                            for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                            {
                                file <<prettystructure[structIdx] << endl;
                            }
                            file << endl;

                            file.close();

                        }
                    } else { // if no particles of this size have been found insert a new pair into the map
                        UniqueSucess++;

                        //give the product a uid
                        productParticles[i]->setuID(
                                concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                        //clone the particle
                        searchSet.push_back(productParticles[i]->clone());
                        //put particel in reference set
                        uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
                        file.open(filePath +"FF_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                        std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                        file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                        for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                        {
                            file <<prettystructure[structIdx] << endl;
                        }
                        file << endl;

                        file.close();
                    }
                    searchSet.clear();
                    matchFound = false;
                    productString = productString + " , " + productParticles[i]->GetuID();
                }
                //After bonding compare bonding property
                std::map<InteractionList*, int> noILChanged ;

                for(int i  = 0; i < allILs.size(); i++){

                    if ((ILvalues[i] - allILs[i]->GetBindingProperty(false)) != 0) {
                        noILChanged.emplace(std::make_pair(allILs[i], 1));

                    }else{
                        noILChanged.emplace(std::make_pair(allILs[i], 0));
                    }
                }

                int ilsChanged = 0;
                for(int i = 0; i < productParticles.size(); i++) {
                    partialILs = productParticles[i]->GetAllInteractionLists();
                    ilsChanged = 0;
                    for(int j  =0; j<partialILs.size(); j++){
                        ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                    }
                    ilChangeString.append(std::to_string(ilsChanged) + ", ");

                }
                ILvalues.clear();
                allILs.clear();
                partialILs.clear();
                file.open(filePath + "FF_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                file << ilChangeString << "| ";
                file << aString << "," << bString << "-";
                file << productString << endl;
                file.close();
                ilChangeString.clear();
                productString.clear();

            } else { // if CC isn't met replace particleA and B randomly into the reactor
                rndIdx = rand() % Reactor.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleA; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back

                rndIdx = rand() % Reac.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleB; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back
            }

        } else { // if there are no interaction lists free replace A and B randomly.
            rndIdx = rand() % Reactor.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleA; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back

            rndIdx = rand() % Reac.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleB; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back
        }
    }
    std::vector<std::string> reacUids;
    for (int i = 0; i < Reactor.size(); i++)
    {
        reacUids.push_back(Reactor[i]->GetuID());
    }

    std::sort(reacUids.begin(), reacUids.end());

    file.open(filePath + "FF_Contents_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    std::string currentUid = reacUids[0];
    int count = 0;
    for (int i = 0; i < reacUids.size(); i++)
    {
        if(currentUid == reacUids[i]) {
            count++;
        }else
        {
            file << currentUid << " , " << count << endl;
            count = 1;
            currentUid = reacUids[i];
        }
    }
    file.close();

    for(auto v : Reactor)
    {
        v->DeepDelete();
        delete v;
    }
    for(auto v : uniqueParticles)
    {
        for(auto p: v.second) {
            p->DeepDelete();
        }

    }
    uniqueParticles.clear();


}

void FlowReactorRandom(std::vector<Particle*> Reac, int reacNumber, int runNumber)
{

    std::vector<Particle*> involvedParticles, productParticles, Reactor;
    Particle* particleA, *particleB, *particleAB, *swapParticle;
    InteractionList* ilAc, *ilBc;
    Bond* possibleBond;
    std::string productString, aString, bString;
    std::vector<std::string> productStructure, bondsNew, bondsExisting;
    ofstream file;
    std::map<int, std::vector<Particle*>> uniqueParticles;
    std::map<int, std::vector<Particle*>>::iterator UPittr ;
    std::map<char, int> feedSet;
    std::vector<Particle*> inflow;
    std::vector<RBN*> componentRBNs;
    std::vector<Particle*> initialSet, searchSet;
    std::vector<int> ILvalues;
    std::vector<InteractionList*> allILs, partialILs;
    std::string ilChangeString;
    int recordCounter, UniqueSucess, particlesToAdd, totalMass, massToRemove;
    bool matchFound = false;
    std::string filePath = "/home/mike/Phd/Paper/FlowR/";
    int CC , rndIdx;
    file.open(filePath + "FR_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    for(int i = 0; i< Reac.size(); i++)
    {
        initialSet.push_back(Reac[i]->clone());
        Reac[i]->CalculateParticle();

        feedSet.emplace(std::make_pair('A'+i, 0));
        file << Reac[i]->GetPrettyName()[0] << ";";
        allILs.clear();
        allILs = Reac[i]->GetAllInteractionLists();
        for (int k = 0; k < allILs.size(); k++){
            file << allILs[k]->GetBindingProperty(false) << ",";
        }
        file << endl;
        Reac[i]->setuID(concatNumbers(1, i + 1));
        for(int j =0; j <200; j++) {
            Reactor.push_back(Reac[i]->clone());

        }
    }
    file.close();
    uniqueParticles.emplace(1, initialSet);


    UniqueSucess = 0;
    random_shuffle(Reactor.begin(), Reactor.end());
    recordCounter = 0;
    for(int attempt = 0; attempt<100000; attempt++) {

        recordCounter++;
        if(recordCounter == 5000|| recordCounter == 10000){
            Particle* p;
            for(int counter; counter < 400; counter++)
            {
                p = Reactor.back();
                Reactor.pop_back();
                p->DeepDelete();
                delete p;
            }
            for(int counter; counter < 400; counter++)
            {
                rndIdx = rand() % Reac.size(); //get rand index
                Reactor.push_back( Reac[rndIdx]->clone());
            }
            //cout << Reactor.size() << endl;
            inflow.clear();
            for(int charIttr = 0; charIttr < 20; charIttr++)
            {
                feedSet['A'+charIttr] = 0;
            }

            random_shuffle(Reactor.begin(), Reactor.end());

        }
        if (recordCounter == 10000){
            file.open(filePath+"FR_Sucesses_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << UniqueSucess << ',';
            file.close();
            file.open(filePath + "FR_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << '--'<< endl;
            file.close();
            recordCounter = 0;
            UniqueSucess = 0;
        }


        involvedParticles.clear();
        particleA = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        particleB = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        aString = particleA->GetuID();
        bString = particleB->GetuID();
        particleA->CalculateParticle();
        particleB->CalculateParticle();


        ilAc = particleA->GetFreeInteractionList();
        ilBc = particleB->GetFreeInteractionList();
        if (ilAc != NULL && ilBc != NULL) {

            // Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
            CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
            //cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
            //cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
            if (CC == 0) {

                // Get all Interaction lists
                allILs = particleA->GetAllInteractionLists();
                partialILs = particleB->GetAllInteractionLists();
                allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
                partialILs.clear();
                ILvalues.clear();

                componentRBNs = particleA->GetComponentRBNs();
                for(auto rbns : componentRBNs)
                {
                    feedSet[rbns->GetRBNSymbol()] = feedSet[rbns->GetRBNSymbol()] + 1;
                }
                componentRBNs = particleB->GetComponentRBNs();
                for(auto rbns : componentRBNs)
                {
                    feedSet[rbns->GetRBNSymbol()] = feedSet[rbns->GetRBNSymbol()] + 1;
                }
                componentRBNs.clear();
                //Get IL values before bonding to be compared with values after bonding
                //to see if bonding resulted in meaningful change
                for(int i  = 0; i < allILs.size(); i++)                {
                    ILvalues.push_back(allILs[i]->GetBindingProperty(false));
                }


                // Create a bond which makes NumberToSwap swaps between ilA and ilB
                possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                involvedParticles.push_back(particleA);
                involvedParticles.push_back(particleB);

                // Create new composit particle
                particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                delete particleA;
                delete particleB;

                productParticles = CheckStability(particleAB);

                //For each product particle
                for (int i = 0; i < productParticles.size(); i++) {
                    //put it randomly back in the reactor
                    rndIdx = rand() % Reactor.size(); //get rand index
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = productParticles[i]; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back

                    //get a pointer to reference particles of that size
                    UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());

                    if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                        //get a search set of all reference particles of that size
                        searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                        //For each particle in the reference set
                        for (int j = 0; j < searchSet.size(); j++) {
                            if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
                                productParticles[i]->setuID(
                                        concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
                                j = searchSet.size(); //jump out of the for loop
                                matchFound = true; // set match to true

                            }
                        }
                        if (!matchFound) //if the particle is new but the size has been seen before
                        {
                            UniqueSucess++;

                            //give it a unique id
                            productParticles[i]->setuID(
                                    concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            //put the new reference set for that size back in the unique particles reference set
                            uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

                            file.open(filePath + "FR_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                            std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                            file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                            for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                            {
                                file <<prettystructure[structIdx] << endl;
                            }
                            file << endl;

                            file.close();

                        }
                    } else { // if no particles of this size have been found insert a new pair into the map
                        UniqueSucess++;

                        //give the product a uid
                        productParticles[i]->setuID(
                                concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                        //clone the particle
                        searchSet.push_back(productParticles[i]->clone());
                        //put particel in reference set
                        uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
                        file.open(filePath +"FR_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                        std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                        file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                        for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                        {
                            file <<prettystructure[structIdx] << endl;
                        }
                        file << endl;

                        file.close();
                    }
                    searchSet.clear();
                    matchFound = false;
                    productString = productString + " , " + productParticles[i]->GetuID();
                }
                //After bonding compare bonding property
                std::map<InteractionList*, int> noILChanged ;

                for(int i  = 0; i < allILs.size(); i++){

                    if ((ILvalues[i] - allILs[i]->GetBindingProperty(false)) != 0) {
                        noILChanged.emplace(std::make_pair(allILs[i], 1));

                    }else{
                        noILChanged.emplace(std::make_pair(allILs[i], 0));
                    }
                }

                int ilsChanged = 0;
                for(int i = 0; i < productParticles.size(); i++) {
                    partialILs = productParticles[i]->GetAllInteractionLists();
                    ilsChanged = 0;
                    for(int j  =0; j<partialILs.size(); j++){
                        ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                    }
                    ilChangeString.append(std::to_string(ilsChanged) + ", ");

                }
                ILvalues.clear();
                allILs.clear();
                partialILs.clear();
                file.open(filePath + "FR_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                file << ilChangeString << "| ";
                file << aString << "," << bString << "-";
                file << productString << endl;
                file.close();
                ilChangeString.clear();
                productString.clear();

            } else { // if CC isn't met replace particleA and B randomly into the reactor
                rndIdx = rand() % Reactor.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleA; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back

                rndIdx = rand() % Reac.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleB; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back
            }

        } else { // if there are no interaction lists free replace A and B randomly.
            rndIdx = rand() % Reactor.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleA; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back

            rndIdx = rand() % Reac.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleB; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back
        }
    }
    std::vector<std::string> reacUids;
    for (int i = 0; i < Reactor.size(); i++)
    {
        reacUids.push_back(Reactor[i]->GetuID());
    }

    std::sort(reacUids.begin(), reacUids.end());

    file.open(filePath + "FR_Contents_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    std::string currentUid = reacUids[0];
    int count = 0;
    for (int i = 0; i < reacUids.size(); i++)
    {
        if(currentUid == reacUids[i]) {
            count++;
        }else
        {
            file << currentUid << " , " << count << endl;
            count = 1;
            currentUid = reacUids[i];
        }
    }
    file.close();

    for(auto v : Reactor)
    {
        v->DeepDelete();
        delete v;
    }
    for(auto v : uniqueParticles)
    {
        for(auto p: v.second) {
            p->DeepDelete();
        }

    }
    uniqueParticles.clear();


}

void CompositReactor(std::vector<Particle*> Reac, int reacNumber, int runNumber)
{
    std::vector<Particle*> involvedParticles, productParticles, Reactor;
    Particle* particleA, *particleB, *particleAB, *swapParticle;
    InteractionList* ilAc, *ilBc;
    Bond* possibleBond;
    std::string productString, aString, bString;
    std::vector<std::string> productStructure, bondsNew, bondsExisting;
    ofstream file;
    std::map<int, std::vector<Particle*>> uniqueParticles;
    std::map<int, std::vector<Particle*>>::iterator UPittr ;
    std::vector<Particle*> initialSet, searchSet;
    std::vector<int> ILvalues;
    std::vector<InteractionList*> allILs, partialILs;
    std::string ilChangeString;

    int recordCounter, UniqueSucess;
    bool matchFound = false;
    std::string filePath = "/home/mike/Phd/Paper/Decant/Comp/";
    int CC , rndIdx;
    file.open(filePath + "DC_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    for(int i = 0; i< Reac.size(); i++)
    {

        Reac[i]->CalculateParticle();
        productStructure = Reac[i]->GetPrettyName();
        for(int structIdx = 0; structIdx < productStructure.size(); structIdx++)
        {
            file <<productStructure[structIdx] << endl;
        }

        allILs.clear();
        allILs = Reac[i]->GetAllInteractionLists();
        for (int k = 0; k < allILs.size(); k++){
            file << allILs[k]->GetBindingProperty(false) << ",";
        }
        file << endl;

        for(int j =0; j <100; j++) {
            Reactor.push_back(Reac[i]->clone());

        }

        UPittr = uniqueParticles.find(Reac[i]->GetParticleSize());
        searchSet.clear();
        if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
            //get a search set of all reference particles of that size
            searchSet = uniqueParticles[Reac[i]->GetParticleSize()];
            searchSet.push_back(Reac[i]->clone());
            uniqueParticles[Reac[i]->GetParticleSize()] = searchSet;
            searchSet.clear();
        }else{
            searchSet.clear();
            searchSet.push_back(Reac[i]->clone());
            uniqueParticles[Reac[i]->GetParticleSize()] = searchSet;
            searchSet.clear();
        }

        searchSet.clear();
    }
    file.close();



    UniqueSucess = 0;
    random_shuffle(Reactor.begin(), Reactor.end());
    recordCounter = 0;
    for(int attempt = 0; attempt<100000; attempt++) {

        recordCounter++;
        if (recordCounter == 10000){
            file.open(filePath+"DC_Sucesses_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << UniqueSucess << ',';
            file.close();
            file.open(filePath + "DC_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << '--'<< endl;
            file.close();
            recordCounter = 0;
            UniqueSucess = 0;
        }


        involvedParticles.clear();
        particleA = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        particleB = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        aString = particleA->GetuID();
        bString = particleB->GetuID();
        particleA->CalculateParticle();
        particleB->CalculateParticle();


        ilAc = particleA->GetFreeInteractionList();
        ilBc = particleB->GetFreeInteractionList();
        if (ilAc != NULL && ilBc != NULL) {

            // Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
            CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
            //cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
            //cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
            if (CC == 0) {

                // Get all Interaction lists
                allILs = particleA->GetAllInteractionLists();
                partialILs = particleB->GetAllInteractionLists();
                allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
                partialILs.clear();
                ILvalues.clear();
                //Get IL values before bonding to be compared with values after bonding
                //to see if bonding resulted in meaningful change
                for(int i  = 0; i < allILs.size(); i++)                {
                    ILvalues.push_back(allILs[i]->GetBindingProperty(false));
                }


                // Create a bond which makes NumberToSwap swaps between ilA and ilB
                possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                involvedParticles.push_back(particleA);
                involvedParticles.push_back(particleB);

                // Create new composit particle
                particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                delete particleA;
                delete particleB;

                productParticles = CheckStability(particleAB);

                //For each product particle
                for (int i = 0; i < productParticles.size(); i++) {
                    //put it randomly back in the reactor
                    rndIdx = rand() % Reactor.size(); //get rand index
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = productParticles[i]; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back

                    //get a pointer to reference particles of that size
                    UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());

                    if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                        //get a search set of all reference particles of that size
                        searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                        //For each particle in the reference set
                        for (int j = 0; j < searchSet.size(); j++) {
                            if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
                                productParticles[i]->setuID(
                                        concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
                                j = searchSet.size(); //jump out of the for loop
                                matchFound = true; // set match to true

                            }
                        }
                        if (!matchFound) //if the particle is new but the size has been seen before
                        {
                            UniqueSucess++;

                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //give it a unique id
                            productParticles[i]->setuID(
                                    concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //put the new reference set for that size back in the unique particles reference set
                            uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

                            file.open(filePath + "DC_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                            std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                            file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                            for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                            {
                                file <<prettystructure[structIdx] << endl;
                            }
                            file << endl;

                            file.close();

                        }
                    } else { // if no particles of this size have been found insert a new pair into the map
                        UniqueSucess++;

                        //clone and add to refrence set
                        searchSet.push_back(productParticles[i]->clone());
                        searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                        //give it a unique id
                        productParticles[i]->setuID(
                                concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                        //put particel in reference set
                        uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
                        file.open(filePath +"DC_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                        std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                        file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                        for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                        {
                            file <<prettystructure[structIdx] << endl;
                        }
                        file << endl;

                        file.close();
                    }
                    searchSet.clear();
                    matchFound = false;
                    productString = productString + " , " + productParticles[i]->GetuID();
                }
                //After bonding compare bonding property
                std::map<InteractionList*, int> noILChanged ;

                for(int i  = 0; i < allILs.size(); i++){

                    if ((ILvalues[i] - allILs[i]->GetBindingProperty(false)) != 0) {
                        noILChanged.emplace(std::make_pair(allILs[i], 1));

                    }else{
                        noILChanged.emplace(std::make_pair(allILs[i], 0));
                    }
                }

                int ilsChanged = 0;
                for(int i = 0; i < productParticles.size(); i++) {
                    partialILs = productParticles[i]->GetAllInteractionLists();
                    ilsChanged = 0;
                    for(int j  =0; j<partialILs.size(); j++){
                        ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                    }
                    ilChangeString.append(std::to_string(ilsChanged) + ", ");

                }
                ILvalues.clear();
                allILs.clear();
                partialILs.clear();
                file.open(filePath + "DC_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                file << ilChangeString << "| ";
                file << aString << "," << bString << "-";
                file << productString << endl;
                file.close();
                ilChangeString.clear();
                productString.clear();

            } else { // if CC isn't met replace particleA and B randomly into the reactor
                rndIdx = rand() % Reactor.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleA; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back

                rndIdx = rand() % Reac.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleB; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back
            }

        } else { // if there are no interaction lists free replace A and B randomly.
            rndIdx = rand() % Reactor.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleA; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back

            rndIdx = rand() % Reac.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleB; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back
        }
    }
    std::vector<std::string> reacUids;
    for (int i = 0; i < Reactor.size(); i++)
    {
        reacUids.push_back(Reactor[i]->GetuID());
    }

    std::sort(reacUids.begin(), reacUids.end());

    file.open(filePath + "DC_Contents_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    std::string currentUid = reacUids[0];
    int count = 0;
    for (int i = 0; i < reacUids.size(); i++)
    {
        if(currentUid == reacUids[i]) {
            count++;
        }else
        {
            file << currentUid << " , " << count << endl;
            count = 1;
            currentUid = reacUids[i];
        }
    }
    file.close();

    for(auto v : Reactor)
    {
        v->DeepDelete();
        delete v;
    }
    for(auto v : uniqueParticles)
    {
        for(auto p: v.second) {
            p->DeepDelete();
        }

    }
    uniqueParticles.clear();

}

void DecantReactor(std::vector<Particle*> Reac, int reacNumber, int runNumber)
{
    std::vector<Particle*> involvedParticles, productParticles, Reactor;
    Particle* particleA, *particleB, *particleAB, *swapParticle;
    InteractionList* ilAc, *ilBc;
    Bond* possibleBond;
    std::string productString, aString, bString;
    std::vector<std::string> productStructure, bondsNew, bondsExisting;
    ofstream file;
    std::map<int, std::vector<Particle*>> uniqueParticles;
    std::map<int, std::vector<Particle*>>::iterator UPittr ;
    std::vector<Particle*> initialSet, searchSet;
    std::vector<int> ILvalues;
    std::vector<InteractionList*> allILs, partialILs;
    std::string ilChangeString;
    int recordCounter, UniqueSucess;
    bool matchFound = false;
    std::string filePath = "/home/mike/Phd/Paper/Decant/Base/";
    int CC , rndIdx;
    file.open(filePath + "DB_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    for(int i = 0; i< Reac.size(); i++)
    {
        initialSet.push_back(Reac[i]->clone());
        Reac[i]->CalculateParticle();
        file << Reac[i]->GetPrettyName()[0] << ";";
        allILs.clear();
        allILs = Reac[i]->GetAllInteractionLists();
        for (int k = 0; k < allILs.size(); k++){
            file << allILs[k]->GetBindingProperty(false) << ",";
        }
        file << endl;
        Reac[i]->setuID(concatNumbers(1, i + 1));
        for(int j =0; j <200; j++) {
            Reactor.push_back(Reac[i]->clone());

        }
    }
    file.close();
    uniqueParticles.emplace(1, initialSet);


    UniqueSucess = 0;
    random_shuffle(Reactor.begin(), Reactor.end());
    recordCounter = 0;
    for(int attempt = 0; attempt<100000; attempt++) {

        recordCounter++;
        if (recordCounter == 10000){
            file.open(filePath+"DB_Sucesses_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << UniqueSucess << ',';
            file.close();
            file.open(filePath + "DB_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
            file << '--'<< endl;
            file.close();
            recordCounter = 0;
            UniqueSucess = 0;
        }


        involvedParticles.clear();
        particleA = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        particleB = Reactor.back(); //Grab particle from reactor
        Reactor.pop_back();
        aString = particleA->GetuID();
        bString = particleB->GetuID();
        particleA->CalculateParticle();
        particleB->CalculateParticle();


        ilAc = particleA->GetFreeInteractionList();
        ilBc = particleB->GetFreeInteractionList();
        if (ilAc != NULL && ilBc != NULL) {

            // Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
            CC = ilAc->GetBindingProperty(false) + ilBc->GetBindingProperty(false);
            //cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
            //cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
            if (CC == 0) {

                // Get all Interaction lists
                allILs = particleA->GetAllInteractionLists();
                partialILs = particleB->GetAllInteractionLists();
                allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
                partialILs.clear();
                ILvalues.clear();
                //Get IL values before bonding to be compared with values after bonding
                //to see if bonding resulted in meaningful change
                for(int i  = 0; i < allILs.size(); i++)                {
                    ILvalues.push_back(allILs[i]->GetBindingProperty(false));
                }


                // Create a bond which makes NumberToSwap swaps between ilA and ilB
                possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                involvedParticles.push_back(particleA);
                involvedParticles.push_back(particleB);

                // Create new composit particle
                particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                delete particleA;
                delete particleB;

                productParticles = CheckStability(particleAB);

                //For each product particle
                for (int i = 0; i < productParticles.size(); i++) {
                    //put it randomly back in the reactor
                    rndIdx = rand() % Reactor.size(); //get rand index
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = productParticles[i]; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back

                    //get a pointer to reference particles of that size
                    UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
                    searchSet.clear();
                    matchFound = false;
                    if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                        //get a search set of all reference particles of that size
                        searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                        //For each particle in the reference set
                        for (int j = 0; j < searchSet.size(); j++) {
                            if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
                                productParticles[i]->setuID(
                                        concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
                                j = searchSet.size(); //jump out of the for loop
                                matchFound = true; // set match to true

                            }
                        }
                        if (!matchFound) //if the particle is new but the size has been seen before
                        {
                            UniqueSucess++;
                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //give it a unique id
                            productParticles[i]->setuID(
                                    concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


                            //put the new reference set for that size back in the unique particles reference set
                            uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

                            file.open(filePath + "DB_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                            std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                            file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                            for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                            {
                                file <<prettystructure[structIdx] << endl;
                            }
                            file << endl;

                            file.close();

                        }
                    } else { // if no particles of this size have been found insert a new pair into the map
                        UniqueSucess++;

                        //clone and add to refrence set
                        searchSet.push_back(productParticles[i]->clone());
                        searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                        //give it a unique id
                        productParticles[i]->setuID(
                                concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

                        //put particel in reference set
                        uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
                        file.open(filePath +"DB_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                        std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                        file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                        for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                        {
                            file <<prettystructure[structIdx] << endl;
                        }
                        file << endl;

                        file.close();
                    }
                    searchSet.clear();
                    matchFound = false;
                    productString = productString + " , " + productParticles[i]->GetuID();
                }
                //After bonding compare bonding property
                std::map<InteractionList*, int> noILChanged ;

                for(int i  = 0; i < allILs.size(); i++){

                    if ((ILvalues[i] - allILs[i]->GetBindingProperty(false)) != 0) {
                        noILChanged.emplace(std::make_pair(allILs[i], 1));

                    }else{
                        noILChanged.emplace(std::make_pair(allILs[i], 0));
                    }
                }

                int ilsChanged = 0;
                for(int i = 0; i < productParticles.size(); i++) {
                    partialILs = productParticles[i]->GetAllInteractionLists();
                    ilsChanged = 0;
                    for(int j  =0; j<partialILs.size(); j++){
                        ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                    }
                    ilChangeString.append(std::to_string(ilsChanged) + ", ");

                }
                ILvalues.clear();
                allILs.clear();
                partialILs.clear();
                file.open(filePath + "DB_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
                file << ilChangeString << "| ";
                file << aString << "," << bString << "-";
                file << productString << endl;
                file.close();
                ilChangeString.clear();
                productString.clear();

            } else { // if CC isn't met replace particleA and B randomly into the reactor
                rndIdx = rand() % Reactor.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleA; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back

                rndIdx = rand() % Reac.size(); //get rand index
                swapParticle = Reactor[rndIdx]; //take out particle at idx
                Reactor[rndIdx] = particleB; // replace with one product
                Reactor.push_back(swapParticle); // push back particle to back
            }

        } else { // if there are no interaction lists free replace A and B randomly.
            rndIdx = rand() % Reactor.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleA; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back

            rndIdx = rand() % Reac.size(); //get rand index
            swapParticle = Reactor[rndIdx]; //take out particle at idx
            Reactor[rndIdx] = particleB; // replace with one product
            Reactor.push_back(swapParticle); // push back particle to back
        }
    }
    std::vector<std::string> reacUids;
    for (int i = 0; i < Reactor.size(); i++)
    {
        reacUids.push_back(Reactor[i]->GetuID());
    }

    std::sort(reacUids.begin(), reacUids.end());

    file.open(filePath + "DB_Contents_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    std::string currentUid = reacUids[0];
    int count = 0;
    for (int i = 0; i < reacUids.size(); i++)
    {
        if(currentUid == reacUids[i]) {
            count++;
        }else
        {
            file << currentUid << " , " << count << endl;
            count = 1;
            currentUid = reacUids[i];
        }
    }
    file.close();

    for(auto v : Reactor)
    {
        v->DeepDelete();
        delete v;
    }
    std::vector<int> keys;
    for(auto v : uniqueParticles)
    {
        keys.push_back( v.first);

    }
    std::sort(keys.begin(), keys.end());
    int num_selected = 0;
    int key = 0;
    std::vector<Particle*> decantSet, decantCurrent;
    while(num_selected<40)
    {
        key = keys.back();
        keys.pop_back();
        decantCurrent = uniqueParticles[key];
        num_selected = num_selected + decantCurrent.size();
        decantSet.insert(decantSet.end(), decantCurrent.begin(), decantCurrent.end());
    }

    if(num_selected > 40){
        for(int removeNum = num_selected - 40; removeNum>0; removeNum--){
            decantSet.pop_back();
        }
    }

    CompositReactor(decantSet, reacNumber, runNumber);

    for(auto v : uniqueParticles)
    {
        for(auto p: v.second) {
            p->DeepDelete();
        }

    }
    uniqueParticles.clear();

}

void Exploration()
{
	srand(25355); //255
	int reactorNumber = 20;

	std::vector<bool> InitOne (12, true );
	RBN* rbnA;
	std::vector<Particle*> Reactor;
	std::vector<std::vector<Particle*> > ReactorSet;
	std::vector<std::vector<float> > ReactorResults;
	std::ofstream outfile;
	for(int j =0; j< reactorNumber; j++)
	{
		ReactorResults.push_back(std::vector<float>(24, 0));
	}
	int uID = 1;
	char name = 'A';
	for(int j =0; j< reactorNumber; j++)
	{
		for(int i =0; i< 20; i++)
		{
			rbnA = new RBN(12, 2, 12, InitOne, (name + i));
			rbnA->SetUniqueID(uID);
			uID++;
			Reactor.push_back(new Particle(rbnA));
		}
		ReactorSet.push_back(Reactor);
		Reactor.clear();
	}
	time_t total_start = time(0);
	for(int generation = 0; generation < 100; generation++)
	{
		for(int j =0; j< reactorNumber; j++)
		{
			outfile.open("Reactor_"+  std::to_string(j) + "Log.log", ios::app);
			outfile << "Generation " << generation << endl;
			outfile.close();
		}
		
		#pragma omp parallel for schedule(dynamic)
		for(int j =0; j< reactorNumber; j++)
		{
			std::string message = "Reactor ";
			message +=   std::to_string(j);
			message +=  " started \n";
		
			cout << message;
			if (generation == 99)
			{
				ReactorResults[j] = ReactorInstance(ReactorSet[j], j);

				outfile.open("Reactor_" + std::to_string(j) + "AtomicParticles.txt", ios::app);
				for(int n = 0;n < ReactorSet[j].size(); n++)
				{
					ReactorSet[j][n]->GetComponentRBNs()[0]->print_ToFile(outfile);
				}
				outfile.close();

			}else 
			{
				ReactorResults[j] = ReactorInstance(ReactorSet[j], -1);
			}
			message = "Reactor ";
			message +=   std::to_string(j);
			message +=  " Done \n";
			cout << message;

		}

	

		std::vector<pair<int, float> > C_Results;
		// ID - Rank
		std::map<int,int> C_Rank;
		std::vector<pair<int, float> > S_Results;
		// ID - Rank
		std::map<int,int> S_Rank;
		std::vector<pair<int, float> > St_Results;
		// ID - Rank
		std::map<int,int> St_Rank;
		std::vector<pair<int, float> > R_Results;
		// ID - Rank
		std::map<int,int> R_Rank;
		std::vector<std::map<int, float> > P_Results;
		std::vector<std::vector<std::pair<int, float> >> P_OrderedResults;
		//Rank - ID
		std::vector<std::map<int,int> > P_Rank;

		std::map<int,int> P_RankReactor;
		std::map<int, float> P_Reactor;
		for(int i = 0; i < ReactorResults.size() ; i++)
		{
			C_Results.push_back(pair<int, float>(i, ReactorResults[i][0])); 
			S_Results.push_back(pair<int, float>(i, ReactorResults[i][1])); 
			St_Results.push_back(pair<int, float>(i, ReactorResults[i][2])); 
			R_Results.push_back(pair<int, float>(i, ReactorResults[i][3])); 
		
			for(int j = 4; j < 24; j++)
			{
				P_Reactor.insert(pair<int, float>(j-4, ReactorResults[i][j])); 
			}
			P_Results.push_back(P_Reactor);
			P_OrderedResults.push_back(std::vector<std::pair<int, float> > (P_Reactor.begin(), P_Reactor.end() ) );
			P_Reactor.clear();

		}
		pair<int, float> thisPair;

		for(int i = 0; i < P_OrderedResults.size(); i++)
		{
			sort(P_OrderedResults[i].begin(), P_OrderedResults[i].end(), [=](pair<int, float>& a, pair<int, float>& b)
			{
			 return a.second > b.second;
			}
			);

			for(int j = 0; j < P_OrderedResults[i].size() ; j++)
			{
				P_RankReactor.insert(std::pair<int,int>(  j+1, P_OrderedResults[i][j].first ) );
			}
			P_Rank.push_back(P_RankReactor);
			P_RankReactor.clear();
		}

	

		sort(C_Results.begin(), C_Results.end(), [=](pair<int, float>& a, pair<int, float>& b)
		{
		 return a.second > b.second;
		}
		);

		for(int i = 0; i < C_Results.size() ; i++)
		{
			C_Rank.insert(std::pair<int,int>( C_Results[i].first, i+1  ) );
		}

		sort(S_Results.begin(), S_Results.end(), [=](pair<int, float>& a, pair<int, float>& b)
		{
		 return a.second > b.second;
		}
		);

		for(int i = 0; i < S_Results.size() ; i++)
		{
			S_Rank.insert(std::pair<int,int>(  S_Results[i].first , i+1  ) );
		}

		sort(St_Results.begin(), St_Results.end(), [=](pair<int, float>& a, pair<int, float>& b)
		{
		 return a.second > b.second;
		}
		);

		for(int i = 0; i < St_Results.size() ; i++)
		{
			St_Rank.insert(std::pair<int,int>(  St_Results[i].first, i+1   ) );
		}

		sort(R_Results.begin(), R_Results.end(), [=](pair<int, float>& a, pair<int, float>& b)
		{
		 return a.second > b.second;
		}
		);

		for(int i = 0; i < R_Results.size() ; i++)
		{
			R_Rank.insert(std::pair<int,int>(  R_Results[i].first, i+1   ) );
		}


		std::vector<float> fr (reactorNumber, 0.0);
		
		for(int i  = 0; i < reactorNumber  ; i++)
		{
			fr[i] = ( C_Rank[i] + S_Rank[i] + St_Rank[i] + R_Rank[i]);
			
			outfile.open("Reactor_"+  std::to_string(i) + ".csv", ios::app);
			outfile << ReactorResults[i][0] << "," << ReactorResults[i][1] << "," << ReactorResults[i][2] << "," << ReactorResults[i][3]<< "," ;
			for(int j = 25; j < 45; j++)
			{
				outfile << ReactorResults[i][j] << ",";
			}
			outfile << endl;
			outfile.close();
		}
		int bestIdx;
		bestIdx = std::min_element(fr.begin(),fr.end()) - fr.begin();
		std::vector<std::vector<float> > mut;
		for(int i  = 0; i < reactorNumber; i++)
		{
			mut.push_back(std::vector<float>(20, 0.0));
		}
		float r;
		int x;

		for(int i  = 0; i < reactorNumber; i++)
		{
			for(int j  = 0; j < 20; j++)
			{
				mut[i][j] = (float)fr[i]*(1.0/(P_Results[i][j] + 1.0));
				mut[i][j] = (mut[i][j] -0.19) /(80.0 - 0.19);
				r = ((float) rand() / (RAND_MAX));
				if(r <= mut[i][j] )
				{
					if (i != bestIdx)
					{
						outfile.open("Reactor_"+  std::to_string(i) + "Log.log", ios::app);
						outfile << "Mutated particle " << j << endl;
						outfile.close();
						ReactorSet[i][j]->DeepDelete();
						delete ReactorSet[i][j];
						rbnA = new RBN(12, 2, 12, InitOne, ('A' + j));
						rbnA->SetUniqueID(uID);
						ReactorSet[i][j] = new Particle(rbnA);
						uID++;
					}
				}
			}
		}

		bool Replaced = false;
		bool FoundDuplicate = false;
		int numberAttempted = 0;
		int Uid1, Uid2, Uid3, dupittr;
		std::vector<int> randOrder;
		for (int i=1; i<reactorNumber; ++i) randOrder.push_back(i);//To Reactor Number fix!!!!!!!!!!!!

		for(int i  = 0; i < reactorNumber; i++)
		{
			r = ((float) rand() / (RAND_MAX));
			if((r <= 0.05 )&& (i != bestIdx) )
			{
				
				std::random_shuffle(randOrder.begin(), randOrder.end());
				while (!Replaced && numberAttempted < 20)
				{
					Uid1 = ReactorSet[randOrder[numberAttempted]][P_Rank[randOrder[numberAttempted]][1]]->GetComponentRBNs()[0]->GetUniqueID();
					Uid2 = ReactorSet[randOrder[numberAttempted]][P_Rank[randOrder[numberAttempted]][2]]->GetComponentRBNs()[0]->GetUniqueID();
					Uid3 = ReactorSet[randOrder[numberAttempted]][P_Rank[randOrder[numberAttempted]][3]]->GetComponentRBNs()[0]->GetUniqueID();
					dupittr = 0;
					FoundDuplicate = false;
					while((!FoundDuplicate) && (dupittr < 20))
					{
						if(	ReactorSet[i][dupittr]->GetComponentRBNs()[0]->GetUniqueID() == Uid1 ||
							ReactorSet[i][dupittr]->GetComponentRBNs()[0]->GetUniqueID() == Uid2 ||
							ReactorSet[i][dupittr]->GetComponentRBNs()[0]->GetUniqueID() == Uid3)
						{
							FoundDuplicate = true;
						}
						dupittr++;
					}

					if ( !FoundDuplicate )
					{
						ReactorSet[i][P_Rank[i][19]]->DeepDelete();
						ReactorSet[i][P_Rank[i][18]]->DeepDelete();
						ReactorSet[i][P_Rank[i][20]]->DeepDelete();

						delete ReactorSet[i][P_Rank[i][19]];
						delete ReactorSet[i][P_Rank[i][18]];
						delete ReactorSet[i][P_Rank[i][20]];
						ReactorSet[i][P_Rank[i][19]] = ReactorSet[randOrder[numberAttempted]][P_Rank[randOrder[numberAttempted]][1]]->clone();
						ReactorSet[i][P_Rank[i][18]] = ReactorSet[randOrder[numberAttempted]][P_Rank[randOrder[numberAttempted]][2]]->clone();
						ReactorSet[i][P_Rank[i][20]] = ReactorSet[randOrder[numberAttempted]][P_Rank[randOrder[numberAttempted]][3]]->clone();
						ReactorSet[i][P_Rank[i][19]]->GetComponentRBNs()[0]->SetRBNSymbol('A' + P_Rank[i][19]);
						ReactorSet[i][P_Rank[i][18]]->GetComponentRBNs()[0]->SetRBNSymbol('A' + P_Rank[i][18]);
						ReactorSet[i][P_Rank[i][20]]->GetComponentRBNs()[0]->SetRBNSymbol('A' + P_Rank[i][20]);
						Replaced = true;
						outfile.open("Reactor_"+  std::to_string(i) + "Log.log", ios::app);
						outfile << "Replaced worse 3 with best 3 from reactor " << randOrder[numberAttempted] << endl;
						outfile.close();

					}
					else
					{
						Replaced = false;
						numberAttempted++;
						FoundDuplicate = false;
					}
				
		
				}
				numberAttempted = 0;
				Replaced = false;
			}
		}
	
	}
	
	for(auto v : ReactorSet)
	{
		for(auto p : v)
		{
			p->DeepDelete();
			delete p;
		}
	}

	double total_since_start = difftime( time(0), total_start);

	double total_minutes = total_since_start / 60;
	
	cout << "Total Time : " << total_minutes;

}


void testMemLeak()
{
	

	std::vector<bool> InitOne (12, true );


		
	Bond* possibleBondAB;
	Bond* possibleBondAC;
	Bond* possibleBondAD;

	std::vector<InteractionList*> ilAc;
	InteractionList* ilAc1;
	InteractionList* ilAc2;
	InteractionList* ilAc3;
	InteractionList* ilBc1;
	InteractionList* ilBc2;
	InteractionList* ilCc1;
	InteractionList* ilDc1;
	int check;
	Particle* particleAB;
	std::vector<Particle*> involvedParticles;
	std::vector<Bond*> bondsToBreak;

	std::vector<std::string> bondsExisting ;
	std::vector<std::string> bondsNew;
	for(int i =0 ; i < 1000000; i++)
	{

		Particle* testParticleA = new Particle(new RBN(12, 2, 12, InitOne, 'A'));
		Particle* testParticleB = new Particle(new RBN(12, 2, 12, InitOne, 'B'));
		Particle* testParticleC = new Particle(new RBN(12, 2, 12, InitOne, 'C'));
		Particle* testParticleD = new Particle(new RBN(12, 2, 12, InitOne, 'D'));
		
		
		ilAc = testParticleA->GetAllFreeInteractionLists();
		check = 0;
		for(int j=0; j< ilAc.size(); j++)
		{
			if((ilAc[j]->size() >= 2) && (check !=3))
			{
				if (check  == 0)
				{
					ilAc1 = ilAc[j];

					check = 1;
				} else if (check == 1)
				{
					ilAc2 = ilAc[j];
					
					check  = 2;
				} else
				{
					ilAc3 = ilAc[j];
					j = ilAc.size();
					check  = 3;
				}
			}
		}
		if (check  == 1 || check == 2)
		{
			delete testParticleA;
			delete testParticleB;
			delete testParticleC;
			delete testParticleD;
			continue;
		}

		ilAc.clear();
		ilAc = testParticleB->GetAllFreeInteractionLists();
		check = 0;
		for(int j=0; j< ilAc.size(); j++)
		{
			if((ilAc[j]->size() >= 2) && (check !=2))
			{
				if (check  == 0)
				{
					ilBc1 = ilAc[j];

					check = 1;
				} else
				{
					ilBc2 = ilAc[j];
					j = ilAc.size();
					check  = 2;
				}
			}
		}
		if (check  == 1)
		{
			delete testParticleA;
			delete testParticleB;
			delete testParticleC;
			delete testParticleD;
			continue;
		}

		possibleBondAB = new Bond(ilAc1, ilBc1, ilAc1->GetParentRBN(), ilBc1->GetParentRBN());

		involvedParticles.push_back(testParticleA);
		involvedParticles.push_back(testParticleB);

		particleAB = new Particle(involvedParticles, possibleBondAB);

		

		involvedParticles.clear();
		ilCc1 = testParticleC->GetFreeInteractionList();
		ilDc1 = testParticleD->GetFreeInteractionList();

		possibleBondAC = new Bond(ilBc2, ilCc1, ilAc2->GetParentRBN(), ilCc1->GetParentRBN());

		involvedParticles.push_back(particleAB);
		involvedParticles.push_back(testParticleC);

		particleAB = new Particle(involvedParticles, possibleBondAC);

		possibleBondAD = new Bond(ilAc3, ilDc1, ilAc3->GetParentRBN(), ilDc1->GetParentRBN());
		involvedParticles.clear();

		involvedParticles.push_back(particleAB);
		involvedParticles.push_back(testParticleD);

		particleAB = new Particle(involvedParticles, possibleBondAD);

		particleAB->BuildParticle();
		particleAB->CalculateParticle();
		
		involvedParticles = CheckStability(particleAB);
		



		involvedParticles.clear();


		bondsToBreak.push_back(possibleBondAC);
		bondsToBreak.push_back(possibleBondAB);
		bondsToBreak.push_back(possibleBondAD);
		involvedParticles = particleAB->BreakBonds(bondsToBreak);

		bondsExisting = involvedParticles[0]->GetPrettyName();
		


		
		cout << i <<"\n";
		involvedParticles.clear(); 
		delete particleAB;


	}
   
}

void MCExploration()
{
	std::string line;
	ifstream infile;
	std::vector<Particle*> Reactor;
	std::vector<std::vector<Particle*>> ReactorSet;
	std::vector<std::string> rbnFile;
	RBN* newRBN;
	for(int i =0; i<20; i++) {

		infile.open("Reactor_" + std::to_string(i) + "AtomicParticles.txt");
		int j = 0;
		int k = 0;
		while (std::getline(infile, line) ) {
			rbnFile.push_back(line);
			j++;
			if (j == 25)
			{
				newRBN = new RBN(rbnFile);
				newRBN->SetRBNSymbol('A' + k);
				Reactor.push_back(new Particle(newRBN));
				k++;
				j =0;
				rbnFile.clear();
			}
		}
		ReactorSet.push_back(Reactor);
		infile.close();
		Reactor.clear();
	}
    std::vector<int> selectReactors = {8, 0, 7, 2,18,13};
    #pragma omp parallel for schedule(dynamic)
	for(int i =0; i<selectReactors.size(); i++) {

        for(int j = 0; j <10; j++) {
            cout << "Reactor " << selectReactors[i] << " run "<< j<<" starting" << endl;
            DecantReactor(ReactorSet[selectReactors[i]], selectReactors[i], j);
        }
	}
}

void TestEquality()
{
    srand(6243);
    std::vector<bool> InitOne (12, true );
    std::vector<Particle*> involvedParticles;
    Particle* testParticleA = new Particle(new RBN(12, 2, 12, InitOne, 'A'));
    Particle* testParticleB = new Particle(new RBN(12, 2, 12, InitOne, 'B'));
    Particle* testParticleA2 = testParticleA->clone();
    Particle* testParticleA3 = testParticleA->clone();
    Particle* testParticleA4 = testParticleA->clone();
    Particle* testParticleA5 = testParticleA->clone();
    Particle* testParticleA6 = testParticleA->clone();

    // particle AB
    InteractionList* ilA = testParticleA->GetFreeInteractionList();
    InteractionList* ilB = testParticleB->GetFreeInteractionList();
    Bond* BondAB = new Bond(ilA, ilB, ilA->GetParentRBN(), ilB->GetParentRBN());
    involvedParticles.push_back(testParticleA);
    involvedParticles.push_back(testParticleB);
    Particle* testParticleAB = new Particle(involvedParticles, BondAB);

    involvedParticles.clear();

    //particle A3A4
    ilA = testParticleA3->GetFreeInteractionList();
    ilB = testParticleA4->GetFreeInteractionList();
    Bond* BondA3A4 = new Bond(ilA, ilB, ilA->GetParentRBN(), ilB->GetParentRBN());
    involvedParticles.push_back(testParticleA3);
    involvedParticles.push_back(testParticleA4);
    Particle* testParticleA3A4 = new Particle(involvedParticles, BondA3A4);

    involvedParticles.clear();

    //particle A5A6
    ilA = testParticleA5->GetFreeInteractionList();
    ilB = testParticleA6->GetFreeInteractionList();
    Bond* BondA5A6 = new Bond(ilA, ilB, ilA->GetParentRBN(), ilB->GetParentRBN());
    involvedParticles.push_back(testParticleA5);
    involvedParticles.push_back(testParticleA6);
    Particle* testParticleA5A6 = new Particle(involvedParticles, BondA5A6);
    Particle* cloneTest = testParticleA5A6->clone();

    if (*testParticleAB == *testParticleB){cout << "A == B True\n";}

    if (*testParticleAB == *testParticleAB){cout << "AB == AB True\n";}

    if (*testParticleA3A4 == *testParticleA3A4){cout << "A3A4 == A3A4 True\n";}
    if (*testParticleA5A6 == *testParticleA5A6){cout << "A5A6 == A5A6 True\n";}
    if (*testParticleA3A4 == *testParticleA5A6){cout << "A3A4 == A5A6 True\n";}
    if (*testParticleA3A4 == *testParticleA2){cout << "A3A4 == A2 True\n";}
    if (*cloneTest == *testParticleA5A6){cout << "clone == A5A6 True\n";}
}

void Excercise1(std::vector<float> values, string filename){
    ofstream file1;
    file1.open(filename, std::ios_base::app);
    for(vector<float>::const_iterator i = values.begin(); i != values.end(); ++i){
        file1 << *i << '\n';
    }
    file1.close();
}

void Excercise2(std::vector<int> values, string filename){
    ofstream file1;
    file1.open(filename, std::ios_base::app);
    for(vector<int>::const_iterator i = values.begin(); i != values.end(); ++i){
        file1 << *i << '\n';
    }
    file1.close();
}

void Excercise3(string filename, vector<int>::const_iterator v_begin, vector<int>::const_iterator v_end){
    ofstream file1;
    file1.open(filename, std::ios_base::app);
    for(vector<int>::const_iterator i = v_begin; i != v_end; ++i){
        file1 << *i << '\n';
    }
    file1.close();
}

void Excercise4(string filename){
    //only works for integer in file not for float in file
    ifstream file1;
    std::string line;
    int val;
    std::vector<int> vec;
    while (std::getline(file1, line))
    {
        std::istringstream ss(line);
        ss >> val; // you can catch an exception here to see if the value is int or not, and if not use float to read in the value in a different loop
        vec.push_back(val);
        // process pair (a,b)
    }

    for(vector<int>::reverse_iterator i = vec.rbegin(); i != vec.rend(); ++i){
        cout << *i << " , ";
    }
}

void ConstTemp(std::vector<Particle*> Reac, int reacNumber, int runNumber, int temp)
{
	std::vector<Particle*> involvedParticles, productParticles, Reactor;
	Particle* particleA, *particleB, *particleAB, *swapParticle;
	InteractionList* ilAc, *ilBc;
	Bond* possibleBond;
	std::string productString, aString, bString;
	std::vector<std::string> productStructure, bondsNew, bondsExisting;
	ofstream file;
	std::map<int, std::vector<Particle*>> uniqueParticles;
	std::map<int, std::vector<Particle*>>::iterator UPittr ;
    std::map<int, std::vector<Particle*>> decomposeList;
	std::vector<Particle*> initialSet, searchSet, decompAtTau;
	std::vector<int> ILvalues, decompTimePos;
	std::vector<InteractionList*> allILs, partialILs;
	std::string ilChangeString;
	int recordCounter, UniqueSucess;
	bool matchFound = false;
	std::string filePath = "/home/mike/Phd/Paper/Temp/Const/";
	int CC , rndIdx, tau;
	float CC_A, CC_B, probA, probB, probAB;
	file.open(filePath + "TC_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(temp)+ "_"+ std::to_string(runNumber), ios::app);
    std::vector<int> selectTemps = {0, 2730, 3276, 3882,4032,4095};
    int selectedTemp = 0;
	for(int i = 0; i< Reac.size(); i++)
	{
		initialSet.push_back(Reac[i]->clone());
		Reac[i]->CalculateParticle();
		file << Reac[i]->GetPrettyName()[0] << ";";
		allILs.clear();
		allILs = Reac[i]->GetAllInteractionLists();
		for (int k = 0; k < allILs.size(); k++){
			file << allILs[k]->GetBindingProperty(false) << ",";
		}
		file << endl;
		Reac[i]->setuID(concatNumbers(1, i + 1));
		for(int j =0; j <200; j++) {
			Reactor.push_back(Reac[i]->clone());

		}
	}
	file.close();
	uniqueParticles.emplace(1, initialSet);


	UniqueSucess = 0;
	random_shuffle(Reactor.begin(), Reactor.end());
	for(int i =0; i < Reactor.size(); i++){
		Reactor[i]->SetReactorPos(i);
	}
	recordCounter = 0;
	for(int attempt = 0; attempt<100000; attempt++) {

		recordCounter++;
		if (recordCounter == 10000){
			file.open(filePath+"TC_Sucesses_" + std::to_string(reacNumber) + "_"+ std::to_string(temp)+ "_"+  std::to_string(runNumber), ios::app);
			file << UniqueSucess << ',';
			file.close();
			file.open(filePath + "TC_Reactions_" + std::to_string(reacNumber) + "_"+  std::to_string(temp)+ "_"+ std::to_string(runNumber), ios::app);
			file << '--'<< endl;
			file.close();
			recordCounter = 0;
			UniqueSucess = 0;
		}


		involvedParticles.clear();
		particleA = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		particleB = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		aString = particleA->GetuID();
		bString = particleB->GetuID();
		particleA->CalculateParticleAtTemp(temp);
		particleB->CalculateParticleAtTemp(temp);


		ilAc = particleA->GetFreeInteractionList();
		ilBc = particleB->GetFreeInteractionList();
		if (ilAc != NULL && ilBc != NULL) {

			// Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
			CC = ilAc->GetBindingPropertyTemp() + ilBc->GetBindingPropertyTemp();
			//cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
			//cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
			if (CC == 0) {

				// Get all Interaction lists
				allILs = particleA->GetAllInteractionLists();
				partialILs = particleB->GetAllInteractionLists();
				allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
				partialILs.clear();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for(int i  = 0; i < allILs.size(); i++)                {
					ILvalues.push_back(allILs[i]->GetBindingPropertyTemp());
				}
                //Calculate the the new CC_A and B as binding propetrty over IL size
				CC_A = (float)ilAc->GetBindingPropertyTemp() / (float)ilAc->GetParticipentNodesIdx().size();
				CC_B = (float)ilBc->GetBindingPropertyTemp() / (float)ilBc->GetParticipentNodesIdx().size();
				//Calculate proabability as nodes >= CC
				probA = ilAc->GetNumberNodesWithLivelinessOver(CC_A)/(float)(ilAc->GetParticipentNodesIdx().size());
				probB = ilBc->GetNumberNodesWithLivelinessOver(CC_B)/(float)(ilBc->GetParticipentNodesIdx().size());
				//Calculate bonding probability as average prob between the two.
                probAB = (probB+probA)/2;
				productParticles.clear();
				if (probAB > rand()/RAND_MAX)
				{
					//Reaction is possible
                    possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                    involvedParticles.push_back(particleA);
                    involvedParticles.push_back(particleB);

                    // Create new composit particle
                    particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                    decompTimePos = particleA->GetDecompTimeAndPos();
					if (decompTimePos[0] != NULL){
						decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
					}
					decompTimePos = particleB->GetDecompTimeAndPos();
					if (decompTimePos[0] != NULL){
						decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
					}
                    delete particleA;
                    delete particleB;
					particleAB->CalculateParticleAtTemp(temp);
					//Temp Stability returns how long untill first bond decomposes, or -1 if stable
					particleAB->CalculateParticleAtTemp(temp);
                    tau = TempStability(particleAB);
					if(tau != -1){
						//If there is something to decompose it will decomp at attempt+tau
						//Get all particle which are to decompose then and add this one to the back
                        //cout << tau<< endl;

						decompAtTau = decomposeList[tau+attempt];
						decompAtTau.push_back(particleAB);
						particleAB->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                        decomposeList[tau+attempt] = decompAtTau;
					}
					productParticles.push_back(particleAB);

                    //For each product particle
                    for (int i = 0; i < productParticles.size(); i++) {
                        //put it randomly back in the reactor
                        rndIdx = rand() % Reactor.size(); //get rand index
						productParticles[i]->SetReactorPos(rndIdx);
                        swapParticle = Reactor[rndIdx]; //take out particle at idx
                        Reactor[rndIdx] = productParticles[i]; // replace with one product
                        Reactor.push_back(swapParticle); // push back particle to back
						swapParticle->SetReactorPos(Reactor.size()-1);//


                        //get a pointer to reference particles of that size
                        UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
                        searchSet.clear();
                        matchFound = false;
                        if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                            //get a search set of all reference particles of that size
                            searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                            //For each particle in the reference set
                            for (int j = 0; j < searchSet.size(); j++) {
                                if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
                                    productParticles[i]->setuID(
                                            concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
                                    j = searchSet.size(); //jump out of the for loop
                                    matchFound = true; // set match to true

                                }
                            }
                            if (!matchFound) //if the particle is new but the size has been seen before
                            {
                                UniqueSucess++;
                                //clone and add to refrence set
                                searchSet.push_back(productParticles[i]->clone());
                                searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                                //give it a unique id
                                productParticles[i]->setuID(
                                        concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


                                //put the new reference set for that size back in the unique particles reference set
                                uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

                                file.open(filePath + "TC_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(temp)+ "_"+  std::to_string(runNumber), ios::app);
                                std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                                file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                                for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                                {
                                    file <<prettystructure[structIdx] << endl;
                                }
                                file << endl;

                                file.close();

                            }
                        } else { // if no particles of this size have been found insert a new pair into the map
                            UniqueSucess++;

                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //give it a unique id
                            productParticles[i]->setuID(
                                    concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

                            //put particel in reference set
                            uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
                            file.open(filePath +"TC_Products_" + std::to_string(reacNumber) + "_"+ std::to_string(temp)+ "_"+  std::to_string(runNumber), ios::app);
                            std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                            file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                            for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                            {
                                file <<prettystructure[structIdx] << endl;
                            }
                            file << endl;

                            file.close();
                        }
                        searchSet.clear();
                        matchFound = false;
                        productString = productString + " , " + productParticles[i]->GetuID();
                    }
                    //After bonding compare bonding property
                    std::map<InteractionList*, int> noILChanged ;

                    for(int i  = 0; i < allILs.size(); i++){

                        if ((ILvalues[i] - allILs[i]->GetBindingPropertyTemp()) != 0) {
                            noILChanged.emplace(std::make_pair(allILs[i], 1));

                        }else{
                            noILChanged.emplace(std::make_pair(allILs[i], 0));
                        }
                    }

                    int ilsChanged = 0;
                    for(int i = 0; i < productParticles.size(); i++) {
                        partialILs = productParticles[i]->GetAllInteractionLists();
                        ilsChanged = 0;
                        for(int j  =0; j<partialILs.size(); j++){
                            ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                        }
                        ilChangeString.append(std::to_string(ilsChanged) + ", ");

                    }
                    ILvalues.clear();
                    allILs.clear();
                    partialILs.clear();
                    file.open(filePath + "TC_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(temp)+ "_"+  std::to_string(runNumber), ios::app);
                    file << ilChangeString << "| ";
                    file << aString << "," << bString << "-";
                    file << productString << endl;
                    file.close();
                    ilChangeString.clear();
                    productString.clear();
                }else { // if the probability doesn't work
                    rndIdx = rand() % Reactor.size(); //get rand index
                    particleA->SetReactorPos(rndIdx);
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = particleA; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size()-1);

                    rndIdx = rand() % Reac.size(); //get rand index
					particleB->SetReactorPos(rndIdx);
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = particleB; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size()-1);
                }
			} else { // if CC isn't met replace particleA and B randomly into the reactor
				rndIdx = rand() % Reactor.size(); //get rand index
				particleA->SetReactorPos(rndIdx);
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleA; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
				swapParticle->SetReactorPos(Reactor.size()-1);

				rndIdx = rand() % Reac.size(); //get rand index
				particleB->SetReactorPos(rndIdx);
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleB; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
				swapParticle->SetReactorPos(Reactor.size()-1);
			}

		} else { // if there are no interaction lists free replace A and B randomly.
			rndIdx = rand() % Reactor.size(); //get rand index
			particleA->SetReactorPos(rndIdx);
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleA; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
			swapParticle->SetReactorPos(Reactor.size()-1);

			rndIdx = rand() % Reac.size(); //get rand index
			particleB->SetReactorPos(rndIdx);
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleB; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
			swapParticle->SetReactorPos(Reactor.size()-1);
		}
	//Decompose particles at this time
		//cout << "Decomposing" << endl;
        ilChangeString.clear();
        productString.clear();

		for (int i = 0; i<decomposeList[attempt].size(); i++){
			if(decomposeList[attempt][i] != NULL) {
				productParticles.clear();
				aString = decomposeList[attempt][i]->GetuID();
				decomposeList[attempt][i]->CalculateParticleAtTemp(temp);
				allILs.clear();
				allILs = decomposeList[attempt][i]->GetAllInteractionLists();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for (int i = 0; i < allILs.size(); i++) {
					ILvalues.push_back(allILs[i]->GetBindingPropertyTemp());
				}

				productParticles = BreakUnstable(decomposeList[attempt][i]);

				for (int i = 0; i < productParticles.size(); i++) {
					productParticles[i]->CalculateParticleAtTemp(temp);
                    tau = TempStability(productParticles[i]);
					if(tau != -1){
						//If there is something to decompose it will decomp at attempt+tau
						//Get all particle which are to decompose then and add this one to the back
                        //cout << tau<< endl;

						decompAtTau = decomposeList[tau+attempt];
						decompAtTau.push_back(productParticles[i]);
						productParticles[i]->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                        decomposeList[tau+attempt] = decompAtTau;
					}
					//put it randomly back in the reactor
					rndIdx = rand() % Reactor.size(); //get rand index
					productParticles[i]->SetReactorPos(rndIdx);
					swapParticle = Reactor[rndIdx]; //take out particle at idx
					Reactor[rndIdx] = productParticles[i]; // replace with one product
					Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size() - 1);//

					//get a pointer to reference particles of that size
					UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
					searchSet.clear();
					matchFound = false;
					if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
						//get a search set of all reference particles of that size
						searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
						//For each particle in the reference set
						for (int j = 0; j < searchSet.size(); j++) {
							if (*(searchSet[j]) ==
								*(productParticles[i])) { //if the particle has already been discoverd
								productParticles[i]->setuID(
										concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
								j = searchSet.size(); //jump out of the for loop
								matchFound = true; // set match to true

							}
						}
						if (!matchFound) //if the particle is new but the size has been seen before
						{
							UniqueSucess++;
							//clone and add to refrence set
							searchSet.push_back(productParticles[i]->clone());
							searchSet.back()->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
							//give it a unique id
							productParticles[i]->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


							//put the new reference set for that size back in the unique particles reference set
							uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

							file.open(filePath + "TC_Products_" + std::to_string(reacNumber) + "_" + std::to_string(temp)+ "_"+
									  std::to_string(runNumber), ios::app);
							std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

							file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
							for (int structIdx = 0; structIdx < prettystructure.size(); structIdx++) {
								file << prettystructure[structIdx] << endl;
							}
							file << endl;

							file.close();

						}
					} else { // if no particles of this size have been found insert a new pair into the map
						UniqueSucess++;

						//clone and add to refrence set
						searchSet.push_back(productParticles[i]->clone());
						searchSet.back()->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
						//give it a unique id
						productParticles[i]->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

						//put particel in reference set
						uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
						file.open(filePath + "TC_Products_" + std::to_string(reacNumber) + "_" + std::to_string(temp)+ "_"+
								  std::to_string(runNumber),
								  ios::app);
						std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

						file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
						for (int structIdx = 0; structIdx < prettystructure.size(); structIdx++) {
							file << prettystructure[structIdx] << endl;
						}
						file << endl;

						file.close();
					}
					searchSet.clear();
					matchFound = false;
					productString = productString + " , " + productParticles[i]->GetuID();
				}
				//After bonding compare bonding property
				std::map<InteractionList *, int> noILChanged;

				for (int i = 0; i < allILs.size(); i++) {

					if ((ILvalues[i] - allILs[i]->GetBindingPropertyTemp()) != 0) {
						noILChanged.emplace(std::make_pair(allILs[i], 1));

					} else {
						noILChanged.emplace(std::make_pair(allILs[i], 0));
					}
				}

				int ilsChanged = 0;
				for (int i = 0; i < productParticles.size(); i++) {
					partialILs = productParticles[i]->GetAllInteractionLists();
					ilsChanged = 0;
					for (int j = 0; j < partialILs.size(); j++) {
						ilsChanged = ilsChanged + noILChanged[partialILs[j]];
					}
					ilChangeString.append(std::to_string(ilsChanged) + ", ");

				}
				ILvalues.clear();
				allILs.clear();
				partialILs.clear();
				file.open(filePath + "TC_Reactions_" + std::to_string(reacNumber) + "_" + std::to_string(temp)+ "_"+  std::to_string(runNumber),
						  ios::app);
				file << ilChangeString << "| ";
				file << aString << "-";
				file << productString << endl;
				file.close();
				ilChangeString.clear();
				productString.clear();
			}
		}
		for (int i = 0; i<decomposeList[attempt].size(); i++){
            if (decomposeList[attempt][i]!= NULL) {
				swapParticle = Reactor.back(); // grap particle at reactor back
				Reactor.pop_back(); // remove from reactiro
				Reactor[decomposeList[attempt][i]->GetReactorPos()] = swapParticle; // put in the position of particle to be deleted
				swapParticle->SetReactorPos(decomposeList[attempt][i]->GetReactorPos()); // update swaped particle position
				delete decomposeList[attempt][i];//delete decomp particle
			}
		}

	}
	std::vector<std::string> reacUids;
	for (int i = 0; i < Reactor.size(); i++)
	{
		reacUids.push_back(Reactor[i]->GetuID());
	}

	std::sort(reacUids.begin(), reacUids.end());

	file.open(filePath + "TC_Contents_" + std::to_string(reacNumber) + "_"+ std::to_string(temp)+ "_"+  std::to_string(runNumber), ios::app);
	std::string currentUid = reacUids[0];
	int count = 0;
	for (int i = 0; i < reacUids.size(); i++)
	{
		if(currentUid == reacUids[i]) {
			count++;
		}else
		{
			file << currentUid << " , " << count << endl;
			count = 1;
			currentUid = reacUids[i];
		}
	}
	file.close();

	for(auto v : Reactor)
	{
		v->DeepDelete();
		delete v;
	}

	for(auto v : uniqueParticles)
	{
		for(auto p: v.second) {
			p->DeepDelete();
		}

	}
	uniqueParticles.clear();

}
void VarTemp(std::vector<Particle*> Reac, int reacNumber, int runNumber, int temp)
{
	std::vector<Particle*> involvedParticles, productParticles, Reactor;
	Particle* particleA, *particleB, *particleAB, *swapParticle;
	InteractionList* ilAc, *ilBc;
	Bond* possibleBond;
	std::string productString, aString, bString;
	std::vector<std::string> productStructure, bondsNew, bondsExisting;
	ofstream file;
	std::map<int, std::vector<Particle*>> uniqueParticles;
	std::map<int, std::vector<Particle*>>::iterator UPittr ;
    std::map<int, std::vector<Particle*>> decomposeList;
	std::vector<Particle*> initialSet, searchSet, decompAtTau;
	std::vector<int> ILvalues, decompTimePos;
	std::vector<InteractionList*> allILs, partialILs;
	std::string ilChangeString;
	int recordCounter, UniqueSucess, tempCounter;
	bool matchFound = false;
	std::string filePath = "/home/mike/Phd/Paper/Temp/Var/";
	int CC , rndIdx, tau;
	float CC_A, CC_B, probA, probB, probAB;
	file.open(filePath + "TV_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
    std::vector<int> selectTemps = {0, 2730, 3276, 3882,4032,4095,0, 2730, 3276, 3882,4032,4095};
    int selectedTemp = 0;
	int decompTime, decompIdx;
	temp = selectTemps[selectedTemp];
	for(int i = 0; i< Reac.size(); i++)
	{
		initialSet.push_back(Reac[i]->clone());
		Reac[i]->CalculateParticle();
		file << Reac[i]->GetPrettyName()[0] << ";";
		allILs.clear();
		allILs = Reac[i]->GetAllInteractionLists();
		for (int k = 0; k < allILs.size(); k++){
			file << allILs[k]->GetBindingProperty(false) << ",";
		}
		file << endl;
		Reac[i]->setuID(concatNumbers(1, i + 1));
		for(int j =0; j <200; j++) {
			Reactor.push_back(Reac[i]->clone());

		}
	}
	file.close();
	uniqueParticles.emplace(1, initialSet);


	UniqueSucess = 0;
	random_shuffle(Reactor.begin(), Reactor.end());
	for(int i =0; i < Reactor.size(); i++){
		Reactor[i]->SetReactorPos(i);
	}
	recordCounter = 0;
	for(int attempt = 0; attempt<100000; attempt++) {

		recordCounter++;
		if (recordCounter == 8333 ){
			file.open(filePath+"TV_Sucesses_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber), ios::app);
			file << UniqueSucess << ',';
			file.close();
			file.open(filePath + "TV_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
			file << '--'<< endl;
			file.close();
			recordCounter = 0;
			UniqueSucess = 0;
			selectedTemp++;
			temp = selectTemps[selectedTemp];
            for(int reacId=0; reacId < Reactor.size(); reacId++){
				particleA = Reactor[reacId];
				decompTimePos = particleA->GetDecompTimeAndPos();
				particleA->CalculateParticleAtTemp(temp);
				tau = TempStability(particleA);
				if (tau != -1 && decompTimePos[0] != NULL){// particle from unstable to unstable
                    decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;

					decompAtTau = decomposeList[tau+attempt];
					decompAtTau.push_back(particleA);
					particleA->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
					decomposeList[tau+attempt] = decompAtTau;
				}else if (tau != -1){ // particle from stable to unstable
					decompAtTau = decomposeList[tau+attempt];
					decompAtTau.push_back(particleA);
					particleA->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
					decomposeList[tau+attempt] = decompAtTau;
				} else if (decompTimePos[0] != NULL){// particle from unstable to stabel
					decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
				}


			}
		}


		involvedParticles.clear();
		particleA = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		particleB = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		aString = particleA->GetuID();
		bString = particleB->GetuID();
		particleA->CalculateParticleAtTemp(temp);
		particleB->CalculateParticleAtTemp(temp);


		ilAc = particleA->GetFreeInteractionList();
		ilBc = particleB->GetFreeInteractionList();
		if (ilAc != NULL && ilBc != NULL) {

			// Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
			CC = ilAc->GetBindingPropertyTemp() + ilBc->GetBindingPropertyTemp();
			//cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
			//cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
			if (CC == 0) {

				// Get all Interaction lists
				allILs = particleA->GetAllInteractionLists();
				partialILs = particleB->GetAllInteractionLists();
				allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
				partialILs.clear();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for(int i  = 0; i < allILs.size(); i++)                {
					ILvalues.push_back(allILs[i]->GetBindingPropertyTemp());
				}
                //Calculate the the new CC_A and B as binding propetrty over IL size
				CC_A = (float)ilAc->GetBindingPropertyTemp() / (float)ilAc->GetParticipentNodesIdx().size();
				CC_B = (float)ilBc->GetBindingPropertyTemp() / (float)ilBc->GetParticipentNodesIdx().size();
				//Calculate proabability as nodes >= CC
				probA = ilAc->GetNumberNodesWithLivelinessOver(CC_A)/(float)(ilAc->GetParticipentNodesIdx().size());
				probB = ilBc->GetNumberNodesWithLivelinessOver(CC_B)/(float)(ilBc->GetParticipentNodesIdx().size());
				//Calculate bonding probability as average prob between the two.
                probAB = (probB+probA)/2;
				productParticles.clear();
				if (probAB > rand()/RAND_MAX)
				{
					//Reaction is possible
                    possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

                    involvedParticles.push_back(particleA);
                    involvedParticles.push_back(particleB);

                    // Create new composit particle
                    particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
                    decompTimePos = particleA->GetDecompTimeAndPos();
					if (decompTimePos[0] != NULL){
						decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
					}
					decompTimePos = particleB->GetDecompTimeAndPos();
					if (decompTimePos[0] != NULL){
						decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
					}
                    delete particleA;
                    delete particleB;
					particleAB->CalculateParticleAtTemp(temp);
					//Temp Stability returns how long untill first bond decomposes, or -1 if stable
					particleAB->CalculateParticleAtTemp(temp);
                    tau = TempStability(particleAB);
					if(tau != -1){
						//If there is something to decompose it will decomp at attempt+tau
						//Get all particle which are to decompose then and add this one to the back
                        //cout << tau<< endl;

						decompAtTau = decomposeList[tau+attempt];
						decompAtTau.push_back(particleAB);
						particleAB->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                        decomposeList[tau+attempt] = decompAtTau;
					}
					productParticles.push_back(particleAB);

                    //For each product particle
                    for (int i = 0; i < productParticles.size(); i++) {
                        //put it randomly back in the reactor
                        rndIdx = rand() % Reactor.size(); //get rand index
						productParticles[i]->SetReactorPos(rndIdx);
                        swapParticle = Reactor[rndIdx]; //take out particle at idx
                        Reactor[rndIdx] = productParticles[i]; // replace with one product
                        Reactor.push_back(swapParticle); // push back particle to back
						swapParticle->SetReactorPos(Reactor.size()-1);//


                        //get a pointer to reference particles of that size
                        UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
                        searchSet.clear();
                        matchFound = false;
                        if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
                            //get a search set of all reference particles of that size
                            searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
                            //For each particle in the reference set
                            for (int j = 0; j < searchSet.size(); j++) {
                                if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
                                    productParticles[i]->setuID(
                                            concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
                                    j = searchSet.size(); //jump out of the for loop
                                    matchFound = true; // set match to true

                                }
                            }
                            if (!matchFound) //if the particle is new but the size has been seen before
                            {
                                UniqueSucess++;
                                //clone and add to refrence set
                                searchSet.push_back(productParticles[i]->clone());
                                searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                                //give it a unique id
                                productParticles[i]->setuID(
                                        concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


                                //put the new reference set for that size back in the unique particles reference set
                                uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

                                file.open(filePath + "TV_Products_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber), ios::app);
                                std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                                file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                                for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                                {
                                    file <<prettystructure[structIdx] << endl;
                                }
                                file << endl;

                                file.close();

                            }
                        } else { // if no particles of this size have been found insert a new pair into the map
                            UniqueSucess++;

                            //clone and add to refrence set
                            searchSet.push_back(productParticles[i]->clone());
                            searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
                            //give it a unique id
                            productParticles[i]->setuID(
                                    concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

                            //put particel in reference set
                            uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
                            file.open(filePath +"TV_Products_" + std::to_string(reacNumber) +"_"+  std::to_string(runNumber), ios::app);
                            std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

                            file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
                            for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
                            {
                                file <<prettystructure[structIdx] << endl;
                            }
                            file << endl;

                            file.close();
                        }
                        searchSet.clear();
                        matchFound = false;
                        productString = productString + " , " + productParticles[i]->GetuID();
                    }
                    //After bonding compare bonding property
                    std::map<InteractionList*, int> noILChanged ;

                    for(int i  = 0; i < allILs.size(); i++){

                        if ((ILvalues[i] - allILs[i]->GetBindingPropertyTemp()) != 0) {
                            noILChanged.emplace(std::make_pair(allILs[i], 1));

                        }else{
                            noILChanged.emplace(std::make_pair(allILs[i], 0));
                        }
                    }

                    int ilsChanged = 0;
                    for(int i = 0; i < productParticles.size(); i++) {
                        partialILs = productParticles[i]->GetAllInteractionLists();
                        ilsChanged = 0;
                        for(int j  =0; j<partialILs.size(); j++){
                            ilsChanged = ilsChanged + noILChanged[partialILs[j]];
                        }
                        ilChangeString.append(std::to_string(ilsChanged) + ", ");

                    }
                    ILvalues.clear();
                    allILs.clear();
                    partialILs.clear();
                    file.open(filePath + "TV_Reactions_" + std::to_string(reacNumber) +"_"+  std::to_string(runNumber), ios::app);
                    file << ilChangeString << "| ";
                    file << aString << "," << bString << "-";
                    file << productString << endl;
                    file.close();
                    ilChangeString.clear();
                    productString.clear();
                }else { // if the probability doesn't work
                    rndIdx = rand() % Reactor.size(); //get rand index
                    particleA->SetReactorPos(rndIdx);
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = particleA; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size()-1);

                    rndIdx = rand() % Reac.size(); //get rand index
					particleB->SetReactorPos(rndIdx);
                    swapParticle = Reactor[rndIdx]; //take out particle at idx
                    Reactor[rndIdx] = particleB; // replace with one product
                    Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size()-1);
                }
			} else { // if CC isn't met replace particleA and B randomly into the reactor
				rndIdx = rand() % Reactor.size(); //get rand index
				particleA->SetReactorPos(rndIdx);
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleA; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
				swapParticle->SetReactorPos(Reactor.size()-1);

				rndIdx = rand() % Reac.size(); //get rand index
				particleB->SetReactorPos(rndIdx);
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleB; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
				swapParticle->SetReactorPos(Reactor.size()-1);
			}

		} else { // if there are no interaction lists free replace A and B randomly.
			rndIdx = rand() % Reactor.size(); //get rand index
			particleA->SetReactorPos(rndIdx);
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleA; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
			swapParticle->SetReactorPos(Reactor.size()-1);

			rndIdx = rand() % Reac.size(); //get rand index
			particleB->SetReactorPos(rndIdx);
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleB; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
			swapParticle->SetReactorPos(Reactor.size()-1);
		}
	//Decompose particles at this time
		//cout << "Decomposing" << endl;
        ilChangeString.clear();
        productString.clear();

		for (int i = 0; i<decomposeList[attempt].size(); i++){
			if(decomposeList[attempt][i] != NULL) {
				productParticles.clear();
				aString = decomposeList[attempt][i]->GetuID();
				decomposeList[attempt][i]->CalculateParticleAtTemp(temp);
				allILs.clear();
				allILs = decomposeList[attempt][i]->GetAllInteractionLists();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for (int i = 0; i < allILs.size(); i++) {
					ILvalues.push_back(allILs[i]->GetBindingPropertyTemp());
				}

				productParticles = BreakUnstable(decomposeList[attempt][i]);

				for (int i = 0; i < productParticles.size(); i++) {
					productParticles[i]->CalculateParticleAtTemp(temp);
                    tau = TempStability(productParticles[i]);
					if(tau != -1){
						//If there is something to decompose it will decomp at attempt+tau
						//Get all particle which are to decompose then and add this one to the back
                        //cout << tau<< endl;

						decompAtTau = decomposeList[tau+attempt];
						decompAtTau.push_back(productParticles[i]);
						productParticles[i]->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                        decomposeList[tau+attempt] = decompAtTau;
					}
					//put it randomly back in the reactor
					rndIdx = rand() % Reactor.size(); //get rand index
					productParticles[i]->SetReactorPos(rndIdx);
					swapParticle = Reactor[rndIdx]; //take out particle at idx
					Reactor[rndIdx] = productParticles[i]; // replace with one product
					Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size() - 1);//

					//get a pointer to reference particles of that size
					UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
					searchSet.clear();
					matchFound = false;
					if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
						//get a search set of all reference particles of that size
						searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
						//For each particle in the reference set
						for (int j = 0; j < searchSet.size(); j++) {
							if (*(searchSet[j]) ==
								*(productParticles[i])) { //if the particle has already been discoverd
								productParticles[i]->setuID(
										concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
								j = searchSet.size(); //jump out of the for loop
								matchFound = true; // set match to true

							}
						}
						if (!matchFound) //if the particle is new but the size has been seen before
						{
							UniqueSucess++;
							//clone and add to refrence set
							searchSet.push_back(productParticles[i]->clone());
							searchSet.back()->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
							//give it a unique id
							productParticles[i]->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


							//put the new reference set for that size back in the unique particles reference set
							uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

							file.open(filePath + "TV_Products_" + std::to_string(reacNumber) + "_"+
									  std::to_string(runNumber), ios::app);
							std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

							file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
							for (int structIdx = 0; structIdx < prettystructure.size(); structIdx++) {
								file << prettystructure[structIdx] << endl;
							}
							file << endl;

							file.close();

						}
					} else { // if no particles of this size have been found insert a new pair into the map
						UniqueSucess++;

						//clone and add to refrence set
						searchSet.push_back(productParticles[i]->clone());
						searchSet.back()->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
						//give it a unique id
						productParticles[i]->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

						//put particel in reference set
						uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
						file.open(filePath + "TV_Products_" + std::to_string(reacNumber) + "_"+
								  std::to_string(runNumber),
								  ios::app);
						std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

						file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
						for (int structIdx = 0; structIdx < prettystructure.size(); structIdx++) {
							file << prettystructure[structIdx] << endl;
						}
						file << endl;

						file.close();
					}
					searchSet.clear();
					matchFound = false;
					productString = productString + " , " + productParticles[i]->GetuID();
				}
				//After bonding compare bonding property
				std::map<InteractionList *, int> noILChanged;

				for (int i = 0; i < allILs.size(); i++) {

					if ((ILvalues[i] - allILs[i]->GetBindingPropertyTemp()) != 0) {
						noILChanged.emplace(std::make_pair(allILs[i], 1));

					} else {
						noILChanged.emplace(std::make_pair(allILs[i], 0));
					}
				}

				int ilsChanged = 0;
				for (int i = 0; i < productParticles.size(); i++) {
					partialILs = productParticles[i]->GetAllInteractionLists();
					ilsChanged = 0;
					for (int j = 0; j < partialILs.size(); j++) {
						ilsChanged = ilsChanged + noILChanged[partialILs[j]];
					}
					ilChangeString.append(std::to_string(ilsChanged) + ", ");

				}
				ILvalues.clear();
				allILs.clear();
				partialILs.clear();
				file.open(filePath + "TV_Reactions_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber),
						  ios::app);
				file << ilChangeString << "| ";
				file << aString << "-";
				file << productString << endl;
				file.close();
				ilChangeString.clear();
				productString.clear();
			}
		}
		for (int i = 0; i<decomposeList[attempt].size(); i++){
            if (decomposeList[attempt][i]!= NULL) {
				swapParticle = Reactor.back(); // grap particle at reactor back
				Reactor.pop_back(); // remove from reactiro
				Reactor[decomposeList[attempt][i]->GetReactorPos()] = swapParticle; // put in the position of particle to be deleted
				swapParticle->SetReactorPos(decomposeList[attempt][i]->GetReactorPos()); // update swaped particle position
				delete decomposeList[attempt][i];//delete decomp particle
			}
		}

	}
	std::vector<std::string> reacUids;
	for (int i = 0; i < Reactor.size(); i++)
	{
		reacUids.push_back(Reactor[i]->GetuID());
	}

	std::sort(reacUids.begin(), reacUids.end());

	file.open(filePath + "TV_Contents_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber), ios::app);
	std::string currentUid = reacUids[0];
	int count = 0;
	for (int i = 0; i < reacUids.size(); i++)
	{
		if(currentUid == reacUids[i]) {
			count++;
		}else
		{
			file << currentUid << " , " << count << endl;
			count = 1;
			currentUid = reacUids[i];
		}
	}
	file.close();

	for(auto v : Reactor)
	{
		v->DeepDelete();
		delete v;
	}

	for(auto v : uniqueParticles)
	{
		for(auto p: v.second) {
			p->DeepDelete();
		}

	}
	uniqueParticles.clear();

}
void CloseTemp(std::vector<Particle*> Reac, int reacNumber, int runNumber, int temp)
{
	std::vector<Particle*> involvedParticles, productParticles, Reactor;
	Particle* particleA, *particleB, *particleAB, *swapParticle;
	InteractionList* ilAc, *ilBc;
	Bond* possibleBond;
	std::string productString, aString, bString;
	std::vector<std::string> productStructure, bondsNew, bondsExisting;
	ofstream file;
	std::map<int, std::vector<Particle*>> uniqueParticles;
	std::map<int, std::vector<Particle*>>::iterator UPittr ;
	std::map<int, std::vector<Particle*>> decomposeList;
	std::vector<Particle*> initialSet, searchSet, decompAtTau;
	std::vector<int> ILvalues, decompTimePos;
	std::vector<InteractionList*> allILs, partialILs;
	std::string ilChangeString;
	int recordCounter, UniqueSucess, tempCounter;
	bool matchFound = false;
	std::string filePath = "/home/mike/Phd/Paper/Temp/Closed/";
	int CC , rndIdx, tau;
	float CC_A, CC_B, probA, probB, probAB;
	file.open(filePath + "Tcl_AtomicIL_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
	std::vector<int> selectTemps = {0, 2730, 3276, 3882,4032,4095,0, 2730, 3276, 3882,4032,4095};
	int selectedTemp = 0;
	int decompTime, decompIdx, totalILChange, totalSize;
	int tempPrev, tempCheck;
	float tempChange;
	for(int i = 0; i< Reac.size(); i++)
	{
		initialSet.push_back(Reac[i]->clone());
		Reac[i]->CalculateParticle();
		file << Reac[i]->GetPrettyName()[0] << ";";
		allILs.clear();
		allILs = Reac[i]->GetAllInteractionLists();
		for (int k = 0; k < allILs.size(); k++){
			file << allILs[k]->GetBindingProperty(false) << ",";
		}
		file << endl;
		Reac[i]->setuID(concatNumbers(1, i + 1));
		for(int j =0; j <200; j++) {
			Reactor.push_back(Reac[i]->clone());

		}
	}
	file.close();
	uniqueParticles.emplace(1, initialSet);


	UniqueSucess = 0;
	random_shuffle(Reactor.begin(), Reactor.end());
	for(int i =0; i < Reactor.size(); i++){
		Reactor[i]->SetReactorPos(i);
	}
	recordCounter = 0;
	tempCheck = 0;
	for(int attempt = 0; attempt<100000; attempt++) {

		recordCounter++;
		totalSize = 0;
		if (recordCounter == 10000 ){
			file.open(filePath+"Tcl_Sucesses_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber), ios::app);
			file << UniqueSucess << ',';
			file.close();
			file.open(filePath + "Tcl_Reactions_" + std::to_string(reacNumber) + "_"+ std::to_string(runNumber), ios::app);
			file << '--'<< endl;
			file.close();
			recordCounter = 0;
			UniqueSucess = 0;
		}
		tempCheck++;
		if(tempCheck==500){
			cout << attempt << endl;
            for(int reacId=0; reacId < Reactor.size(); reacId++){
                particleA = Reactor[reacId];
                decompTimePos = particleA->GetDecompTimeAndPos();
                particleA->CalculateParticleAtTemp(temp);
                tau = TempStability(particleA);
                if (tau != -1 && decompTimePos[0] != NULL){// particle from unstable to unstable
                    decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;

                    decompAtTau = decomposeList[tau+attempt];
                    decompAtTau.push_back(particleA);
                    particleA->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                    decomposeList[tau+attempt] = decompAtTau;
                }else if (tau != -1){ // particle from stable to unstable
                    decompAtTau = decomposeList[tau+attempt];
                    decompAtTau.push_back(particleA);
                    particleA->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                    decomposeList[tau+attempt] = decompAtTau;
                } else if (decompTimePos[0] != NULL){// particle from unstable to stabel
                    decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
                }


            }
            tempCheck=0;
		}

		involvedParticles.clear();
		particleA = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		particleB = Reactor.back(); //Grab particle from reactor
		Reactor.pop_back();
		aString = particleA->GetuID();
		bString = particleB->GetuID();
		particleA->CalculateParticleAtTemp(temp);
		particleB->CalculateParticleAtTemp(temp);


		ilAc = particleA->GetFreeInteractionList();
		ilBc = particleB->GetFreeInteractionList();
		if (ilAc != NULL && ilBc != NULL) {

			// Calculate the Collision Criterion PBP0(A) + PBP0(B) = 0
			CC = ilAc->GetBindingPropertyTemp() + ilBc->GetBindingPropertyTemp();
			//cout << "0A : " << PBP0A << " 1A : " << PBP1A << "\n";
			//cout << "0B : " << PBP0B << " 1B : " << PBP1B << "\n";
			if (CC == 0) {

				// Get all Interaction lists
				allILs = particleA->GetAllInteractionLists();
				partialILs = particleB->GetAllInteractionLists();
				allILs.insert(allILs.end(), partialILs.begin(), partialILs.end());
				partialILs.clear();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for(int i  = 0; i < allILs.size(); i++)                {
					ILvalues.push_back(allILs[i]->GetBindingPropertyTemp());
				}
				//Calculate the the new CC_A and B as binding propetrty over IL size
				CC_A = (float)ilAc->GetBindingPropertyTemp() / (float)ilAc->GetParticipentNodesIdx().size();
				CC_B = (float)ilBc->GetBindingPropertyTemp() / (float)ilBc->GetParticipentNodesIdx().size();
				//Calculate proabability as nodes >= CC
				probA = ilAc->GetNumberNodesWithLivelinessOver(CC_A)/(float)(ilAc->GetParticipentNodesIdx().size());
				probB = ilBc->GetNumberNodesWithLivelinessOver(CC_B)/(float)(ilBc->GetParticipentNodesIdx().size());
				//Calculate bonding probability as average prob between the two.
				probAB = (probB+probA)/2;
				productParticles.clear();
				if (probAB > rand()/RAND_MAX)
				{
					//Reaction is possible
					possibleBond = new Bond(ilAc, ilBc, ilAc->GetParentRBN(), ilBc->GetParentRBN()); //NewBond

					involvedParticles.push_back(particleA);
					involvedParticles.push_back(particleB);

					// Create new composit particle
					particleAB = new Particle(involvedParticles, possibleBond); //CompParticle
					decompTimePos = particleA->GetDecompTimeAndPos();
					if (decompTimePos[0] != NULL){
						decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
					}
					decompTimePos = particleB->GetDecompTimeAndPos();
					if (decompTimePos[0] != NULL){
						decomposeList[decompTimePos[0]][decompTimePos[1]] = NULL;
					}
					delete particleA;
					delete particleB;
					particleAB->CalculateParticleAtTemp(temp);
					totalSize = totalSize+ particleAB->GetParticleSize();
					//Temp Stability returns how long untill first bond decomposes, or -1 if stable
					particleAB->CalculateParticleAtTemp(temp);
					tau = TempStability(particleAB);
					if(tau != -1){
						//If there is something to decompose it will decomp at attempt+tau
						//Get all particle which are to decompose then and add this one to the back
						//cout << tau<< endl;

						decompAtTau = decomposeList[tau+attempt];
						decompAtTau.push_back(particleAB);
						particleAB->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
						decomposeList[tau+attempt] = decompAtTau;
					}
					productParticles.push_back(particleAB);

					//For each product particle
					for (int i = 0; i < productParticles.size(); i++) {
						//put it randomly back in the reactor
						rndIdx = rand() % Reactor.size(); //get rand index
						productParticles[i]->SetReactorPos(rndIdx);
						swapParticle = Reactor[rndIdx]; //take out particle at idx
						Reactor[rndIdx] = productParticles[i]; // replace with one product
						Reactor.push_back(swapParticle); // push back particle to back
						swapParticle->SetReactorPos(Reactor.size()-1);//


						//get a pointer to reference particles of that size
						UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
						searchSet.clear();
						matchFound = false;
						if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
							//get a search set of all reference particles of that size
							searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
							//For each particle in the reference set
							for (int j = 0; j < searchSet.size(); j++) {
								if (*(searchSet[j]) == *(productParticles[i])) { //if the particle has already been discoverd
									productParticles[i]->setuID(
											concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
									j = searchSet.size(); //jump out of the for loop
									matchFound = true; // set match to true

								}
							}
							if (!matchFound) //if the particle is new but the size has been seen before
							{
								UniqueSucess++;
								//clone and add to refrence set
								searchSet.push_back(productParticles[i]->clone());
								searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
								//give it a unique id
								productParticles[i]->setuID(
										concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


								//put the new reference set for that size back in the unique particles reference set
								uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

								file.open(filePath + "Tcl_Products_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber), ios::app);
								std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

								file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
								for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
								{
									file <<prettystructure[structIdx] << endl;
								}
								file << endl;

								file.close();

							}
						} else { // if no particles of this size have been found insert a new pair into the map
							UniqueSucess++;

							//clone and add to refrence set
							searchSet.push_back(productParticles[i]->clone());
							searchSet.back()->setuID(concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
							//give it a unique id
							productParticles[i]->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

							//put particel in reference set
							uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
							file.open(filePath +"Tcl_Products_" + std::to_string(reacNumber) +"_" + std::to_string(runNumber), ios::app);
							std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

							file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
							for(int structIdx = 0; structIdx < prettystructure.size(); structIdx++)
							{
								file <<prettystructure[structIdx] << endl;
							}
							file << endl;

							file.close();
						}
						searchSet.clear();
						matchFound = false;
						productString = productString + " , " + productParticles[i]->GetuID();
					}
					//After bonding compare bonding property
					std::map<InteractionList*, int> noILChanged ;
					totalILChange=0;
					for(int i  = 0; i < allILs.size(); i++){
                        totalILChange = totalILChange + abs(ILvalues[i]) - abs(allILs[i]->GetBindingPropertyTemp());
						if ((ILvalues[i] - allILs[i]->GetBindingPropertyTemp()) != 0) {
							noILChanged.emplace(std::make_pair(allILs[i], 1));

						}else{
							noILChanged.emplace(std::make_pair(allILs[i], 0));
						}
					}

					int ilsChanged = 0;
					for(int i = 0; i < productParticles.size(); i++) {
						partialILs = productParticles[i]->GetAllInteractionLists();
						ilsChanged = 0;
						for(int j  =0; j<partialILs.size(); j++){
							ilsChanged = ilsChanged + noILChanged[partialILs[j]];
						}
						ilChangeString.append(std::to_string(ilsChanged) + ", ");

					}
					ILvalues.clear();
					allILs.clear();
					partialILs.clear();
					file.open(filePath + "Tcl_Reactions_" + std::to_string(reacNumber) +"_"+  std::to_string(runNumber), ios::app);
					file << ilChangeString << "| ";
					file << aString << "," << bString << "-";
					file << productString << endl;
					file.close();
					ilChangeString.clear();
					productString.clear();
				}else { // if the probability doesn't work
					rndIdx = rand() % Reactor.size(); //get rand index
					particleA->SetReactorPos(rndIdx);
					swapParticle = Reactor[rndIdx]; //take out particle at idx
					Reactor[rndIdx] = particleA; // replace with one product
					Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size()-1);

					rndIdx = rand() % Reac.size(); //get rand index
					particleB->SetReactorPos(rndIdx);
					swapParticle = Reactor[rndIdx]; //take out particle at idx
					Reactor[rndIdx] = particleB; // replace with one product
					Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size()-1);
				}
			} else { // if CC isn't met replace particleA and B randomly into the reactor
				rndIdx = rand() % Reactor.size(); //get rand index
				particleA->SetReactorPos(rndIdx);
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleA; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
				swapParticle->SetReactorPos(Reactor.size()-1);

				rndIdx = rand() % Reac.size(); //get rand index
				particleB->SetReactorPos(rndIdx);
				swapParticle = Reactor[rndIdx]; //take out particle at idx
				Reactor[rndIdx] = particleB; // replace with one product
				Reactor.push_back(swapParticle); // push back particle to back
				swapParticle->SetReactorPos(Reactor.size()-1);
			}

		} else { // if there are no interaction lists free replace A and B randomly.
			rndIdx = rand() % Reactor.size(); //get rand index
			particleA->SetReactorPos(rndIdx);
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleA; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
			swapParticle->SetReactorPos(Reactor.size()-1);

			rndIdx = rand() % Reac.size(); //get rand index
			particleB->SetReactorPos(rndIdx);
			swapParticle = Reactor[rndIdx]; //take out particle at idx
			Reactor[rndIdx] = particleB; // replace with one product
			Reactor.push_back(swapParticle); // push back particle to back
			swapParticle->SetReactorPos(Reactor.size()-1);
		}
		//Decompose particles at this time
		//cout << "Decomposing" << endl;
		ilChangeString.clear();
		productString.clear();

		for (int i = 0; i<decomposeList[attempt].size(); i++){
			if(decomposeList[attempt][i] != NULL) {
				productParticles.clear();
				aString = decomposeList[attempt][i]->GetuID();
				decomposeList[attempt][i]->CalculateParticleAtTemp(temp);
                totalSize = totalSize+ decomposeList[attempt][i]->GetParticleSize();
				allILs.clear();
				allILs = decomposeList[attempt][i]->GetAllInteractionLists();
				ILvalues.clear();
				//Get IL values before bonding to be compared with values after bonding
				//to see if bonding resulted in meaningful change
				for (int i = 0; i < allILs.size(); i++) {
					ILvalues.push_back(allILs[i]->GetBindingPropertyTemp());
				}

				productParticles = BreakUnstable(decomposeList[attempt][i]);

				for (int i = 0; i < productParticles.size(); i++) {
					productParticles[i]->CalculateParticleAtTemp(temp);
                    tau = TempStability(productParticles[i]);
					if(tau != -1){
						//If there is something to decompose it will decomp at attempt+tau
						//Get all particle which are to decompose then and add this one to the back
                        //cout << tau<< endl;

						decompAtTau = decomposeList[tau+attempt];
						decompAtTau.push_back(productParticles[i]);
						productParticles[i]->SetDecompTimeAndPos(tau+attempt, decompAtTau.size()-1);
                        decomposeList[tau+attempt] = decompAtTau;
					}
					//put it randomly back in the reactor
					rndIdx = rand() % Reactor.size(); //get rand index
					productParticles[i]->SetReactorPos(rndIdx);
					swapParticle = Reactor[rndIdx]; //take out particle at idx
					Reactor[rndIdx] = productParticles[i]; // replace with one product
					Reactor.push_back(swapParticle); // push back particle to back
					swapParticle->SetReactorPos(Reactor.size() - 1);//

					//get a pointer to reference particles of that size
					UPittr = uniqueParticles.find(productParticles[i]->GetParticleSize());
					searchSet.clear();
					matchFound = false;
					if (UPittr != uniqueParticles.end()) { // check if particles of this size have been found before
						//get a search set of all reference particles of that size
						searchSet = uniqueParticles[productParticles[i]->GetParticleSize()];
						//For each particle in the reference set
						for (int j = 0; j < searchSet.size(); j++) {
							if (*(searchSet[j]) ==
								*(productParticles[i])) { //if the particle has already been discoverd
								productParticles[i]->setuID(
										concatNumbers(productParticles[i]->GetParticleSize(), j + 1));
								j = searchSet.size(); //jump out of the for loop
								matchFound = true; // set match to true

							}
						}
						if (!matchFound) //if the particle is new but the size has been seen before
						{
							UniqueSucess++;
							//clone and add to refrence set
							searchSet.push_back(productParticles[i]->clone());
							searchSet.back()->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
							//give it a unique id
							productParticles[i]->setuID(
									concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));


							//put the new reference set for that size back in the unique particles reference set
							uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;

							file.open(filePath + "Tcl_Products_" + std::to_string(reacNumber)+"_" +
									  std::to_string(runNumber), ios::app);
							std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

							file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
							for (int structIdx = 0; structIdx < prettystructure.size(); structIdx++) {
								file << prettystructure[structIdx] << endl;
							}
							file << endl;

							file.close();

						}
					} else { // if no particles of this size have been found insert a new pair into the map
						UniqueSucess++;

						//clone and add to refrence set
						searchSet.push_back(productParticles[i]->clone());
						searchSet.back()->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));
						//give it a unique id
						productParticles[i]->setuID(
								concatNumbers(productParticles[i]->GetParticleSize(), searchSet.size()));

						//put particel in reference set
						uniqueParticles[productParticles[i]->GetParticleSize()] = searchSet;
						file.open(filePath + "Tcl_Products_" + std::to_string(reacNumber) + "_"+
								  std::to_string(runNumber),
								  ios::app);
						std::vector<std::string> prettystructure = productParticles[i]->GetPrettyStruct();

						file << productParticles[i]->GetParticleSize() << ":" << searchSet.size() << endl;
						for (int structIdx = 0; structIdx < prettystructure.size(); structIdx++) {
							file << prettystructure[structIdx] << endl;
						}
						file << endl;

						file.close();
					}
					searchSet.clear();
					matchFound = false;
					productString = productString + " , " + productParticles[i]->GetuID();
				}
				//After bonding compare bonding property
				std::map<InteractionList *, int> noILChanged;

				for (int i = 0; i < allILs.size(); i++) {
                    totalILChange= totalILChange+abs(ILvalues[i]) - abs(allILs[i]->GetBindingPropertyTemp());
					if ((ILvalues[i] - allILs[i]->GetBindingPropertyTemp()) != 0) {
						noILChanged.emplace(std::make_pair(allILs[i], 1));

					} else {
						noILChanged.emplace(std::make_pair(allILs[i], 0));
					}
				}

				int ilsChanged = 0;
				for (int i = 0; i < productParticles.size(); i++) {
					partialILs = productParticles[i]->GetAllInteractionLists();
					ilsChanged = 0;
					for (int j = 0; j < partialILs.size(); j++) {
						ilsChanged = ilsChanged + noILChanged[partialILs[j]];
					}
					ilChangeString.append(std::to_string(ilsChanged) + ", ");

				}
				ILvalues.clear();
				allILs.clear();
				partialILs.clear();
				file.open(filePath + "Tcl_Reactions_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber),
						  ios::app);
				file << ilChangeString << "| ";
				file << aString << "-";
				file << productString << endl;
				file.close();
				ilChangeString.clear();
				productString.clear();
			}
		}
		for (int i = 0; i<decomposeList[attempt].size(); i++){
			if (decomposeList[attempt][i]!= NULL) {
				swapParticle = Reactor.back(); // grap particle at reactor back
				Reactor.pop_back(); // remove from reactiro
				Reactor[decomposeList[attempt][i]->GetReactorPos()] = swapParticle; // put in the position of particle to be deleted
				swapParticle->SetReactorPos(decomposeList[attempt][i]->GetReactorPos()); // update swaped particle position
				delete decomposeList[attempt][i];//delete decomp particle
			}
		}
        //Change temp accordingly.
		//-2^N+(2^(N+1))/1+e(-(totalSize/TotalReactor)*totalILChange)
		tempChange = (float(-4096)+(float(8192)/(1.0+exp(-((float(totalSize)/4000.0)*float(totalILChange))))));
		tempPrev = temp;
		temp = temp +tempChange;
		//cout << temp << endl;
		file.open(filePath + "Tcl_Temp_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber),
						  ios::app);
        file << temp << ", ";
        file.close();
		totalILChange = 0;
		totalSize = 0;

	}
	std::vector<std::string> reacUids;
	for (int i = 0; i < Reactor.size(); i++)
	{
		reacUids.push_back(Reactor[i]->GetuID());
	}

	std::sort(reacUids.begin(), reacUids.end());

	file.open(filePath + "Tcl_Contents_" + std::to_string(reacNumber) + "_"+  std::to_string(runNumber), ios::app);
	std::string currentUid = reacUids[0];
	int count = 0;
	for (int i = 0; i < reacUids.size(); i++)
	{
		if(currentUid == reacUids[i]) {
			count++;
		}else
		{
			file << currentUid << " , " << count << endl;
			count = 1;
			currentUid = reacUids[i];
		}
	}
	file.close();

	for(auto v : Reactor)
	{
		v->DeepDelete();
		delete v;
	}

	for(auto v : uniqueParticles)
	{
		for(auto p: v.second) {
			p->DeepDelete();
		}

	}
	uniqueParticles.clear();

}
void TempExploration()
{
	std::string line;
	ifstream infile;
	std::vector<Particle*> Reactor;
	std::vector<std::vector<Particle*>> ReactorSet;
	std::vector<std::string> rbnFile;
	RBN* newRBN;
	for(int i =0; i<20; i++) {

		infile.open("/home/mike/Documents/workspaceBACKUO/Build/Release/Reactor_" + std::to_string(i) + "AtomicParticles.txt");
		int j = 0;
		int k = 0;
		while (std::getline(infile, line) ) {
			rbnFile.push_back(line);
			j++;
			if (j == 25)
			{
				newRBN = new RBN(rbnFile);
				newRBN->SetRBNSymbol('A' + k);
				Reactor.push_back(new Particle(newRBN));
				k++;
				j =0;
				rbnFile.clear();
			}
		}
		ReactorSet.push_back(Reactor);
		infile.close();
		Reactor.clear();
	}
	std::vector<int> selectReactors = {8, 0, 7, 2,18,13};
	std::vector<int> selectTemps = {0, 2730, 3276, 3882,4032,4095};

//    #pragma omp parallel for schedule(dynamic)
//	for(int i =0; i<selectReactors.size(); i++) {
//
//		for(int j = 0; j <10; j++) {
//
//			for (int k =0; k<selectTemps.size();k++) {
//				cout << "Const Reactor " << selectReactors[i] <<" At Temp "<< selectTemps[k] << " run " << j << " starting" << endl;
//				ConstTemp(ReactorSet[selectReactors[i]], selectReactors[i], j, selectTemps[k]);
//			}
	//	}
	//}
//#pragma omp parallel for schedule(dynamic)
//	for(int i =0; i<selectReactors.size(); i++) {
//
//		for(int j = 0; j <10; j++) {
//
//			cout << "VarReactor " << selectReactors[i]  << " run " << j << " starting" << endl;
//			VarTemp(ReactorSet[selectReactors[i]], selectReactors[i], j, 0);
//		}
//	}
#pragma omp parallel for schedule(dynamic)
	for(int i =0; i<selectReactors.size(); i++) {

		for(int j = 0; j <10; j++) {

			cout << "CloseReactor " << selectReactors[i]  << " run " << j << " starting" << endl;
			CloseTemp(ReactorSet[selectReactors[i]], selectReactors[i], j, 2730);
		}
	}
}
int main(int argc, char *argv[])
{
    TempExploration();
	cout << "Done \n";
	//cin.get();

//thing

	
	//return 0;
}
