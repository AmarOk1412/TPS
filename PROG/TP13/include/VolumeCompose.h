#ifndef INCLUDE_VOLUMECOMPOSE_H_
#define INCLUDE_VOLUMECOMPOSE_H_

#include "filtre_compose.h"
#include "signal_constant.h"
#include "Multiplicateur.h"

class VolumeCompose: public filtre_compose {
public:
	VolumeCompose(double vol);
	virtual ~VolumeCompose() {}
};

#endif /* INCLUDE_VOLUMECOMPOSE_H_ */
