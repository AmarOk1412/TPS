#include "ComparerLongueurVehicules.h"

ComparerLongueurVehicules::ComparerLongueurVehicules(bool sensTri):ordre(sensTri)	
{}

ComparerLongueurVehicules::~ComparerLongueurVehicules()
{}

bool ComparerLongueurVehicules::operator()(const Vehicule* v1, const Vehicule* v2) const
{
	return ordre?v1->getLongueur()<v2->getLongueur():v1->getLongueur()>=v2->getLongueur();
}
