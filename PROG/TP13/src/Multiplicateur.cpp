#include "Multiplicateur.h"
/**
 * Initialise un multiplicateur 
*/
Multiplicateur::Multiplicateur() : filtre_base(2, 1)
{ }
/**
 * @brief	Effectue les calculs associes au composant.
 */
void Multiplicateur::calculer()
{
	if(yaDesEchantillons()) _sorties[0]->inserer(_entrees[0]->extraire()*_entrees[1]->extraire());
}
