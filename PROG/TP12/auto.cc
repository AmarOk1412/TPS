#include "auto.h"

Auto::Auto(unsigned int nbp, bool tT): Vehicule(2, nbp), longueur(2), passagers(nbp), toutTerrain(tT)
{}

Vehicule* Auto::Clone() const
{ 
	return new Auto(*this); 
} 

/// destructeur
Auto::~Auto(void)
{}

//! déterminer le tarif du véhicule
double	Auto::calculerTarif(void) const
{
	if(toutTerrain) return 350 + tarifPassager*passagers;
	return 100 + tarifPassager*passagers;
}

//! afficher les caractéristiques du véhicule
void	Auto::afficher(std::ostream & s) const
{
	s << "Auto - longueur : " << longueur << " - Nb de passagers : " << passagers << std::endl; 
}
