#ifndef INCLUDE_COMPRESSER_H_
#define INCLUDE_COMPRESSER_H_

#include "filtre_base.h"

class Compresser : public filtre_base {
public:
	Compresser(float taux);
  virtual ~Compresser() {}
  virtual void calculer();
  
  private:
  float _taux;
};

#endif /* INCLUDE_COMPRESSER_H_ */
