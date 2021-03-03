
#include <iostream>
#include <tuple>
#include "Tools.h"
#include <algorithm>  
using namespace std;

void mutation(vector<SMSSDTSolution*>* SolutionsC, int N) {
	double a;
	int index1; int index2;
	for (int i = 0; i < SolutionsC->size(); i++) {
		a = ((double)rand()) / RAND_MAX;
		if (a>0.66) {
			
			index1 = rand() % N;
			do {
				index2 = rand() % N;
			} while (index1 == index2);

			(*SolutionsC)[i]->Solution[index1] = (*SolutionsC)[i]->Solution[index1] + (*SolutionsC)[i]->Solution[index2];
			(*SolutionsC)[i]->Solution[index2] = (*SolutionsC)[i]->Solution[index1] - (*SolutionsC)[i]->Solution[index2];
			(*SolutionsC)[i]->Solution[index1] = (*SolutionsC)[i]->Solution[index1] - (*SolutionsC)[i]->Solution[index2];
			/*
			Tools::scrambleMove((*SolutionsC)[i]->Solution, (*SolutionsC)[i]->Solution, N, 4);
			*/
		}
	}

}

void crossOver(vector<SMSSDTSolution*>* SolutionsC, vector<int> P1, vector<int> P2) {
	int const N = P1.size();
	SMSSDTSolution* solutionC1 = new SMSSDTSolution(N);
	SMSSDTSolution* solutionC2 = new SMSSDTSolution(N);

	vector<int> E1;
	vector<int> E2;
	E1.resize(N);
	E2.resize(N);

	vector<int>  e1check(N);
	vector<int>  e2check(N);

	// choisir deux indices
	
	int i = (int)rand() % N;
	int j;
	do {
		j = (int)rand() % N;
	} while (i == j);



	// i doit tjrs moins que j
	if (i > j) {
		i = i + j;
		j = i - j;
		i = i - j;
	}
	
	//int i = N / 4;
	//int j = (3 * N) / 4; */


	int index1 = 0;
	int index2 = 0;
	int k;

	for (k = 0; k < i; k++) {
		if (e1check[P1[k]] == 1) {
			while (e1check[index1] == 1) index1++;
			E1[k] = index1;
			e1check[index1] = 1;
		}
		else {
			E1[k] = P1[k];
			e1check[P1[k]] = 1;
		}
		if (e2check[P2[k]] == 1) {
			while (e2check[index2] == 1) index2++;
			E2[k] = index2;
			e2check[index2] = 1;
		}
		else {
			E2[k] = P2[k];
			e2check[P2[k]] = 1;
		}
	}

	for (k = i; k < j; k++) {
		if (e1check[P2[k]] == 1) {
			while (e1check[index1] == 1) index1++;
			E1[k] = index1;
			e1check[index1] = 1;
		}
		else {
			E1[k] = P2[k];
			e1check[P2[k]] = 1;
		}
		if (e2check[P1[k]] == 1) {
			while (e2check[index2] == 1) index2++;
			E2[k] = index2;
			e2check[index2] = 1;
		}
		else {
			E2[k] = P1[k];
			e2check[P1[k]] = 1;
		}
	}
	for (k = j; k < N; k++) {
		if (e1check[P1[k]] == 1) {
			while (e1check[index1] == 1) index1++;
			E1[k] = index1;
			e1check[index1] = 1;
		}
		else {
			E1[k] = P1[k];
			e1check[P1[k]] = 1;
		}
		if (e2check[P2[k]] == 1) {
			while (e2check[index2] == 1) index2++;
			E2[k] = index2;
			e2check[index2] = 1;
		}
		else {
			E2[k] = P2[k];
			e2check[P2[k]] = 1;
		}
	}

	solutionC1->Solution = E1;
	solutionC2->Solution = E2;
	
	SolutionsC->push_back(solutionC1);
	SolutionsC->push_back(solutionC2);
}

