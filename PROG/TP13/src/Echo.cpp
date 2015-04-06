#include "Echo.h"

Echo::Echo(double delay): filtre_base(1, 1), buff(delay), _size(MixageSonore::frequency*delay)
{ }

void Echo::calculer()
{
	if(yaDesEchantillons())
	{
		double val = _entrees[0]->extraire();
		double other = 1;
		if(buff.size() == _size)
		{
			other = buff.back();
			buff.pop_back();
			buff.push_front(val);
		}
		_sorties[0]->inserer(val*other);
	}
	else if(!buff.empty()){	
		_sorties[0]->inserer(buff.back());
		buff.pop_back();
	}
}
