#ifndef _COMPARERLONGUEURVEHICULES_H
#define _COMPARERLONGUEURVEHICULES_H

#include "vehicule.h"
#include "Comparator.h"

class ComparerLongueurVehicules : public Comparator
{
	public:
	ComparerLongueurVehicules(bool sensTri = true);
	~ComparerLongueurVehicules();
	virtual bool operator()(const Vehicule* v1, const Vehicule* v2) const;
	
	private:
	bool ordre;
};

#endif
