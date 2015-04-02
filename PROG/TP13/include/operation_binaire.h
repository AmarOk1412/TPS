
#ifndef __OPERATION_BINAIRE__H__
#define __OPERATION_BINAIRE__H__
#include "filtre_base.h"


template<class T>
class operation_binaire : public filtre_base{
	public:
	operation_binaire();
	virtual ~operation_binaire();
	virtual void calculer()
	{
		if(yaDesEchantillons())	_sorties[0]->inserer(bin(_entrees[0]->extraire(),_entrees[1]->extraire()));
	}		
	private:	
	T bin;
};

template<class T>
operation_binaire<T>::~operation_binaire() {};
template<class T>
operation_binaire<T>::operation_binaire() : bin(T()), filtre_base(2, 1)
{}



#endif
