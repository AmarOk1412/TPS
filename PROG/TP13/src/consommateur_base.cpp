#include "consommateur_base.h"

consommateur_base::consommateur_base(unsigned int nbEntrees) _nbEntrees(nbEntrees)
{}

consommateur_base::~consommateur() 
{}

unsigned int nbEntrees() constantes
{
	return _nbEntrees;
}

const counted_ptr<flot> & getEntree(unsigned int numentree) const
{
	assert(numentree<nbEntrees());
	return _sorties->at(numsortie);
}
