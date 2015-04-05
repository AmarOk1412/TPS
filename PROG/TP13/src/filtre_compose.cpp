#include "filtre_compose.h"
#include <iostream>

filtre_compose::filtre_compose
(unsigned int nbEntrees, unsigned int nbSorties) :
filtre_base(nbEntrees,nbSorties), _associations()
{ }

void filtre_compose::calculer()
{
	if(yaDesEchantillons())
		for(unsigned int i = 0; i < _composants.size(); ++i)
			_composants[i]->calculer();
}

void filtre_compose::connecter2Composants(counted_ptr<producteur> comp1, unsigned int numSortie,
	counted_ptr<consommateur> comp2, unsigned int numEntree)
{
	comp2->connecterEntree(comp1->getSortie(numSortie), numEntree);
}

void filtre_compose::connecterEntree(const counted_ptr<flot> &f, unsigned int numEntree)
{
  consommateur_base::connecterEntree(f, numEntree);
	if(_associations.count(numEntree) != 0)
	  _associations[numEntree].first->connecterEntree(f,_associations[numEntree].second);
}

void filtre_compose::connecterEntreeInterne(counted_ptr<consommateur> comp, unsigned int numEntree, unsigned int numEntreeComp)
{
	_associations[numEntree] = std::pair<counted_ptr<consommateur>, unsigned int>(comp, numEntreeComp);
}

void filtre_compose::connecterSortieInterne(counted_ptr<producteur_base> comp, unsigned int numSortieComp, unsigned int numSortie)
{
  assert(numSortie < nbSorties());
	comp->connecterSortie(getSortie(numSortie), numSortieComp);
}

void filtre_compose::ajouterComposant(counted_ptr<composant> comp)
{
	_composants.push_back(comp);
}


