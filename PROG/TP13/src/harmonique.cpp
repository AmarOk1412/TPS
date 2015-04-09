#include "harmonique.h"
#include <math.h>
#include "impl_flot.h"

/**
 * Initialise un producteur qui produit une harmonique
 * @param frequence
 * @param phi
*/
harmonique::harmonique(unsigned int frequence, double phi): producteur_base(1), _freq(frequence), _dephasage(phi), _i(0)
{ }
/**
 * @brief	Effectue les calculs associes au composant.
 */
void harmonique::calculer()
{
	_sorties[0]->inserer(sin((_i/(double)MixageSonore::frequency) * 2 * MixageSonore::pi * _freq + _dephasage));
	_i++;
}
