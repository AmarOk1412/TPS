#include "producteur_base.h"
#include "impl_flot.h"
#include <iostream>

producteur_base::producteur_base(unsigned int nbSorties) : producteur(), _nbSorties(nbSorties)
{
  for(unsigned int i = 0; i < nbSorties; ++i)
  {
  	impl_flot* f = new impl_flot();
		counted_ptr<flot> sortie(f);
    _sorties.push_back(sortie);
  }
}

unsigned int producteur_base::nbSorties() const
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
const counted_ptr<flot> & producteur_base::getSortie(unsigned int numsortie) const
{
	assert(numsortie<nbSorties());
	return _sorties.at(numsortie);
}

/**
 * @brief	Connecte une sortie sur ce composant. 
 * @param	f		Le flot à connecter en sortie du composant. 
 * @param	numsortie	Le numéro de la sortie sur laquelle connecter le flot.
 * @pre    0 <= numsortie < nbSorties()
 */
void producteur_base::connecterSortie(const counted_ptr<flot> & f, unsigned int numsortie)
{
  assert(numsortie < nbSorties());
	_sorties.at(numsortie) = f;
}

void producteur_base::calculer()
{ }
