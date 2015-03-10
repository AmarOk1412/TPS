/** \brief Ce fichier doit contenir la déclaration de la classe vecteur
    Attention, elle ne doit contenir aucune implémentation de méthode / fonction
*/

#ifndef _GENERICVECTOR_H
#define _GENERICVECTOR_H

#include <iostream>

template <class T>
class GenericVector {
public :
  GenericVector(unsigned int nb_dim = 3, T val_init = T());
  ~GenericVector();
  GenericVector(const GenericVector<T> &o);
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

// Prototypes des fonctions
template <class T>
void afficherVecteur(const GenericVector<T> *v);
template <class T>
GenericVector<T>* lireVecteur();
template <class T>
GenericVector<T> add(const GenericVector<T> *v1, const GenericVector<T> * v2);
template <class T>
T operator*(const GenericVector<T> &v1, const GenericVector<T> &v2);
template <class T>
std::ostream & operator<<(std::ostream & out, const GenericVector<T> &v1);
template <class T>
std::istream & operator>>(std::istream & in, GenericVector<T> &v1);

#endif
