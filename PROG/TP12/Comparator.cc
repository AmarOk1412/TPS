#include "Comparator.h"
//constructeur
Comparator::Comparator(bool sensTri) : ordre(sensTri) { }
//destructeur
Comparator::~Comparator() { }

/**
 * Compare deux véhicules
 * @param:v1 un pointeur de véhicule
 * @param:v2 un pointeur de véhicule
 * @return:vrai si pour un critère donné, v1 est inférieur à v2, faux sinon 
 */
bool Comparator::operator()(const Vehicule* v1, const Vehicule* v2) const
{
	return ordre?compare(v1,v2):compare(v2,v1);
}
