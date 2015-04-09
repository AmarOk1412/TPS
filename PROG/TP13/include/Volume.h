// -*- c++ -*-

#ifndef __VOLUME__H__
#define __VOLUME__H__

#include "Multiplicateur.h"
#include "signal_constant.h"
#include "filtre_base.h"

class Volume : public filtre_base {
public:
	/**
	 * Initialise un filtre qui modifie le volume d'un flot
	 * @param volume
	*/
	Volume(double volume);
	//destructeur
  virtual ~Volume() {}
  /**
   * Modifier le volume du filtre
   * @param volume
  */
  void setVolume(double volume);
  /**
   * Calculer la valeur de l'échantillon en sortie
  */
  virtual void calculer();
  /**
   * Connecter un flot à une entrée du filtre
   * @param f : un flot
   * @param numentree : le numéro de l'entrées
  */
  virtual void connecterEntree(const counted_ptr<flot> &f, unsigned int numentree);
  
  private:
  signal_constant _s;
  Multiplicateur _m;
};

#endif // __VOLUME__H__
