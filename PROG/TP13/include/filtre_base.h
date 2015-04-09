
#ifndef __FILTRE_BASE__H__
#define __FILTRE_BASE__H__

#include "filtre.h"
#include "producteur_base.h"
#include "consommateur_base.h"

class filtre_base : public virtual filtre, public producteur_base, public consommateur_base {
public:
	/**
	 * Initialise un filtre de base
	 * @param nbEntrees : le nombre d'entrées du filtre 
	 * @param nbSorties : le nombre de sorties du filtre
	*/
	filtre_base(unsigned int nbEntrees, unsigned int nbSorties);
	//destructeur
	virtual ~filtre_base() {}
	//La méthode calculer
	virtual void calculer() = 0;
};

#endif
