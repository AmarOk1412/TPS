
#ifndef __FILTRE_BASE__H__
#define __FILTRE_BASE__H__

#include "filtre.h"
#include "producteur_base.h"
#include "consommateur_base.h"

class filtre_base : public virtual filtre, public producteur_base, public consommateur_base {
public:
	filtre_base(unsigned int nbEntrees, unsigned int nbSorties);
	virtual ~filtre_base() {}
	virtual void calculer() = 0;
};

#endif
