#include "enregistreur_fichier.h"
#include <iostream>
#include <fstream>
#include "impl_flot.h"

enregistreur_fichier::enregistreur_fichier(std::string nf,
 unsigned int nbc) :  m_nomFichier(nf), m_nbE(nbc)
{
	m_lesEntrees.resize(m_nbE);
	for(unsigned int i = 1; i < m_nbE; ++i)
	{
		flot* f = new impl_flot();
		counted_ptr<flot> sortie(f);
		m_lesEntrees.push_back(sortie);
	}
	m_fluxSortie.open(nf.c_str());
}

enregistreur_fichier::~enregistreur_fichier()
{
	m_fluxSortie.close();
}

unsigned int enregistreur_fichier::nbEntrees() const
{
	return m_nbE;
}

/// \return	L'entrée demandée. 
const counted_ptr<flot> & enregistreur_fichier::getEntree(unsigned int numentree) const
{
	assert(numentree < m_lesEntrees.size());
	return m_lesEntrees[numentree];
}

/// \brief	Connecte une entrée sur ce composant. 
///
/// \param	f		Le flot à connecter en entrée du composant. 
/// \param	numentree	Le numéro de l'entree sur laquelle connecter le flot.
///
/// \pre    0 <= numentree < nbEntrees()
void enregistreur_fichier::connecterEntree(const counted_ptr<flot> & f, unsigned int numentree)
{
	assert(numentree < nbEntrees());
	m_lesEntrees[numentree] = f;
}

/// \return	Vrai si chaque entrée possède au moins un échantillon.
bool enregistreur_fichier::yaDesEchantillons() const
{
	for(unsigned int i = 0; i < m_lesEntrees.size(); ++i)
		if(m_lesEntrees[i]->vide())
			return false;
	return true;
}

/// \brief	Effectue les calculs associes au composant. 
void enregistreur_fichier::calculer()
{
	if(yaDesEchantillons())
		for(unsigned int i = 0; i < m_lesEntrees.size(); ++i)
			m_fluxSortie << m_lesEntrees.at(i)->extraire() << std::endl;
}

const std::string  & enregistreur_fichier::getNomFichier() const
{
	return m_nomFichier;
}

std::ofstream & enregistreur_fichier::getStream()
{
	return m_fluxSortie;
}
