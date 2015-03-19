#include "ComparerNombrePassagers.h"
//comparateur
ComparerNombrePassagers::ComparerNombrePassagers(bool sensTri): Comparator(sensTri)
{}
//destructeur
ComparerNombrePassagers::~ComparerNombrePassagers()
{}

/**
 * Compare le nombre de passagers entre deux véhicules
 * @param:v1 un pointeur de véhicule
 * @param:v2 un pointeur de véhicule
 * @return: vrai si le nombre de passagers de v1 est inférieur ou égal 
 * au nombre de passagers de v2, faux sinon
 */
bool ComparerNombrePassagers::compare (const Vehicule* v1, const Vehicule* v2) const
{
	return v1->getPassagers()<=v2->getPassagers();
}
