// -*- c++ -*-

#ifndef __MIXEUR__H__
#define __MIXEUR__H__

#include "filtre_compose.h"

class Mixeur : public filtre_compose {
public:
	Mixeur(unsigned int nbEntrees, double volumes[]);
  virtual ~Mixeur() {}
  
  private:
};

#endif // __Mixeur__H__
