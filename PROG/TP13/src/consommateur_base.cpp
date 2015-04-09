#include "consommateur_base.h"

/**
 * Initialise un consommateur de base
 * @param nbEntrees : le nombre d'entrées du consommateur
 */
consommateur_base::consommateur_base(unsigned int nbEntrees): _nbEntrees(nbEntrees), _entrees()
{
	for(unsigned int i=0; i < _nbEntrees; ++i)
	{
		counted_ptr<flot> flot(new impl_flot());
		_entrees.push_back(flot);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	virtual unsigned int nbEntrees() const = 0
/// \brief	Renvoie le nombre d'entrees du composant. 
/// \return	Le nombre d'entrees du composant. 
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int consommateur_base::nbEntrees() const
{
	return _nbEntrees;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	virtual const counted_ptr<flot> & getEntree(unsigned int numentree) const = 0
/// \brief	Récupération d'une entrée du composant. 
/// \param	numentree	Le numero de l'entrée à récuperer. 
/// \pre 0 <= numentree < nbEntrees()
/// \return	L'entrée demandée. 
////////////////////////////////////////////////////////////////////////////////////////////////////
const counted_ptr<flot> & consommateur_base::getEntree(unsigned int numentree) const
{
	assert(numentree<nbEntrees());
	return _entrees.at(numentree);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	virtual bool yaDesEchantillons() const = 0
/// \brief	déterminer si chaque entrée possède au moins un échantillon
/// \return	Vrai si chaque entrée possède au moins un échantillon.
////////////////////////////////////////////////////////////////////////////////////////////////////
bool consommateur_base::yaDesEchantillons() const
{
	return !_entrees.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	virtual void connecterEntree(const counted_ptr<flot> & f, unsigned int numentree) = 0
/// \brief	Connecte une entrée sur ce composant. 
/// \param	f		Le flot à connecter en entrée du composant. 
/// \param	numentree	Le numéro de l'entree sur laquelle connecter le flot.
/// \pre    0 <= numentree < nbEntrees()
////////////////////////////////////////////////////////////////////////////////////////////////////
void consommateur_base::connecterEntree(const counted_ptr<flot> & f, unsigned int numentree)
{
	assert(numentree < _nbEntrees);
	_entrees[numentree] = f;
}
