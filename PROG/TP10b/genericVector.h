/** \brief Ce fichier doit contenir la déclaration de la classe vecteur
    Attention, elle ne doit contenir aucune implémentation de méthode / fonction
*/

#ifndef _GENERICVECTOR_H
#define _GENERICVECTOR_H


#include <iostream>
#include <string>
#include <cassert>

template <class T>
class GenericVector {
public :
  GenericVector(unsigned int nb_dim = 3, T val_init = T());
  ~GenericVector();
  GenericVector(const GenericVector<T> &o);
  template<class U>
  GenericVector(const GenericVector<U> &o);
  T get(int unsigned i) const;
  void set(int unsigned i,T v);
  unsigned int dimensions() const;
  GenericVector<T>& operator=(const GenericVector<T> &v1);
  GenericVector<T> operator+(const GenericVector<T> &v1);
  const T& operator[](const unsigned int i) const;
  T& operator[](unsigned int i);  
  
private :
	unsigned int m_dim;
	T *m_vecteur;
};

/**
 * @pre: nb_dim > 0
 */
template <class T> 
GenericVector<T>::GenericVector(unsigned int nb_dim, T val_init) : m_dim(nb_dim)
{
  assert(nb_dim > 0);
	m_vecteur = new T[m_dim];
	for(unsigned int i = 0; i < nb_dim; ++i)
		m_vecteur[i] = val_init;
}

template <class T>
GenericVector<T>::~GenericVector()
{
	delete[] m_vecteur;
}

template <class T>
GenericVector<T>::GenericVector(const GenericVector<T> &o)
{
	m_dim = o.dimensions();
	m_vecteur = new T[m_dim];

	for(unsigned int i = 0; i < m_dim; ++i)
		m_vecteur[i] = o.get(i);
}

template <class T>
template <class U>
GenericVector<T>::GenericVector(const GenericVector<U> &o)
{
	m_dim = o.dimensions();
	m_vecteur = new T[m_dim];

	for(unsigned int i = 0; i < m_dim; ++i)
		m_vecteur[i] = o.get(i);
}

/**
 * @pre: 0 <= i < m_dim
 */
template <class T>
T GenericVector<T>::get(unsigned int i) const
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * @pre: 0 <= i < m_dim
 */
template <class T>
void GenericVector<T>::set(unsigned int i, T v)
{
	assert(i < m_dim);
	m_vecteur[i]=v;
}

template <class T>
unsigned int GenericVector<T>::dimensions() const
{
	return m_dim;
}

template <class T>
void afficherVecteur(const GenericVector<T> *v)
{
	for(unsigned int i=0; i<v->dimensions(); ++i)
		std::cout << v->get(i) << std::endl;
}

/**
 * Créé un vecteur depuis l'entrée standard
 */
template <class T>
GenericVector<T>* lireVecteur(T type)
{
	unsigned int dim;
	std::cout << "Entrez un nombre de dimensions" << std::endl;
	std::cin >> dim;
	GenericVector<T> *res = new GenericVector<T>(dim);

	for(unsigned int i=0; i<dim; i++)
	{
		T value;
		std::cout << "Entrez un nombre" << std::endl;
		std::cin >> value;
		res->set(i, value);
	}

	return res;
}

/**
 * @pre: v2->dimensions() == v1->dimensions()
 * retourne le vecteur somme des deux vecteurs passés en paramètres
 */
 template <class T>
GenericVector<T> add(const GenericVector<T> *v1, const GenericVector<T> * v2)
{
	assert(v2->dimensions() == v1->dimensions());
	unsigned int dim = v1->dimensions();
	GenericVector<T> v(dim);
	for(unsigned int i=0 ; i<dim; i++ )
		v.set(i,v1->get(i)+v2->get(i));
	return v;
}

template <class T>
GenericVector<T>& GenericVector<T>::operator=(const GenericVector<T> &v1)
{
	if(this != &v1)
	{
		if(m_vecteur != NULL) delete[] m_vecteur;
		m_dim = v1.dimensions();
		m_vecteur = new T[m_dim];

		for(unsigned int i = 0; i < m_dim; ++i)
			m_vecteur[i] = v1.get(i);
	}
	return *this;
}

/**
 * @pre: v2->dimensions() == v1->dimensions()
 * retourne le vecteur somme des deux vecteurs passés en paramètres
 */
template <class T>
GenericVector<T> GenericVector<T>::operator+(const GenericVector<T> &v1)
{
	assert(m_dim == v1.dimensions());
	GenericVector<T> v(v1.dimensions());
	for(unsigned int i=0 ; i<v1.dimensions(); i++)
		v.set(i,get(i)+v1.get(i));
	return v;
}

/**
 * Accès en lecture seule à this[i]
 */
template <class T>
const T& GenericVector<T>::operator[](const unsigned int i) const
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * Accès en lecture/écriture à this[i]
 */
template <class T>
T& GenericVector<T>::operator[](unsigned int i)
{
	assert(i < m_dim);
	return m_vecteur[i];
}

/**
 * Effectue une multiplication scalaire v1 et v2
 */ 
template <class T, class U>
T operator*(const GenericVector<T> &v1, const GenericVector<U> &v2)
{
	assert(v2.dimensions() == v1.dimensions());
	T res = 0;
	for(unsigned int i=0 ; i<v1.dimensions(); i++)
		res += v1.get(i)*v2.get(i);
	return res;
}

/**
 * Affiche un vecteur
 * @param: out le flux de sortie
 * @param: v1 le vecteur à afficher
 */
template <class T>
std::ostream & operator<<(std::ostream & out, const GenericVector<T> &v1)
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
template <class T>
std::istream & operator>>(std::istream & in, GenericVector<T> &v1)
{
	for(unsigned int i=0; i<v1.dimensions(); i++)
	{
		T value;
		in >> value;
		v1.set(i, value);
	}
	return in;
}

#endif
