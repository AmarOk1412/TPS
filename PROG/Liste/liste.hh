#ifndef LISTE_HH
#define LISTE_HH

#include "cyclicNode.h"

#include <cassert>
#include <iostream>

//class Liste
template<class T>
class Liste
{ 
  typedef DataStructure::cyclicNode<T> Chainon;
  public:
  Liste();
  ~Liste();
  Liste(const Liste<T> &l);
  
  //class const_iterator
  class const_iterator 
  {
    friend class Liste;
    public:    
    ~const_iterator() { }
    
    /** opérator ++ préfixé
    *	positionne l'itérateur sur l'élément suivant
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    const_iterator& operator++()
    {
      assert(*this != _l->end());
      _c = _c->next();
      return *this;
    }
    
    /** opérator ++ postfixé
    *	positionne l'itérateur sur l'élément suivant
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    const_iterator& operator++(int)
    {
      return ++*this;
    }
    
    /** opérator -- préfixé
    *	positionne l'itérateur sur l'élément précédent
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    const_iterator & operator--()
    {
      assert(*this != _l->begin());
    	_c = _c->previous();
      return *this;
    }
    
    /** opérator -- postfixé
    *	positionne l'itérateur sur l'élément précédent
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    const_iterator & operator--(int)
    {
      return --*this;
    }
        
    /** opérator d'indirection * (accès NON modifiable)
    *	@pre l'itérateur désigne une position valide (!= end())
    *	@return valeur de l'élément désigné par l'itérateur
    */    
    const T& operator*() const 
    {      
    	return (*_c).data();
    }
    
    /** opérator d'indirection -> (accès NON modifiable)
    *	@pre l'itérateur désigne une position valide(!= end())
    *	@return adresse de l'élément désigné par l'itérateur
    */  
    const T* operator->() const
    {
    	return &_c->data();
    }
    
    /** opérator de comparaison ==
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return true si les deux itérateurs ont la même position, false sinon.
    */  
		bool operator==(const const_iterator &i) const
		{
			return i._l==_l && i._c==_c;
		}
		
		/** opérator de comparaison !=
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return true si les deux itérateurs ont des positions différentes, false sinon
    */
		bool operator!=(const const_iterator &i) const
		{
			return i._l!=_l || i._c!=_c;
		}
		
    protected:
    private:
    const_iterator(const Liste* l, Chainon* c)
    {
    	_l=l;
    	_c=c;
    }
    
    const Liste<T>* _l;
    Chainon* _c;   
  };
  
  //class iterator
  class iterator 
  {
    friend class Liste;
    public:    
    ~iterator() { }
    
    /** opérator ++ préfixé
    *	positionne l'itérateur sur l'élément suivant
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    iterator& operator++()
    {
      assert(*this != _l->end());
      _c = _c->next();
      return *this;
    }
    
  	/** opérator ++ postfixé
    *	positionne l'itérateur sur l'élément suivant
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    iterator& operator++(int)
    {
      return ++(*this);
    }
    
    /** opérator -- préfixé
    *	positionne l'itérateur sur l'élément précédent
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */
    iterator & operator--()
    {
      assert(*this != _l->begin());
    	_c = _c->previous();
      return *this;
    }
     
    /** opérator -- postfixé
    *	positionne l'itérateur sur l'élément précédent
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return nouvelle valeur de l'itérateur
    */ 
    iterator & operator--(int)
    {
      return --(*this);
    }  
    
    /** opérator d'indirection * 
    *	@pre l'itérateur désigne une position valide (!= end())
    *	@return valeur de l'élément désigné par l'itérateur
    */
    T& operator*() const
    {      
    	return (*_c).data();
    }
    
    /** opérator d'indirection ->
    *	@pre l'itérateur désigne une position valide(!= end())
    *	@return adresse de l'élément désigné par l'itérateur
    */  
    T* operator->() const
    {
    	return &_c->data();
    }
    
    /** opérator de comparaison ==
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return true si les deux itérateurs ont la même position, false sinon.
    */ 
		bool operator==(const iterator &i) const
		{
			return i._l==_l && i._c==_c;
		}
		
