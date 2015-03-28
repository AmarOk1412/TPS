#include "consommateur_base.h"

consommateur_base::consommateur_base(unsigned int nbEntrees): _nbEntrees(nbEntrees), _entrees()
{
	for(unsigned int i=0; i < _nbEntrees; ++i)
	{
		counted_ptr<flot> flot(new impl_flot());
		_entrees.push_back(flot);
	}
}

unsigned int consommateur_base::nbEntrees() const
{
	return _nbEntrees;
}

const counted_ptr<flot> & consommateur_base::getEntree(unsigned int numentree) const
{
	assert(numentree<nbEntrees());
	return _entrees.at(numentree);
}

bool consommateur_base::yaDesEchantillons() const
{
	return !_entrees.empty();
}

void consommateur_base::connecterEntree(const counted_ptr<flot> & f, unsigned int numentree)
{
	assert(numentree < _nbEntrees);
	_entrees[numentree] = f;
}
