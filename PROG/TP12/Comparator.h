#ifndef _COMPARATOR_H
#define _COMPARATOR_H

#include "vehicule.h"

class Comparator
{
	public:
	//consructeur
	Comparator(bool sensTri = true);
	//destructeur
	virtual ~Comparator();
	//operateur ()
	bool operator()(const Vehicule* v1, const Vehicule* v2) const;
	
	protected:
	virtual bool compare (const Vehicule* v1, const Vehicule* v2) const = 0;
	bool ordre; ///< sens du tri du comparateur 
};

#endif
