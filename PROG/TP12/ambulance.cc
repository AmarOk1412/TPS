#include "ambulance.h"

Ambulance::Ambulance(unsigned int nbp, bool tT): Auto(nbp, tT)
{}

/**
 * Clone un Vehicule
 * @return: Le Vehicule cloné
 */
Vehicule* Ambulance::Clone() const
{ 
	return new Ambulance(*this); 
} 

/// destructeur
Ambulance::~Ambulance(void)
{}

//! déterminer le tarif du véhicule
double	Ambulance::calculerTarif(void) const
{
	return 0;
}

//! afficher les caractéristiques du véhicule
void	Ambulance::afficher(std::ostream & s) const
{
	s << "Ambulance - longueur : " << longueur << " - Nb de passagers : " << passagers << std::endl; 
}
