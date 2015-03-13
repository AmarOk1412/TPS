// -*- c++ -*-

#ifndef _FERRY_H
#define _FERRY_H
// choisir selon le conteneur utilisé
#include <vector>
//#include <deque>
#include <list>
#include "vehicule.h"

/**
 * Un ferry transporte des véhicules
 */
class Ferry {
public:
  /**
     constructeur : initialiser un ferry vide
     @param longueur  : capacité du ferry en unités de longueur
     @param personnes : capacité du ferry en nombre de passagers
  */
  Ferry (unsigned int longueur, unsigned int personnes);

  /// destructeur
  virtual ~Ferry(void);

  /** ajouter un véhicule dans le ferry.
      sans effet s'il n'y a plus de place
      @param pv : désigne le véhicule à ajouter
      @return vrai si l'ajout a eu lieu, faux sinon
  */
  virtual bool   ajouter(const Vehicule * pv);

  //! déterminer le tarif de l'ensembles des véhicules présents dans le ferry
  virtual double calculerTarif(void) const;

  //! afficher les informations sur le contenu du ferry
  virtual void   afficher(std::ostream & s = std::cout) const;

private :
  unsigned int _longueur;		///< longueur du gros véhicule
  unsigned int _passagers;
  unsigned int _maxL;		///< longueur du gros véhicule
  unsigned int _maxP;
  std::vector<const Vehicule*> _ferry;
};

// opérateur d'affichage
std::ostream & operator << (std::ostream & sortie, const Ferry & ferry);

#endif // _FERRY_H