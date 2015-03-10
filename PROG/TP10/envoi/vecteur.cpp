/** \brief Ce fichier doit contenir l'ensemble des implémentations
relatives à la classe vecteur et aux fonctionnalités la concernant */

#include <cassert>
#include <iostream>
#include "vecteur.h"

/**
 * @pre: nb_dim > 0
 */
Vecteur::Vecteur(unsigned int nb_dim, float val_init) : m_dim(nb_dim)
{
  assert(nb_dim > 0);
	m_vecteur = new float[m_dim];
	for(unsigned int i = 0; i < nb_dim; ++i)
		m_vecteur[i] = val_init;
	std::cout << "Constructeur vecteur" << std::endl;
}

Vecteur::~Vecteur()
{
	std::cout << "DESTRUCTION VECTEUR" << std::endl;
	delete[] m_vecteur;
}

/**
 * Copie un vecteur
 */
Vecteur::Vecteur(const Vecteur &o)
{
	m_dim = o.dimensions();
	m_vecteur = new float[m_dim];

	for(unsigned int i = 0; i < m_dim; ++i)
		m_vecteur[i] = o.get(i);
}

/**
 * Retourne this[i]
 * @pre: 0 <= i < m_dim
 */
float& Vecteur::get(unsigned int i)
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * Retourne this[i]
 * @pre: 0 <= i < m_dim
 */
const float& Vecteur::get(const unsigned int i) const
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * Associe this[i] à une nouvelle valeur
 * @pre: 0 <= i < m_dim
 */
void Vecteur::set(unsigned int i, float v)
{
	assert(i < m_dim);
	m_vecteur[i]=v;
}

/**
 * @return le nomber de dimensions du vecteur
 */
unsigned int Vecteur::dimensions() const
{
	return m_dim;
}

/**
 * Affiche un vecteur
 * @param: v le vecteur à afficher
 */
void afficherVecteur(const Vecteur *v)
{
	for(unsigned int i=0; i<v->dimensions(); ++i)
		std::cout << v->get(i) << std::endl;
}

/**
 * Créé un vecteur depuis l'entrée standard
 */
Vecteur* lireVecteur()
{
	unsigned int dim;
	std::cout << "Entrez un nombre de dimensions" << std::endl;
	std::cin >> dim;
	Vecteur *res = new Vecteur(dim);

	for(unsigned int i=0; i<dim; i++)
	{
		float value;
		std::cout << "Entrez un nombre" << std::endl;
		std::cin >> value;
		res->set(i, value);
	}

	return res;
}

/**
 * Effectue une addition de 2 vecteurs
 * @pre: v2->dimensions() == v1->dimensions()
 * @return le vecteur somme des deux vecteurs passés en paramètres
 */
Vecteur add(const Vecteur *v1, const Vecteur * v2)
{
	assert(v2->dimensions() == v1->dimensions());
	unsigned int dim = v1->dimensions();
	Vecteur v(dim);
	for(unsigned int i=0 ; i<dim; i++ )
		v.set(i,v1->get(i)+v2->get(i));
	return v;
}

/**
 * Copie un vecteur
 */
Vecteur& Vecteur::operator=(const Vecteur &v1)
{
	if(this != &v1)
	{
		if(m_vecteur != NULL) delete[] m_vecteur;
		m_dim = v1.dimensions();
		m_vecteur = new float[m_dim];

		for(unsigned int i = 0; i < m_dim; ++i)
			m_vecteur[i] = v1.get(i);
	}
	return *this;
}

/**
 * Effectue une addition de 2 vecteurs
 * @pre: v2->dimensions() == v1->dimensions()
 * @return le vecteur somme des deux vecteurs passés en paramètres
 */
Vecteur Vecteur::operator+(const Vecteur &v1)
{
	assert(m_dim == v1.dimensions());
	Vecteur v(v1.dimensions());
	for(unsigned int i=0 ; i<v1.dimensions(); i++)
		v.set(i,v1.get(i)+get(i));
	return v;
}

/**
 * Accès en lecture seule à this[i]
 */
const float& Vecteur::operator[](const unsigned int i) const
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * Accès en lecture/écriture à this[i]
 */
float& Vecteur::operator[](unsigned int i)
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * Effectue une multiplication scalaire v1 et v2
 * @param: v1 le vecteur 1
 * @param: v2 le vecteur 2
 * @return: v1.v2
 */
float operator*(const Vecteur &v1, const Vecteur &v2)
{
	assert(v2.dimensions() == v1.dimensions());
	float res = 0;
	for(unsigned int i=0 ; i<v1.dimensions(); i++)
		res += v1.get(i)*v2.get(i);
	return res;
}

/**
 * Affiche un vecteur
 * @param: out le flux de sortie
 * @param: v1 le vecteur à afficher
 * @return: un flux de sortie affichant le vecteur v1
 */
std::ostream & operator<<(std::ostream & out, const Vecteur &v1)
{
	out << "[";
	for(unsigned int i=0; i<v1.dimensions(); ++i) out << v1.get(i) <<" ";
	out << "]";
	return out;
}

/**
 * Lis un vecteur
 * @param: in le flux d'entrée
 * @param: v1 le vecteur à modifier
 */
std::istream & operator>>(std::istream & in, Vecteur &v1)
{
	for(unsigned int i=0; i<v1.dimensions(); i++)
	{
		float value;
		in >> value;
		v1.set(i, value);
	}
	return in;
}
