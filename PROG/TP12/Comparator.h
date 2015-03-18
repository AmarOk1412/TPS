#ifndef _COMPARATOR_H
#define _COMPARATOR_H

#include "vehicule.h"

class Comparator
{
	public:
	Comparator(bool sensTri = true);
	virtual ~Comparator();
	virtual bool operator()(const Vehicule* v1, const Vehicule* v2) const;
	
	private:
	bool ordre;
};

#endif
