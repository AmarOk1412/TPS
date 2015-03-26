#include "harmonique.h"
#include <math.h>
harmonique::harmonique(unsigned int frequence, double phi): producteur_base(1), _freq(frequence), _dephasage(phi)
{}

unsigned int harmonique::nbSorties() const
{
	return _nbSorties;
}
/**
* @fn	const counted_ptr<flot> & getSortie(unsigned int numsortie) = 0
* @brief	Recupération d'une sortie du composant. 
* @param	numsortie	Le numero de la sortie a recuperer. 
* @pre 0 <= numsortie < nbSorties()
* @return	La sortie demandée. 
*/
const counted_ptr<flot> & harmonique::getSortie(unsigned int numsortie) const
{
	assert(numsortie<nbSorties());
	return _sorties->at(numsortie);
}

/**
 * @brief	Connecte une sortie sur ce composant. 
 * @param	f		Le flot à connecter en sortie du composant. 
 * @param	numsortie	Le numéro de la sortie sur laquelle connecter le flot.
 * @pre    0 <= numsortie < nbSorties()
 */
void harmonique::connecterSortie(const counted_ptr<flot> & f, unsigned int numsortie)
{
  assert(numsortie < nbSorties());
	_sorties->at(numsortie) = f;
}

void harmonique::calculer()
{
	unsigned int nb = nbSorties();
	for(unsigned int i = 0; i < nb; ++i)
	  getSortie(i)->inserer(sin(i/MixageSonore::frequency*2*MixageSonore::pi*_freq+_dephasage));
	
}
