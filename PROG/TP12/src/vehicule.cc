#include <iostream>
#include "vehicule.h"

//------------------------------------------------------------------------
// classe Vehicule
//------------------------------------------------------------------------

// constructeur
Vehicule::Vehicule(unsigned int lg, unsigned int nbp) : longueur(lg), passagers(nbp)
{}
// destructeur
Vehicule::~Vehicule(void)
{}

// longueur d'un véhicule
unsigned int Vehicule::getLongueur(void) const
{
	return longueur;
}

// nombre de personnes dans le véhicule
unsigned int Vehicule::getPassagers() const
{
	return passagers;
}

// opérateur d'affichage
std::ostream & operator << (std::ostream & sortie, const Vehicule & v)
{
	v.afficher(sortie);
	return sortie;
}

