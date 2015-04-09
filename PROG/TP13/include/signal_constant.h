// -*- c++ -*-

#ifndef __SIGNAL_CONSTANT__H__
#define __SIGNAL_CONSTANT__H__

#include "producteur_base.h"
#include <vector>

class signal_constant : public producteur_base {
public:
	/**
	 * Initialise un producteur qui produit un signal constant
	 * @param outVal
	*/
  signal_constant(double outVal);
  //destructeur
  ~signal_constant();
  
  /**
   * @brief	Effectue les calculs associes au composant.
   */
  void calculer();
  
  /**
   * Modifie la valeur du signal constant
   * @param newVal : un réel
   */
  void setOutVal(double newVal) { _outVal = newVal; }
  
private:
	double _outVal; 
};

#endif // __SIGNAL_CONSTANT__H__
