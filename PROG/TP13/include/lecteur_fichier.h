#ifndef __LECTEUR_FICHIER__H__
#define __LECTEUR_FICHIER__H__

#include "producteur_base.h"
#include <fstream>

class lecteur_fichier : public producteur_base {
public:

	lecteur_fichier(std::string nom, unsigned int nbCanaux);
	
	virtual ~lecteur_fichier();
	void calculer();
	void ElectroSummerMixCalc();
	
private:
	std::string _nom;
	unsigned int _nbCanaux;
	std::ifstream _ifs;
};

#endif