		/** opérator de comparaison !=
    *	@pre l'itérateur désigne une position valide dans la liste (!= end())
    *	@return true si les deux itérateurs ont des positions différentes, false sinon
    */
		bool operator!=(const iterator &i) const
		{
			return i._l!=_l || i._c!=_c;
		}
		
		/** Récupérer un chainon
    *	@return l'adresse du chainon désigné par l'itérateur
    */
		Chainon* getC()
		{
		  return _c;
		}
		
    protected:
    private:
    iterator(Liste* l, Chainon* c)
    {
    	_l=l;
    	_c=c;
    }
    
    Liste<T>* _l;
    Chainon* _c;   
  };
    
  bool empty() const;
  unsigned int size() const;
  T& front();
  T& back();
  const T& front() const;
  const T& back() const;
  void push_front(const T& el);
  void push_back(const T& el);
  void pop_front();
  void pop_back();
  Liste<T>& operator=(const Liste<T> &l);
  Liste<T> operator+(const Liste<T> &l) const;

	/** Retourner un itérateur qui désigne le premier élément de la liste
	*/
  const_iterator begin() const
  {
   return const_iterator(this, _sentinelle->next());
	}
	
	/** Retourner un itérateur qui désigne la sentinelle de la liste
	*/
  const_iterator end() const
  {
   return const_iterator(this, _sentinelle);
	}
	
	/** Retourner un itérateur qui désigne le premier élément de la liste
	*/
	iterator begin() 
  {
   return iterator(this, _sentinelle->next());
	}
	
	/** Retourner un itérateur qui désigne la sentinelle de la liste
	*/
  iterator end() 
  {
   return iterator(this, _sentinelle);
	}
	
	/** Insérer un nouvel élément
	*	@param position : itérateur qui désigne l'élément qui suit l'élément inséré
	*	@param x : valeur de l'élément inséré
	* @return itérateur qui désigne l'élément x
	*/
	iterator insert(iterator position, const T & x)
	{
	  Chainon* ch = new Chainon(x);
	  position.getC()->insertBefore(ch);
		if(position==end()) 
		  return begin();
		return (position--);
	}
	
	/** Supprimer l'élément désigné par l'itérateur passé en paramètre
	*	@param position : itérateur qui désigne l'élément à supprimer
	* @pre l'élément à supprimer existe
	* @return itérateur qui désigne l'élément qui suit l'élément supprimé
	*/
	iterator erase(iterator position)
	{
		assert(position!=end());
		typename Liste<T>::iterator res = (position++);
		delete position.getC();
		return res;
	}
    
  protected:
  Chainon* _sentinelle;
};

/** Constructeur
*/
template <class T>
Liste<T>::Liste()
{
	_sentinelle = new Chainon();
}

/** Destructeur
*/
template <class T>
Liste<T>::~Liste()
{
	while(!empty())
	  pop_back();
	delete _sentinelle;
}

/** Constructeur de copie
*@param une liste 
*/
template <class T>
Liste<T>::Liste(const Liste<T> &l)
{
  _sentinelle = new Chainon();
  typename Liste<T>::const_iterator it = l.begin();	
	typename Liste<T>::const_iterator end = l.end();
	while(it != end)
	{
		push_back(*it);
		++it;
	}
}

/** opérateur d'affectation =
* @param l : la référence d'une liste
* @return une référence vers une liste
*/
template <class T>
Liste<T>& Liste<T>::operator=(const Liste<T> &l)
{
	if(this != &l){
	  if(_sentinelle != NULL) delete _sentinelle;
		_sentinelle = new Chainon();
		typename Liste<T>::const_iterator it = l.begin();	
		typename Liste<T>::const_iterator end = l.end();
		while(it != end)
		{
			push_back(*it);
			++it;
		}
	}
	return *this;
}

