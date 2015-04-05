#include "signal_constant.h"
#include "impl_flot.h"
#include <iostream>

signal_constant::signal_constant(double outVal) : producteur_base(1), _outVal(outVal)
{ }

signal_constant::~signal_constant() {}

void signal_constant::calculer()
{
	_sorties.at(0)->inserer(_outVal);
}
