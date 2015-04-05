#include "lecteur_fichier.h"
#include "impl_flot.h"
#include "composant_exception.h"

#include <cstring>
#include <memory>
#include <utility>
#include <string>

lecteur_fichier::lecteur_fichier(std::string nom, unsigned int nbCanaux) : producteur_base(nbCanaux), _nom(nom), _nbCanaux(nbCanaux)
{
	char * cnom = new char [nom.length()+1];
  std::strcpy (cnom, nom.c_str());
  _ifs(cnom, std::ios::binary);
  if(!_ifs.good())
  {
  	composant_exception exc("Fichier non trouvé");
  	exc.what();
  }
}

lecteur_fichier::~lecteur_fichier()
{ _ifs.close(); }

void lecteur_fichier::calculer()
{
		if(!_ifs.eof())
		{
			short int echantillon(0);
			for(unsigned int i = 0; i < _nbCanaux; ++i)
			{
				_ifs.read(echantillon, 16);
				if(!_ifs.good())
				{
					composant_exception exc("Échec de lecture");
					exc.what();
				}
				_sorties[i]->inserer(echantillon);
			}
		}
		else
		{
			composant_exception exc("Fin de fichier atteint");
			exc.what();
		}
}
