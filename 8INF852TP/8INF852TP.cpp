
#include <iostream>
#include "Tools.h"
#include <algorithm>  
using namespace std;

void mutation(vector<SMSSDTSolution*>* SolutionsC, int N) {
	double a;
	int index1; int index2;
	for (int i = 0; i < SolutionsC->size(); i++) {
		a = ((double)rand()) / RAND_MAX;
		if (a>0.75) {

			index1 = rand() % N;
			do {
				index2 = rand() % N;
			} while (index1 == index2);

			(*SolutionsC)[i]->Solution[index1] = (*SolutionsC)[i]->Solution[index1] + (*SolutionsC)[i]->Solution[index2];
			(*SolutionsC)[i]->Solution[index2] = (*SolutionsC)[i]->Solution[index1] - (*SolutionsC)[i]->Solution[index2];
			(*SolutionsC)[i]->Solution[index1] = (*SolutionsC)[i]->Solution[index1] - (*SolutionsC)[i]->Solution[index2];

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
			else { e = 1;
			
			} 
			
			
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
	double Elapsed = 0;	//Variable servant à calculer le temps écoulé (Différence entre End et Start
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
		int mu = 100;
		int lambda =100;
		int k = 2;
		int indexP1, indexP2;

		// Création de la population
		vector<SMSSDTSolution*> SolutionsP;
		SolutionsP.resize(mu);

		for (int i = 0; i < mu; i++) {
			pSolution = new SMSSDTSolution(LeProb->getN(), true);
			if(i%2==0)
			desente(LeProb, pSolution, *pSolution);

			Tools::Evaluer(LeProb, *pSolution);
			SolutionsP[i] = pSolution;
		}


		for (int l = 0; l < 100; l++) {
			// Crossover
			vector<SMSSDTSolution*> SolutionsC;
			while (SolutionsC.size() < lambda) {
				indexP1 = (int)rand() % mu;
				do {
					indexP2 = (int)rand() % mu;
				} while (indexP1 == indexP2);
				
				
				crossOver2(LeProb, &SolutionsC, SolutionsP[indexP1]->Solution, SolutionsP[indexP2]->Solution);
					crossOver(&SolutionsC, SolutionsP[indexP1]->Solution, SolutionsP[indexP2]->Solution);
				/*
				// croisement 2
	crossOver2(LeProb, &SolutionsC, SolutionsP[indexP1]->Solution, SolutionsP[indexP2]->Solution);
				// croisement 3
				SMSSDTSolution* fils = NULL;
					fils =  new SMSSDTSolution(LeProb, *SolutionsP[indexP1], *SolutionsP[indexP2]);
				 SolutionsC.push_back(fils);*/
				
			}

			// Mutation
			
			//mutation(&SolutionsC, LeProb->getN());
			
			vector<SMSSDTSolution*> SolutionsT;
			SolutionsT.resize(mu + lambda);
			for (int i = 0; i < lambda; i++) {
				Tools::Evaluer(LeProb, *SolutionsC[i]);
				SolutionsT[i + mu] = SolutionsC[i];
			}
			for (int i = 0; i < mu; i++) SolutionsT[i] = SolutionsP[i];
			
			int index = rand() % (mu + lambda);
			
		
			for (int i = 0; i < mu; i++) SolutionsP.pop_back();
			for (int i = 0; i < mu +  lambda; i++)
			{
				for (int j = i+1; j < mu +  lambda; j++)
				{
					if (SolutionsT[i]->getObj() >SolutionsT[j]->getObj()) {
						swap(SolutionsT[i], SolutionsT[j]);

					}
				}
			}
			
			 
			int id = 0;
			
			while (SolutionsP.size() < mu) {
				
				desente(LeProb, SolutionsT[id], *SolutionsT[id]);
				SolutionsP.push_back(SolutionsT[id]);
				id++;
			}

			
		
		}

		for (int i = 0; i < mu; i++) {
			//Tools::Evaluer(LeProb, *SolutionsP[i]);
			for (int k = 0; k < LeProb->getN(); k++) {
				cout << SolutionsP[i]->Solution[k] << " ";
			}
			cout << "\t" << SolutionsP[i]->getObj() << endl;
		}
		cout << endl << endl;

		/**/

		SMSSDTSolution	Smeilleur(LeProb->getN());	//Sauvegarde de la meilleure solution
		for (int i = 0; i < 1000; i++)
		{
			pSolution = new SMSSDTSolution(LeProb->getN(), true);	//Une solution aléatoire
			Tools::Evaluer(LeProb, *pSolution);	//Évaluer la solution
			if (pSolution->getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
			{
				Smeilleur = *pSolution;
				dTheBestFitness = Smeilleur.getObj();
			}
			delete pSolution;
		}





		End = clock(); // Arrêter le clock
		Elapsed = (double(End - Start)) / CLOCKS_PER_SEC;	//Calculer le temps écoulé
		Tools::WriteReportLog(Elapsed, Smeilleur, LeProb->getNomFichier());	//Logguer le temps et la meilleure solution
		dTheBestFitness = 100000;

	}


	return 0;


}
