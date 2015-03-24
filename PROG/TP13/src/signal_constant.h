// -*- c++ -*-

#ifndef __SIGNAL_CONSTANT__H__
#define __SIGNAL_CONSTANT__H__

#include "producteur.h"
#include <vector>

class signal_constant : public producteur {
public:

  signal_constant(double outVal);
  ~signal_constant();

  /**
  * @fn	unsigned int nbSorties() const = 0
  * @brief	Nombre de sorties du composant. 
  * @return Le nombre de sorties du composant. 
  */
  unsigned int nbSorties() const;

  /**
  * @fn	const counted_ptr<flot> & getSortie(unsigned int numsortie) = 0
  * @brief	Recupération d'une sortie du composant. 
  * @param	numsortie	Le numero de la sortie a recuperer. 
  * @pre 0 <= numsortie < nbSorties()
  * @return	La sortie demandée. 
  */
  const counted_ptr<flot> & getSortie(unsigned int numsortie) const;
  
  /**
   * @brief	Effectue les calculs associes au composant.
   */
  void calculer();
  
private:
	double _outVal;  
  counted_ptr< std::vector< counted_ptr<flot> > > _sorties;
};

#endif // __SIGNAL_CONSTANT__H__
