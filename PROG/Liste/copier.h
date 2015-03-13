#include "liste.hh"

/** 3.1 chercher une valeur dans une liste triée
 * @param l : liste où se fait la recherche
 * @param x : valeur à chercher
 * @return position du premier élément de valeur >= x <br>
 * ou end() si un tel élément n'existe pas
 * @warning T doit posséder l'opérateur <
 */
template <class T>
static typename Liste<T>::iterator chercherTri(Liste<T> & l,const T & x) {
	typename Liste<T>::iterator it(l.begin());
	while(*it<x && it != l.end()) it++;
	return it;
}

/** 3.1 créer une copie triée par valeurs croissantes d'une liste
 * @param l : liste à copier
 * @warning T doit posséder l'opérateur <
 * @return liste triée
 */

template <class T>
static Liste<T> * copierTri(const Liste<T> & l) {
	Liste<T> *res = new Liste<T>();
	typename Liste<T>::const_iterator it = l.begin();
	typename Liste<T>::const_iterator it2 = l.end();
	while(it!=it2){
		typename Liste<T>::iterator itRes = chercherTri(*res,*it);
		res->insert(itRes,*it);
		++it;
	}	
	return res;
}
