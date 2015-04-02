// -*- c++ -*-

#ifndef __VOLUME__H__
#define __VOLUME__H__

#include "Multiplicateur.h"
#include "signal_constant.h"
#include "filtre_base.h"

class Volume : public filtre_base {
public:
	Volume(double volume);
  virtual ~Volume() {}
  void setVolume(double volume);
  virtual void calculer();
  
  private:
  signal_constant _s;
  Multiplicateur _m;
};

#endif // __VOLUME__H__