void crossOver2(SMSSDTProblem* LeProb,vector<SMSSDTSolution*>* SolutionsC, vector<int> P1, vector<int> P2) {
	int const N = P1.size();
	SMSSDTSolution* solutionC1 = new SMSSDTSolution(N);
	SMSSDTSolution* solutionC2 = new SMSSDTSolution(N);

	vector<int> E1;
	vector<int> E2;
	E1.resize(N);
	E2.resize(N);

	vector<int>  e1check(N);
	vector<int>  e2check(N);

	// choisir deux indices

	int i = (int)rand() % N;
	int j;
	do {
		j = (int)rand() % N;
	} while (i == j);



	// i doit tjrs moins que j
	if (i > j) {
		i = i + j;
		j = i - j;
		i = i - j;
	}

	//int i = N / 4;
	//int j = (3 * N) / 4; */


	int index1 = 0;
	int index2 = 0;
	int k;

	for (k = 0; k < i; k++) {
		if (e1check[P1[k]] == 1) {
			while (e1check[index1] == 1) index1++;
			E1[k] = index1;
			e1check[index1] = 1;
			index1 = 0;
		}
		else {
			E1[k] = P1[k];
			e1check[P1[k]] = 1;
		}
		if (e2check[P2[k]] == 1) {
			while (e2check[index2] == 1) index2++;
			E2[k] = index2;
			e2check[index2] = 1;
			index2 = 0;
		}
		else {
			E2[k] = P2[k];
			e2check[P2[k]] = 1;
		}
	}
	int a = 0; int b = 0;
	vector <vector < int > > s = LeProb->getS();


	for (k = i; k < j-1; k++) {
		a += s[P1[i]][P1[i + 1]];
		b += s[P2[i]][P2[i + 1]];
	} 
	if (a < b) {
		for (k = i; k < j; k++) {
			if (e1check[P1[k]] == 1) {
				while (e1check[index1] == 1) index1++;
				E1[k] = index1;
				e1check[index1] = 1;
				index1 = 0;
			}
			else {
				E1[k] = P1[k];
				e1check[P1[k]] = 1;
			}


			if (e2check[P1[k]] == 1) {
				while (e2check[index2] == 1) index2++;
				E2[k] = index2;
				e2check[index2] = 1;
				index2 = 0;
			}
			else {
				E2[k] = P1[k];
				e2check[P1[k]] = 1;
			}
		}
	}
	else {


		for (k = i; k < j; k++) {
			if (e1check[P2[k]] == 1) {
				while (e1check[index1] == 1) index1++;
				E1[k] = index1;
				e1check[index1] = 1;
				index1 = 0;
			}
			else {
				E1[k] = P2[k];
				e1check[P2[k]] = 1;
			}


			if (e2check[P2[k]] == 1) {
				while (e2check[index2] == 1) index2++;
				E2[k] = index2;
				e2check[index2] = 1;
				index2 = 0;
			}
			else {
				E2[k] = P2[k];
				e2check[P2[k]] = 1;
			}
		}
	}



	for (k = j; k < N; k++) {
		if (e1check[P2[k]] == 1) {
			while (e1check[index1] == 1) index1++;
			E1[k] = index1;
			e1check[index1] = 1;
			index1 = 0;
		}
		else {
			E1[k] = P2[k];
			e1check[P2[k]] = 1;
		}
		if (e2check[P1[k]] == 1) {
			while (e2check[index2] == 1) index2++;
			E2[k] = index2;
			e2check[index2] = 1;
			index1 = 0;
		}
		else {
			E2[k] = P1[k];
			e2check[P1[k]] = 1;
		}
	}

	solutionC1->Solution = E1;
	solutionC2->Solution = E2;

	SolutionsC->push_back(solutionC1);
	SolutionsC->push_back(solutionC2);
}

