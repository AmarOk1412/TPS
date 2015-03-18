// -*- c++ -*-
#ifndef _AUTO_H
#define _AUTO_H

#include "vehicule.h"
#include <iostream>
/**
 * définition abstraite d'un Vehicule
 */

class Auto : public Vehicule {
public:
  /** @param lg : longueur du véhicule
      @param nbp : nombre de personnes transportées
  */
  Auto(unsigned int nbp = 1, bool tT=false);
  virtual Vehicule* Clone();

  /// destructeur
  ~Auto(void);

  //! déterminer le tarif du véhicule
  double	calculerTarif(void) const;

  //! afficher les caractéristiques du véhicule
  void		afficher(std::ostream & s = std::cout) const;
private:
  unsigned int longueur;		///< longueur du véhicule
  unsigned int passagers;		///< nombre de personnes dans le véhicule
  bool toutTerrain; 				///tout terrain ou pas
};

#endif // _VEHICULE_H
