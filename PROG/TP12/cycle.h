// -*- c++ -*-
#ifndef _CYCLE_H
#define _CYCLE_H

#include "vehicule.h"
#include <iostream>
/**
 * définition abstraite d'un Vehicule
 */

class Cycle : public Vehicule {
public:
  /** @param lg : longueur du véhicule
      @param nbp : nombre de personnes transportées
  */
  Cycle();
  virtual Vehicule* Clone() const;

  /// destructeur
  ~Cycle(void);

  //! déterminer le tarif du véhicule
  virtual double	calculerTarif(void) const;

  //! afficher les caractéristiques du véhicule
  void		afficher(std::ostream & s = std::cout) const;
private:
  unsigned int longueur;		///< longueur du véhicule
  unsigned int passagers;		///< nombre de personnes dans le véhicule
};

#endif // _CYCLE_H

