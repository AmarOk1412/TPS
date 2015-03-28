#include "signal_constant.h"
#include "impl_flot.h"
#include <iostream>

signal_constant::signal_constant(double outVal) : producteur_base(1), _outVal(outVal)
{ }

signal_constant::~signal_constant() {}

void signal_constant::calculer()
{
  unsigned int nb = nbSorties();
	for(unsigned int i = 0; i < nb; ++i)
		_sorties.at(i)->inserer(_outVal);
}