/** Opérateur d'affichage
*	@param o : flux de sortie
*	@param l : une liste
* @return un flux de sortie
*/
template <class T>
std::ostream & operator<< (std::ostream & o, Liste<T> const& l)
{
	o << "<";
  typename Liste<T>::const_iterator it  = l.begin();
  typename Liste<T>::const_iterator fin = l.end();
  while (it != fin) {
    o << *it << " ";
    ++it;
  }
  o << ">\n";
  return o;
}

/** Opérateur de concaténation +
*	@param l : une liste
* @return une référence vers une nouvelle liste qui résulte de la concaténation 
* de this avec la liste passé en paramètre
*/
template <class T>
Liste<T> Liste<T>::operator+(const Liste<T> &l) const
{
  Liste<T> res;
	typename Liste<T>::const_iterator it = begin();
	typename Liste<T>::const_iterator it2 = end();
	typename Liste<T>::const_iterator it3 = l.begin();
	typename Liste<T>::const_iterator it4 = l.end();
	while(it != it2)
	{
		res.push_back(*it);
		++it;
	}
	while(it3 != it4) {
		res.push_back(*it3);
		++it3;
	}
	return res;
}

/** Liste vide
* @return true si la liste est vide, false sinon
*/
template <class T>
bool Liste<T>::empty() const
{
  return _sentinelle->previous() == _sentinelle 
  			 && _sentinelle->next() == _sentinelle;
}

/** Taille de la liste
* @return un entier qui correspond à la taille de la liste
*/
template <class T>
unsigned int Liste<T>::size() const
{
  int res = 0;
  Chainon* it = _sentinelle;
	while(it->next() != _sentinelle)
	{
	  ++res;
	  it = it->next();
	}
	return res;
}

/** Renvoyer la valeur du premier élément de la liste (accès NON modifiable)
* @return la valeur du premier élément de la liste
*/
template <class T>
const T& Liste<T>::front() const
{
	assert(!empty());
	return _sentinelle->next()->data();
}

/** Renvoyer la valeur du premier élément de la liste
* @return la valeur du premier élément de la liste
*/
template <class T>
T& Liste<T>::front()
{
	assert(!empty());
	return _sentinelle->next()->data();
}

/** Renvoyer la valeur du dernier élément de la liste (accès NON modifiable)
* @return la valeur du dernier élément de la liste
*/
template <class T>
const T& Liste<T>::back() const
{
	assert(!empty());
	return _sentinelle->previous()->data();
}

/** Renvoyer la valeur du dernier élément de la liste 
* @return la valeur du dernier élément de la liste
*/
template <class T>
T& Liste<T>::back()
{
  assert(!empty());
	return _sentinelle->previous()->data();
}

/** Insérer un élément en début de liste
* @param el : la valeur de l'élément
*/
template <class T> 
void Liste<T>::push_front(const T& el)
{
	Chainon* ch = new Chainon(el);
	_sentinelle->insertAfter(ch);
}

/** Insérer un élément en fin de liste
* @param el : la valeur de l'élément
*/
template <class T>
void Liste<T>::push_back(const T& el)
{
	Chainon* ch = new Chainon(el);
	_sentinelle->insertBefore(ch);
}

/** Supprimer le premier élément de la liste
*/
template <class T>
void Liste<T>::pop_front()
{
  assert(!empty());
	delete _sentinelle->next();
}

/** Supprimer le dernier élément de la liste
*/
template <class T>
void Liste<T>::pop_back()
{
  assert(!empty());
	delete _sentinelle->previous();
}

/** Chercher un élément dans la séquence [premier, dernier]
*	@param premier : début de la séquence
*	@param dernier : fin de séquence
* @param x       : valeur cherchée
* @return itérateur qui désigne x s'il est trouvé ; cet itérateur est égal à dernier si x est absent
*/
template<class T>
typename Liste<T>::iterator
find(typename Liste<T>::iterator premier, typename Liste<T>::iterator dernier, const T& x)
{
  typename Liste<T>::iterator it = premier;
  
  while(it != dernier)
  {
    if(*it == x)
      break;
    ++it;
  }
  
  return it;
}

#endif
