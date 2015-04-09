#include "signal_constant.h"
#include "impl_flot.h"
#include <iostream>

/**
 * Initialise un producteur qui produit un signal constant
 * @param outVal
 */
signal_constant::signal_constant(double outVal) : producteur_base(1), _outVal(outVal)
{ }
//destructeur
signal_constant::~signal_constant() {}
/**
 * @brief	Effectue les calculs associes au composant.
 */
void signal_constant::calculer()
{
	_sorties.at(0)->inserer(_outVal);
}