void crossOver3(vector<SMSSDTSolution*>* SolutionsC, vector<int> P1, vector<int> P2) {
	int const N = P1.size();
	SMSSDTSolution* solutionC1 = new SMSSDTSolution(N);
	SMSSDTSolution* solutionC2 = new SMSSDTSolution(N);

	vector<int> E1;
	vector<int> E2;
	E1.resize(N);
	E2.resize(N);

	vector<int>  e1check(N);
	vector<int>  e2check(N);

	// choisir deux indices
	
	int i = (int)rand() % N;
	int j;
	do {
		j = (int)rand() % N;
	} while (i == j);



	// i doit tjrs moins que j
	if (i > j) {
		i = i + j;
		j = i - j;
		i = i - j;
	}
	/*
	int i = N / 4;
	int j = (3 * N) / 4; 
	*/
	int k;
	for (k = 0; k < i; k++) {
		if (e1check[P1[k]] == 1) {
			E1[k] = -1;
		}
		else {
			E1[k] = P1[k];
			e1check[P1[k]] = 1;
		}
		if (e2check[P2[k]] == 1) {
			E2[k] = -1;
		}
		else {
			E2[k] = P2[k];
			e2check[P2[k]] = 1;
		}
	}

	for (k = i; k < j; k++) {
		if (e1check[P2[k]] == 1) {
			E1[k] = -1;
		}
		else {
			E1[k] = P2[k];
			e1check[P2[k]] = 1;
		}
		if (e2check[P1[k]] == 1) {
			E2[k] = -1;
		}
		else {
			E2[k] = P1[k];
			e2check[P1[k]] = 1;
		}
	}

	for (k = j; k < N; k++) {
		if (e1check[P1[k]] == 1) {
			E1[k] = -1;
		}
		else {
			E1[k] = P1[k];
			e1check[P1[k]] = 1;
		}
		if (e2check[P2[k]] == 1) {
			E2[k] = -1;
		}
		else {
			E2[k] = P2[k];
			e2check[P2[k]] = 1;
		}
	}
	int index1 = 0;
	int index2 = 0;
	for (k = 0; k < N; k++) {
		if (E1[k] == -1) {
			while (e1check[index1] != 0) {
				index1++;
			}
			E1[k] = index1;
			e1check[index1] = 1;
		}
		if (E2[k] == -1) {
			while (e2check[index2] != 0) {
				index2++;
			}
			E2[k] = index2;
			e2check[index2] = 1;
		}
	}
	

	solutionC1->Solution = E1;
	solutionC2->Solution = E2;

	SolutionsC->push_back(solutionC1);
	SolutionsC->push_back(solutionC2);
}

vector< tuple<SMSSDTSolution*, SMSSDTSolution*>* >* roulette(vector<SMSSDTSolution*> population, int nombreEnfant)
{
	float sommeTotal = 0;
	vector< tuple<SMSSDTSolution*, SMSSDTSolution*>* > listeCoupleParent;

	//On fait la somme des fonction obj
	for (SMSSDTSolution* solution : population)
	{
		sommeTotal += 1 / (solution->getObj());	//Attention : solution->getObj() != 0
	}

	//On cree la liste de couple
	for (int i = 0; i < nombreEnfant; i++)
	{
		SMSSDTSolution* parent1;
		SMSSDTSolution* parent2;

		//On choisie le parent 1
		float nombreAleatoire = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (sommeTotal);	//On choisie aleatoirement un nombre entre 0 et sommeTotal
		float sommeProv = 0;
		int j = 0;
		do
		{
			sommeProv += 1 / (population[j]->getObj());
			j += 1;
		} while (sommeProv > nombreAleatoire);

		parent1 = population[j];

		//On choisie le parent 2
		nombreAleatoire = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (sommeTotal);	//On choisie aleatoirement un nombre entre 0 et sommeTotal
		sommeProv = 0;
		j = 0;
		do
		{
			sommeProv += 1 / (population[j]->getObj());
			j += 1;
		} while (sommeProv > nombreAleatoire);

		//Si les deux parents sont les meme
		if (population[j] == parent1)
		{
			if (j > 0)
			{
				j -= 1;
			}
			else
			{
				j += 1;
			}
		}
		
		parent2 = population[j];

		//On cree le couple
		tuple<SMSSDTSolution*, SMSSDTSolution*> couple;
		couple = make_tuple(parent1, parent2);
		listeCoupleParent.push_back(&couple);
	}

	return &listeCoupleParent;
}

