// -*- c++ -*-

#ifndef __HARMONIQUE__H__
#define __HARMONIQUE__H__

#include "producteur_base.h"
#include <vector>
#include "constantes.h"

class harmonique : virtual public producteur_base {
public:
  harmonique(unsigned int frequence, double phi = 0);
  virtual ~harmonique() {}

  /**
   * @brief	Effectue les calculs associes au composant.
   */
  virtual void calculer();
  
private:
  unsigned int _freq;
  double _dephasage;
  unsigned long _i;
};

#endif // __HARMONIQUE__H__
