// -*- c++ -*-

#ifndef __MIXEUR__H__
#define __MIXEUR__H__

#include "filtre_compose.h"

class Mixeur : public filtre_compose {
public:
	Mixeur(double volume);
  virtual ~Mixeur() {}
  virtual void calculer();
  virtual void connecterEntree(const counted_ptr<flot> &f, unsigned int numentree);
  
  private:
};

#endif // __Mixeur__H__