void voi(SMSSDTSolution& Sol, SMSSDTProblem* LeProb) { // fonction qui parcours le voisinage 
	double	dTheBestFitness = 100000;
	SMSSDTSolution	Smeilleur(LeProb->getN());

	for (int i = 0; i < LeProb->getN(); i++) {

		for (int j = i + 1; j < LeProb->getN(); j++) {

			Sol.opt(LeProb->getN(), i, j);


			Tools::Evaluer(LeProb, Sol);

			if (Sol.getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
			{
				Smeilleur = Sol;
				dTheBestFitness = Smeilleur.getObj();

			}
			Sol.opt(LeProb->getN(), i, j);



		}
	}
	Sol = Smeilleur;
}

void voi2(SMSSDTSolution& Sol, SMSSDTProblem* LeProb) { // fonction qui parcours le voisinage 
	double	dTheBestFitness = 100000; 
	SMSSDTSolution	Smeilleur(LeProb->getN());
	SMSSDTSolution	voisins =(LeProb->getN());
	
	for (int i = 0; i < LeProb->getN() - 1; i++) {
		
		for (int j = i + 2; j < LeProb->getN() - 1; j++) {
			voisins = Sol;
			
			voisins.Solution[j] = Sol.Solution[i];
			voisins.Solution[j + 1] = Sol.Solution[i + 1];

			for (int k = i + 2; k < j +2; k++) {

				voisins.Solution[k - 2] = Sol.Solution[k];


			}
			

		


		Tools::Evaluer(LeProb, voisins);

		if (voisins.getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
		{
			Smeilleur = voisins;
			dTheBestFitness = Smeilleur.getObj();

		}
		
	
					
				
		 }
	}
	Sol = Smeilleur;
}



void voi3(SMSSDTSolution& Sol, SMSSDTProblem* LeProb) { // fonction qui parcours le voisinage 
	double	dTheBestFitness = 100000;
	SMSSDTSolution	Smeilleur(LeProb->getN());
	SMSSDTSolution	voisins = (LeProb->getN());

	for (int i = 0; i < LeProb->getN() - 2; i++) {

		for (int j = i + 3; j < LeProb->getN() - 2; j++) {
			voisins = Sol;

			voisins.Solution[j] = Sol.Solution[i];
			voisins.Solution[j + 1] = Sol.Solution[i + 1];
			
			voisins.Solution[j + 2] = Sol.Solution[i + 2];
			for (int k = i + 3; k < j + 3; k++) {

				voisins.Solution[k - 2] = Sol.Solution[k];


			}





			Tools::Evaluer(LeProb, voisins);

			if (voisins.getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
			{
				Smeilleur = voisins;
				dTheBestFitness = Smeilleur.getObj();

			}




		}
	}
	Sol = Smeilleur;
}

void desente(SMSSDTProblem* LeProb, SMSSDTSolution* pSolution, SMSSDTSolution	&Smeilleur) {

	int N = LeProb->getN();
	//sl.resize(N);
	double	dTheBestFitness = 100000;	//Fitness de la meilleure solution
		int e = 0;
		Tools::Evaluer(LeProb, *pSolution);	//Évaluer la solution
		dTheBestFitness = pSolution->getObj();
		while (e == 0) {
			SMSSDTSolution	sol(LeProb->getN());
			sol = *pSolution;
			voi(sol, LeProb);
			if (sol.getObj() < dTheBestFitness) // Si la meilleur sol du voisinage  améliore meilleure solution, la garder
			{
				*pSolution = sol;
				dTheBestFitness = pSolution->getObj();
				//sl.push_back(pSolution->getObj());
			}
			else { e = 1;} 
		}
		Smeilleur = *pSolution;
	
}

void shaking(SMSSDTProblem* LeProb, vector<int> const& solution, vector<int>& voisins, int mode) {
	switch (mode) {
	case 0:
		Tools::swapMove(solution, voisins, LeProb->getN());
		break;
	case 1:
		Tools::insertionMove(solution, voisins, LeProb->getN());
		break;
	case 2:
	
		Tools::EDDMove(solution, voisins, LeProb->getD(), LeProb->getN(), rand() % (LeProb->getN()));
		break;
	case 4:
		
		Tools::scrambleMove(solution, voisins, LeProb->getN(), rand() % (LeProb->getN()));
		break;
	case 5:
		Tools::inversionMove(solution, voisins, LeProb->getN(), rand() % (LeProb->getN()));
		
		break;
	}
}

int main(int argc, char* argv[])
{
	
	int amelioration = 0;
	srand(time(NULL));
	clock_t	Start, End;	//Déclaration de variable afin de calculer le temps écoulé
	double Elapsed = 0;	//Variable servant à calculer le temps écoulé (Différence entre End et Start)
	double	dTheBestFitness = 100000;	//Fitness de la meilleure solution
	SMSSDTProblem* LeProb;	//Déclaration d'un problème	
	LeProb = new SMSSDTProblem(argv[2]);	//Lecture du deuxi;eme paramètre à partir de la console
	//LeProb->printOn(cout);	// Imprimer le Problème
	
	SMSSDTSolution* pSolution = NULL;	//Solution intermédiaire
	SMSSDTSolution* fils = NULL;
	// argv[1] exécutions de la génération aléatoire
	for (int j = 0; j < atoi(argv[1]); j++)
	{
		Start = clock();	//Démarrer l'horloge	

		// Déclaration des paramètres
		int mu = 10; // le nombre de population
		int lambda = 10; // le nombre des enfants
		int k = 5; // le nombre de solution utilisé pour faire le tirage
		int nbiter = 200; // le nombre d'itération (nb de génération)
		int modeInit = 0; // 0 : la population initiale est aléatoire 1 : la population initiale est aléatoire + la moitié subie une descente
						  // 2 : la population initiale est aléatoire + toute la population subie une descente
		int modeCrossOver = 0; // 4 façons.
		int modeSelec = 2; // 0 : par tournoi avec remise. 1 : par tournoi sans remise. 2 : déterministe
		int indexP1, indexP2;
		
		// Création de la population
		vector<SMSSDTSolution*> population;
		population.resize(mu);
		for (int i = 0; i < mu; i++) {
			pSolution = new SMSSDTSolution(LeProb->getN(), true);
			switch (modeInit){
			case 1: if (i % 2 == 0) desente(LeProb, pSolution, *pSolution); break;
			case 2: desente(LeProb, pSolution, *pSolution); break;
			default:;
			}
			Tools::Evaluer(LeProb, *pSolution);
			population[i] = pSolution;
		}

		for (int l = 0; l < nbiter; l++) {
			
			// Crossover : le but est de générer des nouveux enfants à partir de la population ancienne pour cela on choisit deux 
			// solutions aléatoirement pour générer deux enfants (mode 0,1,2) ou un seul enfant (mode 3).
			vector<SMSSDTSolution*> populationC;
			while (populationC.size() < lambda) {
				indexP1 = (int)rand() % mu;
				do {
					indexP2 = (int)rand() % mu;
				} while (indexP1 == indexP2);
				
				switch (modeCrossOver){
				case 0: crossOver(&populationC, population[indexP1]->Solution, population[indexP2]->Solution); break;
				case 1: crossOver2(LeProb, &populationC, population[indexP1]->Solution, population[indexP2]->Solution); break;
				case 2: crossOver3(&populationC, population[indexP1]->Solution, population[indexP2]->Solution); break;
				case 3:
					fils = new SMSSDTSolution(LeProb, *population[indexP1], *population[indexP2]);
					populationC.push_back(fils);
					break;
				}
			}
			

			// Mutation : 
			mutation(&populationC, LeProb->getN());
			
			// stocker la population parent et la population enfant dans le même vecteur
			vector<SMSSDTSolution*> nvPopulation;
			nvPopulation.resize(mu + lambda);
			for (int i = 0; i < mu; i++) nvPopulation[i] = population[i];
			for (int i = 0; i < lambda; i++) {
				Tools::Evaluer(LeProb, *populationC[i]);
				nvPopulation[i + mu] = populationC[i];
			}
			
						
			// Sélection
			for (int i = 0; i < mu; i++) population.pop_back();
			
			vector<int> L; // ce vecteur pour la Séléction par tournoi sans remise
			switch (modeSelec){
			case 0: // Séléction par tournoi avec remise
				while (population.size() < mu) {
					int x = rand() % (mu + lambda);
					pSolution = nvPopulation[x];
					for (int i = 0; i < k; i++) {
						x = rand() % (mu + lambda);
						if (pSolution->getObj() > nvPopulation[x]->getObj()) {
							pSolution = nvPopulation[x];
						}
					}

					population.push_back(pSolution);
				}
				break;
			case 1: // Séléction par tournoi sans remise
				
				L.resize(mu + lambda);
				int x;
				int y;
				while (population.size() < mu) {
					do { x = rand() % (mu + lambda); } while (L[x] == 1);
					pSolution = nvPopulation[x];
					y = x;
					for (int i = 1; i < k; i++) {
						do { x = rand() % (mu + lambda); } while (L[x] == 1);
						if (pSolution->getObj() > nvPopulation[x]->getObj()) {
							pSolution = nvPopulation[x];
							y = x;
						}
					}
					population.push_back(pSolution);
					L[y] = 1;
				}
				break;
			case 2: // Séléction déterministe
				for (int i = 0; i < mu + lambda; i++)
				{
					for (int j = i + 1; j < mu + lambda; j++)
					{
						if (nvPopulation[i]->getObj() > nvPopulation[j]->getObj()) {
							swap(nvPopulation[i], nvPopulation[j]);
						}
					}
				}

				// Choisir 70% des (populations parents+populations enfants) et 30% des nouvelles solutions aléatoires
				int id = 0;
				while (population.size() < 0.7 * mu) {

					desente(LeProb, nvPopulation[id], *nvPopulation[id]);
					population.push_back(nvPopulation[id]);
					id++;
				}
				while (population.size() < mu) {
					pSolution = new SMSSDTSolution(LeProb->getN(), true);
					desente(LeProb, pSolution, *pSolution);
					Tools::Evaluer(LeProb, *pSolution);
					population.push_back(pSolution);

				}
				break;
			}
		}
		
		// Afficher toute la population
		/*
		for (int i = 0; i < mu; i++) {
			//Tools::Evaluer(LeProb, *SolutionsP[i]);
			for (int k = 0; k < LeProb->getN(); k++) {
				cout << SolutionsP[i]->Solution[k] << " ";
			}
			cout << "\t" << SolutionsP[i]->getObj() << endl;
		}
		cout << endl << endl;
		*/

		//Sauvegarde de la meilleure solution
		SMSSDTSolution	Smeilleur = *(population[0]);
		for (int i = 1; i < mu; i++) {
			if (population[i]->getObj() < Smeilleur.getObj()) {
				Smeilleur = *(population[i]);
			}
		}
	
		// Afficher la meilleure solution
		/*
		for (int i = 0; i < LeProb->getN(); i++) {
			cout << Smeilleur.Solution[i] << " ";
		}
		cout << "\t" << Smeilleur.getObj() << endl;
		*/

		End = clock(); // Arrêter le clock
		Elapsed = (double(End - Start)) / CLOCKS_PER_SEC;	//Calculer le temps écoulé
		Tools::WriteReportLog(Elapsed, Smeilleur, LeProb->getNomFichier());	//Logguer le temps et la meilleure solution
		dTheBestFitness = 100000;

	}


	return 0;


}
