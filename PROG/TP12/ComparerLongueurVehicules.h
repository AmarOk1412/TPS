#ifndef _COMPARERLONGUEURVEHICULES_H
#define _COMPARERLONGUEURVEHICULES_H

#include "vehicule.h"

class ComparerLongueurVehicules
{
	public:
	ComparerLongueurVehicules(bool sensTri = true);
	~ComparerLongueurVehicules();
	bool operator()(const Vehicule* v1, const Vehicule* v2) const;
	
	private:
	bool ordre;
};

#endif
