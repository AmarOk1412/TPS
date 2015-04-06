// -*- c++ -*-

#ifndef __FADEIN__H__
#define __FADEIN__H__

#include "producteur_base.h"
#include <vector>
#include "constantes.h"

class FadeIn : virtual public producteur_base {
public:
  FadeIn(unsigned int duree);
  virtual ~FadeIn() {}
  virtual void calculer();
  
private:
  unsigned int _duree;
  unsigned int _i;
};

#endif // __FADEIN__H__
