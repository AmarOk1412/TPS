#ifndef LISTE_HH
#define LISTE_HH

#include "cyclicNode.h"

#include <cassert>
#include <iostream>

template<class T>
class Liste
{ 
  typedef DataStructure::cyclicNode<T> Chainon;
  public:
  Liste();
  ~Liste();
  Liste(const Liste<T> &l);
  
  class const_iterator 
  {
    friend class Liste;
    public:    
    ~const_iterator() { }
    
    const_iterator& operator++()
    {
      assert(*this != _l->end());
      _c = _c->next();
      return *this;
    }
    
    const_iterator& operator++(int)
    {
      return ++*this;
    }
    
    const_iterator & operator--()
    {
      assert(*this != _l->begin());
    	_c = _c->previous();
      return *this;
    }
    
    const_iterator & operator--(int)
    {
      return --*this;
    }
        
    const T& operator*()
    {      
    	return (*_c).data();
    }
    
    const T* operator->()
    {
    	return &_c->data();
    }
    
		bool operator==(const const_iterator &i)
		{
			return i._l==_l && i._c==_c;
		}
		
		bool operator!=(const const_iterator &i)
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
  
  class iterator 
  {
    friend class Liste;
    public:    
    ~iterator() { }
    
    iterator& operator++()
    {
      assert(*this != _l->end());
      _c = _c->next();
      return *this;
    }
    
    iterator& operator++(int)
    {
      return ++(*this);
    }
    
    iterator & operator--()
    {
      assert(*this != _l->begin());
    	_c = _c->previous();
      return *this;
    }
      
    iterator & operator--(int)
    {
      return --(*this);
    }  
    
    T& operator*()
    {      
    	return (*_c).data();
    }
    
    T* operator->()
    {
    	return &_c->data();
    }
    
		bool operator==(const iterator &i)
		{
			return i._l==_l && i._c==_c;
		}
		
		bool operator!=(const iterator &i)
		{
			return i._l!=_l || i._c!=_c;
		}
		
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
  const int size() const;
  T& front();
  T& back();
  const T& front() const;
  const T& back() const;
  void push_front(const T& el);
  void push_back(const T& el);
  void pop_front();
  void pop_back();
  Liste<T>& operator=(const Liste<T> &l);
  Liste<T>& operator+(const Liste<T> &l) const;

  const_iterator begin() const
  {
   return const_iterator(this, _sentinelle->next());
	}
  const_iterator end() const
  {
   return const_iterator(this, _sentinelle);
	}
	iterator begin() 
  {
   return iterator(this, _sentinelle->next());
	}
  iterator end() 
  {
   return iterator(this, _sentinelle);
	}
	
	iterator insert(iterator position, const T & x)
	{
	  Chainon* ch = new Chainon(x);
	  position.getC()->insertBefore(ch);
		if(position==end()) 
		  return begin();
		return (position--);
	}
	
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

template <class T>
Liste<T>::Liste()
{
	_sentinelle = new Chainon();
}


template <class T>
Liste<T>::~Liste()
{
	while(_sentinelle->next() != _sentinelle)
	  delete _sentinelle->next();
	delete _sentinelle;
}

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

template <class T>
Liste<T>& Liste<T>::operator+(const Liste<T> &l) const
{
  Liste<T>* res = new Liste<T>();
	typename Liste<T>::const_iterator it = begin();
	typename Liste<T>::const_iterator it2 = end();
	typename Liste<T>::const_iterator it3 = l.begin();
	typename Liste<T>::const_iterator it4 = l.end();
	while(it != it2)
	{
		res->push_back(*it);
		++it;
	}
	while(it3 != it4) {
		res->push_back(*it3);
		++it3;
	}
	return *res;
}

template <class T>
bool Liste<T>::empty() const
{
  return _sentinelle->previous() == _sentinelle 
  			 && _sentinelle->next() == _sentinelle;
}

template <class T>
const int Liste<T>::size() const
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

template <class T>
const T& Liste<T>::front() const
{
	assert(!empty());
	return _sentinelle->next()->data();
}

template <class T>
T& Liste<T>::front()
{
	assert(!empty());
	return _sentinelle->next()->data();
}

template <class T>
const T& Liste<T>::back() const
{
	assert(!empty());
	return _sentinelle->previous()->data();
}

template <class T>
T& Liste<T>::back()
{
  assert(!empty());
	return _sentinelle->previous()->data();
}
template <class T> 
void Liste<T>::push_front(const T& el)
{
	Chainon* ch = new Chainon(el);
	_sentinelle->insertAfter(ch);
}
template <class T>
void Liste<T>::push_back(const T& el)
{
	Chainon * ch = new Chainon(el);
	_sentinelle->insertBefore(ch);
}

template <class T>
void Liste<T>::pop_front()
{
  assert(!empty());
	delete _sentinelle->next();
}
template <class T>
void Liste<T>::pop_back()
{
  assert(!empty());
	delete _sentinelle->previous();
}

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
