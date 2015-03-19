#include "ComparerLongueurVehicules.h"
//constructeur
ComparerLongueurVehicules::ComparerLongueurVehicules(bool sensTri): Comparator(sensTri)
{}
//destructeur
ComparerLongueurVehicules::~ComparerLongueurVehicules()
{}

/**
 * Compare la longueur de deux véhicules
 * @param:v1 un pointeur de véhicule
 * @param:v2 un pointeur de véhicule
 * @return: vrai si la longueur de v1 est inférieure ou égale 
 * à la longueur de v2, faux sinon
 */
bool ComparerLongueurVehicules::compare (const Vehicule* v1, const Vehicule* v2) const
{
	return v1->getLongueur()<v2->getLongueur();
}
