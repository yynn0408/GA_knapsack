#ifndef KNAPSACK_H
#define KNAPSACK_H
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<sstream>
#include"utils.h"
using namespace std;


struct SGenome {
	double fitness;
	vector<int>vecBag;

	SGenome() :fitness(0) {}

	SGenome(const int num_bits) :fitness(0)
	{
		//create a random bit string
		for (int i = 0; i<num_bits; ++i)
		{
			vecBag.push_back(RandInt(0, 1));
			printf("%d", vecBag[i]);
		}
		printf("\n");
	}

	friend bool operator<(const SGenome& lhs, const SGenome& rhs)
	{
		return (lhs.fitness < rhs.fitness);
	}
};

class knapsack {
private:
	vector<SGenome>		m_vecPopulation;

	//size of population
	int             m_iPopSize;

	double          m_dCrossoverRate;

	double          m_dMutationRate;

	//how many bits per chromosome
	int             m_iChromoLength;

	//how many bits per gene
	int             m_iGeneLength;

	int             m_iFittestGenome;

	double          m_dBestFitnessScore;

	double          m_dTotalFitnessScore;

	int             m_iGeneration;


	void        Mutate(vector<int> &vecBits);

	void        Crossover(const vector<int>	&mum,
		const vector<int> &dad,
		vector<int>       &baby1,
		vector<int>       &baby2);

	SGenome&		RouletteWheelSelection();

	void			  UpdateFitnessScores();

	void			  CreateStartPopulation();

	void GrabNBest(int				      NBest,
		const int        NumCopies,
		vector<SGenome>	&vecNewPop);

public :
	knapsack(double cross_rat,
		double mut_rat,
		int    pop_size,
		int    num_bits,
		int    gene_len) :m_dCrossoverRate(cross_rat),
		m_dMutationRate(mut_rat),
		m_iPopSize(pop_size),
		m_iChromoLength(num_bits),
		m_dTotalFitnessScore(0.0),
		m_iGeneration(0),
		m_iGeneLength(gene_len)	

	{
		CreateStartPopulation();
	}

	void			Epoch();

	void			gamain();

	void			Run();

	//accessor methods
	int				Generation() { return m_iGeneration; }
	int				GetFittest() { return m_iFittestGenome; }
	
};





#endif