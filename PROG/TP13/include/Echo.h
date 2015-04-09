#ifndef INCLUDE_ECHO_H_
#define INCLUDE_ECHO

#include <deque>
#include "filtre_base.h"
#include "constantes.h"

class Echo : public filtre_base {
public:
	/**
	 * Initialise un filtre qui applique un effet d'écho à un flot
	 * @param delay : le delai de l'écho
	*/
	Echo(double delay);
	//destructeur
  virtual ~Echo() {}
  virtual void calculer();
  
  private:
  std::deque<double> buff;
  unsigned int _size;
};

#endif /* INCLUDE_ECHO_H_ */
