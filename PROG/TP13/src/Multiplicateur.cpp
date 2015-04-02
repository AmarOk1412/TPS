#include "Multiplicateur.h"

#include <iostream>
Multiplicateur::Multiplicateur() : filtre_base(2, 1)
{ }

void Multiplicateur::calculer()
{
	double temp1 = .0;
	double temp2 = .0;
	if(yaDesEchantillons()){
		temp1 = _entrees[0]->extraire();
		temp2 = _entrees[1]->extraire();
		_sorties[0]->inserer(temp1*temp2);
	}
	
	std::cout << temp1 << "---" << temp2  <<"---" << temp1*temp2 << std::endl;
}
