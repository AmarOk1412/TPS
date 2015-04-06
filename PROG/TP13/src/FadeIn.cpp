#include "FadeIn.h"
#include <math.h>
#include "impl_flot.h"

FadeIn::FadeIn(unsigned int duree): producteur_base(1), _duree(duree), _i(0)
{ }

void FadeIn::calculer()
{
	_sorties[0]->inserer(1-((_duree*(double)MixageSonore::frequency-_i)/(_duree*(double)MixageSonore::frequency)));
	if(_i < (_duree*(double)MixageSonore::frequency)) _i++;
}
