//#include "vecteur.h"
#include "genericVector.h"

int main()
{
  /**/
	//Création de 3 vecteurs	
  float type;
	GenericVector<float>* v1 = lireVecteur(type);
	afficherVecteur(v1);
	GenericVector<float>* v2 = lireVecteur(type);
	afficherVecteur(v2);
	
	GenericVector<float> somme (*v1 + *v2);
		std::cout << somme << std::endl;		
		
	float mul (*v1 * *v2);
		std::cout << mul << std::endl;
	delete v1;
	delete v2;	
	/**/
	/**/
	std::string type2;
	GenericVector<std::string>* v3 = lireVecteur(type2);
	afficherVecteur(v3);
	GenericVector<std::string>* v4 = lireVecteur(type2);
	afficherVecteur(v4);
	
	GenericVector<std::string> somme2 (*v3 + *v4);
		std::cout << somme2 << std::endl;
  std::cin >> somme2;
  std::cout << somme2 << std::endl;
	delete v3;
	delete v4;
	/**/
	/**/
	GenericVector<float> a(3, 1.13423);
	GenericVector<int> b(3,10);
	float mula(a*b);
	float mulb(b*a);	
	GenericVector<float> add(a+b);
	a = b;
	std::cout << mula << std::endl;	
	std::cout << mulb << std::endl;
	std::cout << add << std::endl;	
	std::cout << a << std::endl;
	/**/
	return 0 ;
}
