#include "lecteur_fichier.h"
#include "impl_flot.h"

lecteur_fichier::lecteur_fichier(std::string nom, unsigned int nbCanaux) : producteur_base(nbCanaux), _nom(nom), _nbCanaux(nbCanaux)
{
	char * cnom = new char [nom.length()+1];
  std::strcpy (cnom, nom.c_str());
  _isf(cnom, std::ifstream::in | std::ifstream::binary);
}			

lecteur_fichier::~lecteur_fichier()
{}

lecteur_fichier::void calculer()
{
		short int echantillon(0);
		_isf.read(echantillon, 16);
		_sorties[0]->insérer(echantillon);
		if(_nbCanaux==2)
		{
			_isf.read(echantillon, 16);
				_sorties[1]->insérer(echantillon);
		}
}
