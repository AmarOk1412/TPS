#include "harmonique.h"
#include <math.h>
#include "impl_flot.h"

harmonique::harmonique(unsigned int frequence, double phi): producteur_base(1), _freq(frequence), _dephasage(phi), _i(0)
{ }

void harmonique::calculer()
{
	_sorties[0]->inserer(sin((_i/(double)MixageSonore::frequency) * 2 * MixageSonore::pi * _freq + _dephasage));
	_i++;
}
