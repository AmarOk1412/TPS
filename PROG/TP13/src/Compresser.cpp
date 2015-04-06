#include "Compresser.h"
#include <math.h>
#include <iostream>

Compresser::Compresser(float taux) : filtre_base(1, 1), _taux(taux)
{ }

void Compresser::calculer()
{
	if(yaDesEchantillons())
	{
		double val = _entrees[0]->extraire();
		double signe = -1.;
		if(val >= 0)
			signe = 1.;
		double value = signe*pow(sqrt(pow(val,2)), _taux);
		std::cout << val << "---" << value << std::endl;
		_sorties[0]->inserer(value);
	}
}
