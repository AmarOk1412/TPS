#ifndef INCLUDE_ECHO_H_
#define INCLUDE_ECHO

#include <deque>
#include "filtre_base.h"
#include "constantes.h"

class Echo : public filtre_base {
public:
	Echo(double delay);
  virtual ~Echo() {}
  virtual void calculer();
  
  private:
  std::deque<double> buff;
  unsigned int _size;
};

#endif /* INCLUDE_ECHO_H_ */
