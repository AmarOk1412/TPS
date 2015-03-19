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
  
  virtual Vehicule* Clone() const;

  /// destructeur
  ~Bus(void);

  //! déterminer le tarif du véhicule
  double	calculerTarif(void) const;

  //! afficher les caractéristiques du véhicule
  void		afficher(std::ostream & s = std::cout) const;
};

#endif // _BUS_H
