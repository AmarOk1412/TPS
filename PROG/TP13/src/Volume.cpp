#include "Volume.h"

Volume::Volume(double volume) : filtre_base(1, 1), _s(volume), _m()
{
	_m.connecterEntree(_s.getSortie(0), 0);
	_m.connecterEntree(getSortie(0), 1);
}

void Volume::setVolume(double volume)
{
	_s.setOutVal(volume);
}

void Volume::calculer()
{
	if(yaDesEchantillons())
	{
		_s.calculer();
		_m.calculer();
		_sorties[0]->inserer(_m.getSortie(0)->extraire());
	}
}
