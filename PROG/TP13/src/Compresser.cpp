#include "Compresser.h"
#include <math.h>
#include <iostream>

/** 
 * Initialise un filtre qui compresse un flot 
 * @param taux : le taux de compression
*/
Compresser::Compresser(float taux) : filtre_base(1, 1), _taux(taux)
{ }

/**
 * @brief	Effectue les calculs associes au composant.
 */
void Compresser::calculer()
{
	if(yaDesEchantillons())
	{
		double val = _entrees[0]->extraire();
		double signe = -1.;
		if(val >= 0)
			signe = 1.;
		double value = signe*pow(sqrt(pow(val,2)), _taux);
		_sorties[0]->inserer(value);
	}
}
