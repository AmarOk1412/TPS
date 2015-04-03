
#ifndef __FILTRE_COMPOSE__H__
#define __FILTRE_COMPOSE__H__

#include "filtre_bases.h"
#include <vector>

class filtre_compose : public filtre_base{
public:
	filtre_compose(std::vector<counted_ptr<composant> > filtres, unsigned int nbEntrees, unsigned int nbSorties);
	virtual ~filtre_compose();
	virtual void calculer();
	virtual void connecter2Composants(unsigned int numcomp1, unsigned int numcomp2);
	virtual void connecterEntreeInterne (unsigned int numentree, unsigned int numcomp);
	virtual void connecterSortieInterne (unsigned int numsortie, unsigned int numcomp);
private:
	std::vector<counted_ptr<composant>  > _filtres;
	std::map<unsigned int numcomp, 
	std::pair<counted_ptr<composant> compSortie, counted_ptr<composant> compEntree> > _associations;
};

#endif
