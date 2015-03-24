#ifndef _COMPARERNOMBREPASSAGERS_H
#define _COMPARERNOMBREPASSAGERS_H

#include "vehicule.h"
#include "Comparator.h"

class ComparerNombrePassagers : public Comparator
{
	public:
	// constructeur
	ComparerNombrePassagers(bool sensTri = true);
	//destructeur
	~ComparerNombrePassagers();	
	
	protected:
	virtual bool compare (const Vehicule* v1, const Vehicule* v2) const;
};

#endif
