#include<iostream>
#include<algorithm>
#include<windows.h>
#include<time.h>
#include<random>
#include<cstdlib>
#include"knapsack.h"
#include"define.h"
#include"info.h"
using namespace std;

SGenome& knapsack::RouletteWheelSelection()
{
	double fSlice = RandFloat() * m_dTotalFitnessScore;

	double cfTotal = 0.0;

	int	SelectedGenome = 0;

	for (int i = 0; i<m_iPopSize; ++i)
	{

		cfTotal += m_vecPopulation[i].fitness;

		if (cfTotal > fSlice)
		{
			SelectedGenome = i;
			break;
		}
	}
	
	return m_vecPopulation[SelectedGenome];
}

void knapsack::Mutate(vector<int> &vecBits)//IM
{
	if (RandFloat() > m_dMutationRate) return;

	//create an iterator for us to work with
	vector<int>::iterator curPos;

	//choose a gene to move
	curPos = vecBits.begin() + RandInt(0, vecBits.size() - 1);

	//keep a note of the genes value
	int items = *curPos;

	//remove from the chromosome
	vecBits.erase(curPos);

	//move the iterator to the insertion location
	curPos = vecBits.begin() + RandInt(0, vecBits.size() - 1);

	vecBits.insert(curPos, items);
}

void knapsack::Crossover(const vector<int> &mum,
	const vector<int> &dad,
	vector<int>		  &baby1,
	vector<int>		  &baby2)
{
	//just return parents as offspring dependent on the rate
	//or if parents are the same
	if ((RandFloat() > m_dCrossoverRate) || (mum == dad))
	{
		baby1 = mum;
		baby2 = dad;

		return;
	}

	//determine a crossover point
	int cp = RandInt(0, m_iChromoLength - 1);

	//swap the bits
	for (int i = 0; i<cp; ++i)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}

	for (int i = cp; i<mum.size(); ++i)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
}

void knapsack::Run()
{
	//The first thing we have to do is create a random population
	//of genomes
	CreateStartPopulation();
}

void knapsack::CreateStartPopulation()
{
	//clear existing population
	m_vecPopulation.clear();

	for (int i = 0; i<m_iPopSize; i++)
	{
		m_vecPopulation.push_back(SGenome(m_iChromoLength));

	}

	//reset all variables
	m_iGeneration = 0;
	m_iFittestGenome = 0;
	m_dBestFitnessScore = 0;
	m_dTotalFitnessScore = 0;
}
void knapsack::gamain() {
	clock_t ansbegin;
	ansbegin = clock();
	for (int i = 0; i < GENERATION_NUMBER; i++) {
		clock_t ansend;
		Epoch();
		ansend = clock();
		cout << "수행시간" << ((float)(ansend - ansbegin)) << "ms" << endl;
		
	}
	int weight = 0;
	int value = 0;
	for (int i = 0; i < CHROMO_LENGTH; i++) {
		if (m_vecPopulation[m_iFittestGenome].vecBag[i] == 1) {
			cout << i + 1 << " ";
			weight += item[0][i];
			value += item[1][i];
		}
	}

	cout << "weight: " << weight;
	cout << "value" << value << endl;
}
void knapsack::GrabNBest(int				      NBest,
	const int        NumCopies,
	vector<SGenome>	&vecNewPop)
{
	//first we need to sort our genomes
	
	sort(m_vecPopulation.begin(), m_vecPopulation.end());

	//now add the required amount of copies of the n most fittest 
	//to the supplied vector
	while (NBest--)
	{
		for (int i = 0; i<NumCopies; ++i)
		{
			vecNewPop.push_back(m_vecPopulation[(m_iPopSize - 1) - NBest]);
			//cout << "howmany";
		}
	}
}
void knapsack::Epoch()
{

	UpdateFitnessScores();
	printf("Best fitness[%d]: %f\n",m_iFittestGenome, m_dBestFitnessScore);
	cout << "generation" << m_iGeneration<<endl;
	//Now to create a new population
	int NewBabies = 0;

	//create some storage for the baby genomes 
	vector<SGenome> vecBabyGenomes;

	const int CopiesToAdd = 2;
	const int Nbest = 1;
	//if (!(CopiesToAdd*Nbest) % 2) {
		GrabNBest(Nbest, CopiesToAdd, vecBabyGenomes);
		NewBabies =NewBabies+2;
	//}
	
	while (NewBabies < m_iPopSize)
	{
		SGenome mum = RouletteWheelSelection();
		SGenome dad = RouletteWheelSelection();


		//operator - crossover
		SGenome baby1, baby2;
		Crossover(mum.vecBag, dad.vecBag, baby1.vecBag, baby2.vecBag);

		//operator - mutate
		Mutate(baby1.vecBag);
		Mutate(baby2.vecBag);

		//add to new population
		vecBabyGenomes.push_back(baby1);
		vecBabyGenomes.push_back(baby2);
		
		NewBabies += 2;
		
	}

	//copy babies back into starter population
	m_vecPopulation = vecBabyGenomes;

	//increment the generation counter
	++m_iGeneration;
	//return m_dBestFitnessScore;
}


double GetSumWeight(vector<int> &route)
{
	double Totalweight = 0;
	double Totalvalue = 0;
	int size = route.size();
	for (int i = 0; i<route.size() ; ++i)
	{
		if (route[i] == 1) {

			Totalweight = Totalweight + item[0][i];
			Totalvalue = Totalvalue + item[1][i];
			if (Totalweight > BAG_WEIGHT) {
				route.clear();
				for (int j = 0; j < size; j++) {
					route.push_back(RandInt(0, 1));
				}
				return GetSumWeight(route);
				///가방무게의 총합이 조건으로 주어진 가방무게보다 크면
				//벡터를 초기화 한 후에 다시 지정후 적합도 계산
			}
		}
	}
	return Totalvalue;
}


void knapsack::UpdateFitnessScores()
{
	m_iFittestGenome = 0;
	m_dBestFitnessScore = 0;
	m_dTotalFitnessScore = 0;

	//update the fitness scores and keep a check on fittest so far
	for (int i = 0; i<m_iPopSize; ++i)
	{
		//decode each genomes chromosome into a vector of directions
		double value = GetSumWeight(m_vecPopulation[i].vecBag);

		//get it's fitness score
		m_vecPopulation[i].fitness = value;
		
		//update total
		m_dTotalFitnessScore += m_vecPopulation[i].fitness;

		//if this is the fittest genome found so far, store results
		if (m_vecPopulation[i].fitness > m_dBestFitnessScore)
		{
			m_dBestFitnessScore = m_vecPopulation[i].fitness;

			m_iFittestGenome = i;
		}
		printf("fitness[%d]: %f Best fitness[%d]: %f\n", i, m_vecPopulation[i].fitness, m_iFittestGenome, m_dBestFitnessScore);
	}//next genome

}
