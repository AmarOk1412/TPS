#ifndef __LECTEUR_FICHIER__H__
#define __LECTEUR_FICHIER__H__

#include "producteur_base.h"
#include <fstream>

class lecteur_fichier : public producteur_base {
public:
	/**
	 * Initialise un lecteur de fichier
	 * @param nbCanaux : le nombre de sorties 
	*/
	lecteur_fichier(std::string nom, unsigned int nbCanaux);
	
	//destructeur
	virtual ~lecteur_fichier();
	
	/**
	 * Calcule la valeur de l'échantillon en sortie
	*/
	void calculer();
	
	/**
	 * Calcule la valeur "Hit Summer" de l'échantillon
	*/
	void ElectroSummerMixCalc();
	
private:
	std::string _nom;
	unsigned int _nbCanaux;
	std::ifstream _ifs;
};

#endif
