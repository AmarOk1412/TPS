#include "lecteur_fichier.h"
#include "impl_flot.h"
#include "composant_exception.h"

#include <cstring>
#include <memory>
#include <utility>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <climits>

lecteur_fichier::lecteur_fichier(std::string nom, unsigned int nbCanaux) : producteur_base(nbCanaux), _nom(nom), _nbCanaux(nbCanaux)
{
	char * cnom = new char [nom.length()+1];
  std::strcpy (cnom, nom.c_str());
  _ifs.open(nom.c_str(), std::ios::in | std::ios::binary);
  if(!_ifs.good()) {
  	composant_exception exc("Fichier non trouvé (" + nom + ")");  	
		throw exc;
	}
}

lecteur_fichier::~lecteur_fichier()
{ _ifs.close(); }

void lecteur_fichier::calculer()
{
		if(!_ifs.eof())
			for(unsigned int i = 0; i < _nbCanaux; ++i)
			{
				short int echantillon(0);
				_ifs.read((char *)&echantillon, sizeof(short int));
				if(!_ifs.good() && !_ifs.eof()) {
					composant_exception exc("Échec de lecture");
					throw exc;
				}
				double e = (double)echantillon/(double)SHRT_MAX;
				_sorties[i]->inserer(e);
			}
		else
		{
			composant_exception exc("Fin de fichier atteint ("+_nom+")");
			throw exc;
		}
}

void lecteur_fichier::ElectroSummerMixCalc()
{
		if(!_ifs.eof())
			for(unsigned int i = 0; i < _nbCanaux; ++i)
			{
				long echantillon(0);
				_ifs.read((char *)&echantillon, sizeof(long));
				if(!_ifs.good() && !_ifs.eof()) {
					composant_exception exc("Échec de lecture");
					throw exc;
				}
				double e = (double)echantillon/(double)LONG_MAX;
				_sorties[i]->inserer(e);
			}
		else
		{
			composant_exception exc("Fin de fichier atteint ("+_nom+")");
			throw exc;
		}
}
