//#include "vecteur.h"
#include "genericVector.h"

#include <iostream>
#include <string>

int main()
{	
	//Création de 3 vecteurs
	GenericVector<float>* v1 = new GenericVector<float>(4,2.);
//	GenericVector<float>* v1 = lireVecteur();
	afficherVecteur(v1);
	GenericVector<float>* v2 = new GenericVector<float>(4,2.);
//	GenericVector<float>* v2 = lireVecteur();
	afficherVecteur(v2);
	
	GenericVector<float> somme (*v1 + *v2);
		std::cout << somme << std::endl;
	delete v1;
	delete v2;	
	
	GenericVector<float> v3(4, 2.);
	return 0 ;
}
