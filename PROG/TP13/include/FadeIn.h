// -*- c++ -*-

#ifndef __FADEIN__H__
#define __FADEIN__H__

#include "producteur_base.h"
#include <vector>
#include "constantes.h"

class FadeIn : virtual public producteur_base {
public:
	/**
	 * Initialise un producteur qui produit un flot avec un effet de fondu en ouverture
	 * @param duree : la durée du fondu en ouverture
	*/
  FadeIn(unsigned int duree);
  //destructeur
  virtual ~FadeIn() {}
  virtual void calculer();
  
private:
  unsigned int _duree;
  unsigned int _i;
};

#endif // __FADEIN__H__
