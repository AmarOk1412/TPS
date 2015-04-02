#include "operation_binaire.h"

template<class T>
operation_binaire::operation_binaire(T binaire) : bin(binaire), filtre_base(2, 1)
{}

template<class T>
void operation_binaire::calculer()
{
	if(yaDesEchantillons())	_sorties[0]->inserer(T(_entrees[O],entrees[1]));
}		

