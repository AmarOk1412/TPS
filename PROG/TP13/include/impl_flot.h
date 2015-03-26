// -*- c++ -*-

#ifndef __IMPL_FLOT__H__
#define __IMPL_FLOT__H__

#include <deque>

#include "flot.h"
#include "counted_ptr.h"

class impl_flot : public flot{
public :

  impl_flot();
  ~impl_flot();

	/**
	 * @brief	Insertion d'un echantillon dans le flot. 
   * @param	echantillon	L'echantillon a inserer dans le flot.
   */
  virtual void inserer(double echantillon);

  /**
   * @brief	Extraction de l'echantillon situe en tete du flot. 
   * @pre	!vide()
   * @return	L'echantillon en tete de flot. 
   */
  virtual double extraire();
  /**
   * @brief	Permet de savoir si le flot est vide ou non. 
   * @return	Vrai si le flot est vide, faux sinon. 
   */
  virtual bool vide() const;
  
private:
  counted_ptr<std::deque<double> > _flot;
  
};

#endif // __FLOT__H__
