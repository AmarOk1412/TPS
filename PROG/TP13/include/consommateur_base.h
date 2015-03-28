// -*- c++ -*-

#ifndef __CONSOMMATEUR_BASE__H__
#define __CONSOMMATEUR_BASE__H__

#include "consommateur.h"
#include "impl_flot.h"
#include "counted_ptr.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	consommateur
///
/// \brief Interface d'un consommateur d'échantillons sonores. Il s'agit d'une
///			interface décrivant un composant qui ne possède que des entrées.
///
/// \author	Jean Christophe Engel, Fabrice Lamarche, University Of Rennes 1
/// \date	23/04/2010
////////////////////////////////////////////////////////////////////////////////////////////////////
class consommateur_base : public virtual consommateur {
public:

	consommateur_base(unsigned int nbEntrees);
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual ~consommateur()
  /// \brief	Destructeur virtuel. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual ~consommateur_base() {}

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual unsigned int nbEntrees() const = 0
  /// \brief	Renvoie le nombre d'entrees du composant. 
  /// \return	Le nombre d'entrees du composant. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual unsigned int nbEntrees() const;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual const counted_ptr<flot> & getEntree(unsigned int numentree) const = 0
  /// \brief	Récupération d'une entrée du composant. 
  /// \param	numentree	Le numero de l'entrée à récuperer. 
  /// \pre 0 <= numentree < nbEntrees()
  /// \return	L'entrée demandée. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual const counted_ptr<flot> & getEntree(unsigned int numentree) const;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual void connecterEntree(const counted_ptr<flot> & f, unsigned int numentree) = 0
  /// \brief	Connecte une entrée sur ce composant. 
  /// \param	f		Le flot à connecter en entrée du composant. 
  /// \param	numentree	Le numéro de l'entree sur laquelle connecter le flot.
  /// \pre    0 <= numentree < nbEntrees()
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual void connecterEntree(const counted_ptr<flot> & f, unsigned int numentree);

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual bool yaDesEchantillons() const = 0
  /// \brief	déterminer si chaque entrée possède au moins un échantillon
  /// \return	Vrai si chaque entrée possède au moins un échantillon.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual bool yaDesEchantillons() const;
  
  virtual void calculer() = 0;
  
protected:
	unsigned int _nbEntrees;
	std::vector<counted_ptr<flot> > _entrees;
};

#endif // __CONSOMMATEUR_BASE__H__
