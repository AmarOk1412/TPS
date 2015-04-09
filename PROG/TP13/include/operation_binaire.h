
#ifndef __OPERATION_BINAIRE__H__
#define __OPERATION_BINAIRE__H__
#include "filtre_base.h"


template<class T>
class operation_binaire : public filtre_base{
	public:
	//Initialise une operation binaire
	operation_binaire();
	//destructeur
	virtual ~operation_binaire();
	/**
   * @brief	Effectue les calculs associes au composant.
   */
	virtual void calculer()
	{
		if(yaDesEchantillons())	_sorties[0]->inserer(bin(_entrees[0]->extraire(),_entrees[1]->extraire()));
	}		
	private:	
	T bin;
};

//destructeur
template<class T>
operation_binaire<T>::~operation_binaire() {};
//constructeur
template<class T>
operation_binaire<T>::operation_binaire() : bin(T()), filtre_base(2, 1)
{}



#endif
