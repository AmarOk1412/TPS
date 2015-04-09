// -*- c++ -*-

#ifndef __MULTIPLICATEUR__H__
#define __MULTIPLICATEUR__H__

#include "filtre_base.h"

class Multiplicateur : public filtre_base {
public:
	/**
	 * Initialise un multiplicateur 
	*/
	Multiplicateur();
	//destructeur
  virtual ~Multiplicateur() {}
  /**
   * Calcule la valeur de l'échantillon en sortie
  */
  virtual void calculer();
};

#endif // __MULTIPLICATEUR__H__
