// -*- c++ -*-

#ifndef __MIXEUR__H__
#define __MIXEUR__H__

#include "filtre_compose.h"

class Mixeur : public filtre_compose {
public:
	/**
	 * Initialise un mixeur
	 * @param nbEntrees : le nombre d'entrées du filtre
	 * @param volumes : 
	*/
	Mixeur(unsigned int nbEntrees, double volumes[]);
	
	//destructeur
  virtual ~Mixeur() {}
  
  private:
};

#endif // __Mixeur__H__
