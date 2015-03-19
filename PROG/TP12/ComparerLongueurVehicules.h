#ifndef _COMPARERLONGUEURVEHICULES_H
#define _COMPARERLONGUEURVEHICULES_H

#include "vehicule.h"
#include "Comparator.h"

class ComparerLongueurVehicules : public Comparator
{
	public:
	//construteur
	ComparerLongueurVehicules(bool sensTri = true);
	//destructeur
	~ComparerLongueurVehicules();
	
	protected:
	virtual bool compare (const Vehicule* v1, const Vehicule* v2) const;
};

#endif
