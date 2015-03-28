// -*- c++ -*-

#ifndef __PRODUCTEUR_BASE__H__
#define __PRODUCTEUR_BASE__H__

#include "producteur.h"
#include <vector>

class producteur_base : virtual public producteur {
public:
  producteur_base(unsigned int nbSorties);
  virtual ~producteur_base() {}

  /**
  * @fn	unsigned int nbSorties() const = 0
  * @brief	Nombre de sorties du composant. 
  * @return Le nombre de sorties du composant. 
  */
  virtual unsigned int nbSorties() const;

  /**
  * @fn	const counted_ptr<flot> & getSortie(unsigned int numsortie) = 0
  * @brief	Recupération d'une sortie du composant. 
  * @param	numsortie	Le numero de la sortie a recuperer. 
  * @pre 0 <= numsortie < nbSorties()
  * @return	La sortie demandée. 
  */
  virtual const counted_ptr<flot> & getSortie(unsigned int numsortie) const;
  
  /**
   * @brief	Effectue les calculs associes au composant.
   */
  virtual void calculer() = 0;
  
protected:
  virtual void connecterSortie(const counted_ptr<flot> & f, unsigned int numsortie); 
  std::vector< counted_ptr<flot> > _sorties;
  unsigned int _nbSorties;
};

#endif // __PRODUCTEUR__H__
