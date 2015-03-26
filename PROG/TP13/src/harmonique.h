// -*- c++ -*-

#ifndef __HARMONIQUE__H__
#define __HARMONIQUE__H__

#include "producteur_base.h"
#include <vector>
#include "constantes.h"

class harmonique : virtual public producteur_base {
public:
  harmonique(unsigned int frequency, double phi);
  virtual ~harmonique() {}

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
  virtual void calculer();
  
protected:
  virtual void connecterSortie(const counted_ptr<flot> & f, unsigned int numsortie); 
  counted_ptr< std::vector< counted_ptr<flot> > > _sorties;
  unsigned int _nbSorties;
  unsigned int freq;
  double dephasage;
};

#endif // __HARMONIQUE__H__
