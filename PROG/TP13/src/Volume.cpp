#include "Volume.h"

/**
 * Initialise un filtre qui modifie le volume d'un flot
 * @param volume
 */
Volume::Volume(double volume) : filtre_base(1, 1), _s(volume), _m()
{
	_m.connecterEntree(_s.getSortie(0), 0);
	_m.connecterSortie(getSortie(0), 0);
}
/**
 * Modifier le volume du filtre
 * @param volume
 */
void Volume::setVolume(double volume)
{
	_s.setOutVal(volume);
}
/**
 * Connecter un flot à une entrée du filtre
 * @param f : un flot
 * @param numentree : le numéro de l'entrées
 */
void Volume::connecterEntree(const counted_ptr<flot> &f, unsigned int numentree)
{
  consommateur_base::connecterEntree(f, numentree);
  _m.connecterEntree(f, 1);
}
/**
 * @brief	Effectue les calculs associes au composant.
 */
void Volume::calculer()
{
	if(yaDesEchantillons())
	{
		_s.calculer();
		_m.calculer();
	}
}
