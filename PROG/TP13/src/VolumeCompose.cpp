#include "VolumeCompose.h"

/**
 * Initialise un filtre composé qui modifie le volume d'un flot
 * @param vol : valeur du signal constant du filtre
 */
VolumeCompose::VolumeCompose(double vol) : filtre_compose(1, 1)
{
	counted_ptr<signal_constant> s(new signal_constant(vol));
	counted_ptr<Multiplicateur> m(new Multiplicateur());
	ajouterComposant(s);
	ajouterComposant(m);

	connecterEntreeInterne(m, 0, 1);
	connecterSortieInterne(m, 0, 0);
	connecter2Composants(s, 0, m, 0);
}
