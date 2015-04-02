
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

template<class T>
operation_binaire::operation_binaire(T binaire) : bin(binaire), filtre_base(2, 1)
{}

template<class T>
void operation_binaire::calculer()
{
	if(yaDesEchantillons())	_sorties[0]->inserer(T(_entrees[O],entrees[1]));
}		


#endif
