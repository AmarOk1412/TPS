#include "Volume.h"
#include <iostream>

Volume::Volume(double volume) : filtre_base(1, 1), _s(volume), _m()
{
	_m.connecterEntree(_s.getSortie(0), 0);
	_m.connecterSortie(getSortie(0), 0);

}

void Volume::setVolume(double volume)
{
	_s.setOutVal(volume);
}

void Volume::connecterEntree(const counted_ptr<flot> &f, unsigned int numentree)
{
  consommateur_base::connecterEntree(f, numentree);
  _m.connecterEntree(f, 1);
}

void Volume::calculer()
{
	if(yaDesEchantillons())
	{
		_s.calculer();
		_m.calculer();
	}
}
