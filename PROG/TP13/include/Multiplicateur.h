// -*- c++ -*-

#ifndef __MULTIPLICATEUR__H__
#define __MULTIPLICATEUR__H__

#include "filtre_base.h"

class Multiplicateur : public filtre_base {
public:

	Multiplicateur();
  virtual ~Multiplicateur() {}
  
  virtual void calculer();
};

#endif // __MULTIPLICATEUR__H__
