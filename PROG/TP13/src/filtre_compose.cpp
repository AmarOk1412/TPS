#include "filtre_compose.h"
#include <iostream>

/**
 * Initialise un filtre composé
 * @param nbEntrees : le nombre d'entrées du filtre
 * @param nBSorties : le nombre de sorties du filtre
*/
filtre_compose::filtre_compose
(unsigned int nbEntrees, unsigned int nbSorties) :
filtre_base(nbEntrees,nbSorties), _associations()
{ }


/**
 * @brief	Effectue les calculs associes au composant.
 */
void filtre_compose::calculer()
{
	if(yaDesEchantillons())
		for(unsigned int i = 0; i < _composants.size(); ++i)
			_composants[i]->calculer();
}
/**
 * Connecter deux composants entre eux
 * @param comp1 : un producteur 
 * @param numSortie : le numéro de sortie du producteur
 * @param comp2 : un consommateur
 * @param numEntree : le numéro d'entrée du consommateur
*/
void filtre_compose::connecter2Composants(counted_ptr<producteur> comp1, unsigned int numSortie,
	counted_ptr<consommateur> comp2, unsigned int numEntree)
{
	comp2->connecterEntree(comp1->getSortie(numSortie), numEntree);
}
/**
 * Connecter un flot à l'entrée d'un filtre composé
 * @param : f : un flot
 * @param numEntree : le numéro d'entrée du filtre
 */
void filtre_compose::connecterEntree(const counted_ptr<flot> &f, unsigned int numEntree)
{
  consommateur_base::connecterEntree(f, numEntree);
	if(_associations.count(numEntree) != 0)
	  _associations[numEntree].first->connecterEntree(f,_associations[numEntree].second);
}
/**
 * Connecter l'entrée du filtre composé à l'entrée d'un consommateur interne 
 * @param comp : un consommateur
 * @param numEntree : le numéro de l'entrée du filtre
 * @param numEntreeComp : le numéro de l'entrée du composant
*/
void filtre_compose::connecterEntreeInterne(counted_ptr<consommateur> comp, unsigned int numEntree, unsigned int numEntreeComp)
{
	_associations[numEntree] = std::pair<counted_ptr<consommateur>, unsigned int>(comp, numEntreeComp);
}
/**
 * Connecter la sortie d'un producteur interne à la sortie d'un filtre composé 
 * @param comp : un producteur 
 * @param numSortieComp : le numéro de la sortie du filtre
 * @param numSortie : le numéro de la sortie du producteur
*/
void filtre_compose::connecterSortieInterne(counted_ptr<producteur_base> comp, unsigned int numSortieComp, unsigned int numSortie)
{
  assert(numSortie < nbSorties());
	comp->connecterSortie(getSortie(numSortie), numSortieComp);
}
/**
 *  Ajouter un composant au filtre composé
 * @param comp : un composant
*/
void filtre_compose::ajouterComposant(counted_ptr<composant> comp)
{
	_composants.push_back(comp);
}


