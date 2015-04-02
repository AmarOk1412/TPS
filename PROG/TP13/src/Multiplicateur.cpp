#include "Multiplicateur.h"

#include <iostream>
Multiplicateur::Multiplicateur() : filtre_base(2, 1)
{ }

void Multiplicateur::calculer()
{
	if(yaDesEchantillons()) _sorties[0]->inserer(_entrees[0]->extraire()*_entrees[1]->extraire());
}
