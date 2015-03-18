#ifndef _COMPARERNOMBREPASSAGERS_H
#define _COMPARERNOMBREPASSAGERS_H

#include "vehicule.h"
#include "Comparator.h"

class ComparerNombrePassagers : public Comparator
{
	public:
	ComparerNombrePassagers(bool sensTri = true);
	~ComparerNombrePassagers();
	virtual bool operator()(const Vehicule* v1, const Vehicule* v2) const;
	
	private:
	bool ordre;
};

#endif
