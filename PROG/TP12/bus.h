// -*- c++ -*-
#ifndef _BUS_H
#define _BUS_H

#include "vehicule.h"
#include <iostream>
/**
 * définition abstraite d'un Vehicule
 */

class Bus : public Vehicule {
public:
  /** @param lg : longueur du véhicule
      @param nbp : nombre de personnes transportées
  */
  Bus(unsigned int l = 1, unsigned int nbp = 1);
  
  virtual Vehicule* Clone();

  /// destructeur
  ~Bus(void);

  //! déterminer le tarif du véhicule
  double	calculerTarif(void) const;

  //! afficher les caractéristiques du véhicule
  void		afficher(std::ostream & s = std::cout) const;
private:
  unsigned int longueur;		///< longueur du véhicule
  unsigned int passagers;		///< nombre de personnes dans le véhicule
};

#endif // _BUS_H
