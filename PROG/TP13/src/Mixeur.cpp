#include "Mixeur.h"

#include "operation_binaire.h"
#include "signal_constant.h"
#include "Volume.h"
#include <functional>
#include <vector>

Mixeur::Mixeur(unsigned int nbEntrees, double volumes[]) : filtre_compose(nbEntrees,1)
{
	//Première colonne de multiplicateur
	std::vector<counted_ptr<filtre_base> > couchePre;
	for(unsigned int i = 0; i < nbEntrees; ++i)
	{
		counted_ptr<filtre_base> vol(new Volume(volumes[i]));
		ajouterComposant(vol);
		connecterEntreeInterne(vol, i, 0);
		couchePre.push_back(vol);
	}
	
	//Pyramide de add
	std::vector<counted_ptr<filtre_base> > tcouchePre;
	while(couchePre.size() > 1)
	{
		for(unsigned int i = 0; i < couchePre.size(); i+=2)
		{
			counted_ptr<filtre_base> adder(new operation_binaire<std::plus<double> >());
			if(i+1 == couchePre.size())
			{
				signal_constant *s = new signal_constant(1);
				counted_ptr<signal_constant> ps(s);
				ajouterComposant(ps);
				connecter2Composants(ps, 0, adder, 1);
			}
			else
				connecter2Composants(couchePre[i+1], 0, adder, 1);
			connecter2Composants(couchePre[i], 0, adder, 0);
			ajouterComposant(adder);
			tcouchePre.push_back(adder);
		}
		couchePre = tcouchePre;
		tcouchePre.clear();
	}
	//Connecter le dernier adder
	connecterSortieInterne(couchePre[0], 0, 0);
}
