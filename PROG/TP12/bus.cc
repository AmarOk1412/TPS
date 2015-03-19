#include "bus.h"

Bus::Bus(unsigned int l, unsigned int nbp): Vehicule(l,nbp)
{}

Vehicule* Bus::Clone() const
{ 
	return new Bus(*this); 
} 

/// destructeur
Bus::~Bus(void)
{}
//! déterminer le tarif du véhicule
double Bus::calculerTarif(void) const
{
	return 200 + 50*longueur + passagers*tarifPassager;
}

//! afficher les caractéristiques du véhicule
void	Bus::afficher(std::ostream & s) const
{
	s << "Bus - longueur : " << longueur << " - Nb de passagers : " << passagers << std::endl; 
}
