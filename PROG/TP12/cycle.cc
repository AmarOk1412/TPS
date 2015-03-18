#include "cycle.h"

Cycle::Cycle(): Vehicule(1, 1), longueur(1), passagers(1)
{}

Vehicule* Cycle::Clone() const
{ 
	return new Cycle(*this); 
} 

/// destructeur
Cycle::~Cycle(void)
{}

//! déterminer le tarif du véhicule
double	Cycle::calculerTarif(void) const
{
	return tarifPassager+20;
}

//! afficher les caractéristiques du véhicule
void	Cycle::afficher(std::ostream & s) const
{
	s << "Cycle - longueur : " << longueur << " - Nb de passagers : " << passagers << std::endl; 
}
