#include "ferry.h"
 /**
     constructeur : initialiser un ferry vide
     @param longueur  : capacité du ferry en unités de longueur
     @param personnes : capacité du ferry en nombre de passagers
  */
Ferry::Ferry (unsigned int longueur, unsigned int personnes):_longueur(0), _passagers(0), _maxL(longueur), _maxP(personnes), _ferry(std::vector<const Vehicule*>())
{}
/// destructeur
Ferry::~Ferry(void)	
{
	std::vector<const Vehicule*>::const_iterator it = _ferry.begin();
	std::vector<const Vehicule*>::const_iterator it2 = _ferry.end();
	while(it!=it2)
	{
		delete *it;
		++it;
	}
}

  /** ajouter un véhicule dans le ferry.
      sans effet s'il n'y a plus de place
      @param pv : désigne le véhicule à ajouter
      @return vrai si l'ajout a eu lieu, faux sinon
  */
bool  Ferry::ajouter(const Vehicule * pv)
{
	if(_maxL-_longueur >= pv->getLongueur() && _maxP-_passagers >= pv->getPassagers()){
		_ferry.push_back(pv);
		_longueur += pv->getLongueur();
		_passagers += pv->getPassagers();
		return true;
	}
	return false; 
}

//! déterminer le tarif de l'ensembles des véhicules présents dans le ferry
double Ferry::calculerTarif(void) const
{
	double res(0);
	std::vector<const Vehicule*>::const_iterator it = _ferry.begin();
	std::vector<const Vehicule*>::const_iterator it2 = _ferry.end();
	while(it!=it2)
	{
		res += (*it)->calculerTarif();
		++it;
	}
	return res;
}

//! afficher les informations sur le contenu du ferry
void  Ferry::afficher(std::ostream & s) const
{
	std::vector<const Vehicule*>::const_iterator it = _ferry.begin();
	std::vector<const Vehicule*>::const_iterator it2 = _ferry.end();
	while(it!=it2)
	{
		(*it)->afficher(s);
		s << std::endl;
		++it;
	}
	s << "longueur disponible : " << _maxL-_longueur 
		<< " - Nb places disponibles : " << _maxP-_passagers
	 	<< " - 		Tarif total : " << calculerTarif() << std::endl;
}

//opérateur d'affichage
std::ostream & operator << (std::ostream & sortie, const Ferry & ferry)
{
	ferry.afficher(sortie);
	return sortie;
}
