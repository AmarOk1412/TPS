#include "signal_constant.h"

signal_constant::signal_constant(double outVal) : producteur(), _outVal(outVal), _sorties(new std::vector< counted_ptr<flot> >())
{}

signal_constant::~signal_constant() {}

unsigned int signal_constant::nbSorties() const
{
	return _sorties->size();
}

const counted_ptr<flot> & signal_constant::getSortie(unsigned int numsortie) const
{
	assert(numsortie<nbSorties());
	return _sorties->at(numsortie);
}

void signal_constant::calculer()
{
  unsigned int nb = nbSorties();
	for(unsigned int i = 0; i < nb; ++i)
	  getSortie(i)->inserer(_outVal);
}
