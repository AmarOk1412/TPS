
#ifndef __FILTRE_COMPOSE__H__
#define __FILTRE_COMPOSE__H__

#include "filtre_base.h"
#include <vector>
#include <utility>
#include <map>

class filtre_compose : public filtre_base {
public:
	filtre_compose(std::vector<counted_ptr<composant> > composants, unsigned int nbEntrees, unsigned int nbSorties);
	virtual ~filtre_compose() { }
	virtual void calculer();
protected:
	virtual void connecter2Composants(counted_ptr<producteur> comp1, unsigned int numSortie,
	counted_ptr<consommateur> comp2, unsigned int numEntree);
	virtual void connecterEntreeInterne (counted_ptr<consommateur> comp, unsigned int numEntree, unsigned int numEntreeComp);
	virtual void connecterEntree(const counted_ptr<flot> &f, unsigned int numEntree);
	virtual void connecterSortieInterne(counted_ptr<producteur_base> comp, unsigned int numSortieComp, unsigned int numSortie);
	virtual void ajouterComposant(counted_ptr<composant> comp);
	
	
	std::vector<counted_ptr<composant>  > _composants;
	std::map<unsigned int, std::pair<counted_ptr<consommateur>, unsigned int> > _associations;
};

#endif
