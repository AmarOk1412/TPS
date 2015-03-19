#ifndef _AMBULANCE_H
#define _AMBULANCE_H

#include "auto.h"
#include <iostream>

class Ambulance : public Auto
{
public:
  /** @param lg : longueur du véhicule
      @param nbp : nombre de personnes transportées
  */
  Ambulance(unsigned int nbp = 1, bool tT=false);
  virtual Vehicule* Clone() const;

  /// destructeur
  ~Ambulance(void);

  //! déterminer le tarif du véhicule
  virtual double	calculerTarif(void) const;

  //! afficher les caractéristiques du véhicule
  void		afficher(std::ostream & s = std::cout) const;
};

#endif
