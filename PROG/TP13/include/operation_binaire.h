
#ifndef __OPERATION_BINAIRE__H__
#define __OPERATION_BINAIRE__H__
#include "filtre_base.h"


template<class T>
class operation_binaire : public filtre_base{
	public:
	operation_binaire(T binaire);
	virtual ~operation_binaire();
	virtual void calculer();
	private:
	T bin;
};
#endif
