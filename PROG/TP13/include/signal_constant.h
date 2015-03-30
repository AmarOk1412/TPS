// -*- c++ -*-

#ifndef __SIGNAL_CONSTANT__H__
#define __SIGNAL_CONSTANT__H__

#include "producteur_base.h"
#include <vector>

class signal_constant : public producteur_base {
public:

  signal_constant(double outVal);
  ~signal_constant();
  
  /**
   * @brief	Effectue les calculs associes au composant.
   */
  void calculer();
  
private:
	double _outVal; 
};

#endif // __SIGNAL_CONSTANT__H__
