
#ifndef __FILTRE_COMPOSE__H__
#define __FILTRE_COMPOSE__H__

#include "filtre_base.h"
#include <vector>
#include <utility>
#include <map>

class filtre_compose : public filtre_base {
public:
	/**
	 * Initialise un filtre composé
	 * @param nbEntrees : le nombre d'entrées du filtre
	 * @param nBSorties : le nombre de sorties du filtre
	*/
	filtre_compose(unsigned int nbEntrees, unsigned int nbSorties);
	//destructeur
	virtual ~filtre_compose() { }
	//la méthode de calcul du filtre composé
	virtual void calculer();
	/**
	 * Connecter deux composants entre eux
	 * @param comp1 : un producteur 
	 * @param numSortie : le numéro de sortie du producteur
	 * @param comp2 : un consommateur
	 * @param numEntree : le numéro d'entrée du consommateur
	*/
	virtual void connecter2Composants(counted_ptr<producteur> comp1, unsigned int numSortie,
	counted_ptr<consommateur> comp2, unsigned int numEntree);
	/**
	 * Connecter l'entrée du filtre composé à l'entrée d'un consommateur interne 
	 * @param comp : un consommateur
	 * @param numEntree : le numéro de l'entrée du filtre
	 * @param numEntreeComp : le numéro de l'entrée du composant
	*/
	virtual void connecterEntreeInterne (counted_ptr<consommateur> comp, unsigned int numEntree, unsigned int numEntreeComp);
	/**
	 * Connecter un flot à l'entrée d'un filtre composé
	 * @param : f : un flot
	 * @param numEntree : le numéro d'entrée du filtre
	 */
	virtual void connecterEntree(const counted_ptr<flot> &f, unsigned int numEntree);
	/**
	 * Connecter la sortie d'un producteur interne à la sortie d'un filtre composé 
	 * @param comp : un producteur 
	 * @param numSortieComp : le numéro de la sortie du filtre
	 * @param numSortie : le numéro de la sortie du producteur
	*/
	virtual void connecterSortieInterne(counted_ptr<producteur_base> comp, unsigned int numSortieComp, unsigned int numSortie);
	/**
	 *  Ajouter un composant au filtre composé
	 * @param comp : un composant
	*/
	virtual void ajouterComposant(counted_ptr<composant> comp);
	
	
protected:
	std::vector<counted_ptr<composant>  > _composants;
	std::map<unsigned int, std::pair<counted_ptr<consommateur>, unsigned int> > _associations;
};

#endif
