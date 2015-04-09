#ifndef INCLUDE_VOLUMECOMPOSE_H_
#define INCLUDE_VOLUMECOMPOSE_H_

#include "filtre_compose.h"
#include "signal_constant.h"
#include "Multiplicateur.h"

class VolumeCompose: public filtre_compose {
public:
	/**
	 * Initialise un filtre composé qui modifie le volume d'un flot
	 * @param vol : valeur du signal constant du filtre
	*/
	VolumeCompose(double vol);
	
	//destructeur
	virtual ~VolumeCompose() {}
};

#endif /* INCLUDE_VOLUMECOMPOSE_H_ */
