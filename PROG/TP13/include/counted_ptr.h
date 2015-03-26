// -*- c++ -*-

#ifndef COUNTED_PTR_H
#define COUNTED_PTR_H
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	counted_ptr
///
/// \brief	Classe gérant un "smart pointer". 
///
/// \author	Jean Christophe Engel, Fabrice Lamarche, University Of Rennes 1
/// \date	23/04/2010
////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class counted_ptr {
public:
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	explicit counted_ptr(T * pointer = 0)
  /// \brief	Constructeur
  /// \param	pointer Si non nul, un pointeur vers une variable allouée dynamiquement.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  explicit counted_ptr(T * pointer = 0) ;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual ~counted_ptr(void)
  /// \brief	Destructeur, libère la donnée s'il s'agit du dernier pointeur qui la désigne.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual ~counted_ptr() ;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	counted_ptr(const counted_ptr & smartPointer)
  /// \brief	Constructeur de copie. 
  /// \param	smartPointer : le "smart pointer" à copier. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  counted_ptr(const counted_ptr & smartPointer) ;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	counted_ptr & operator = (const counted_ptr & smartPointer)
  /// \brief	Opérateur d'affectation. 
  /// \param	smartPointer : l'opérande de droite de l'affectation. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  counted_ptr & operator = (const counted_ptr & smartPointer) ;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief	Constructeur de transtypage. Permet de pointer sur une instance de classe U
  ///		via un pointeur de type T, U héritant T.
  /// \param smartPointer 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class U>
  counted_ptr(const counted_ptr<U> & smartPointer) ;

  /// Donner à counted_ptr<U> accès à la partie privée de counted_ptr<T>
  template <class U> friend class counted_ptr;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	bool isnull () const
  /// \return	vrai si le pointeur ne désigne rien
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  bool isnull() const;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	T & operator * () const
  /// \brief	Accès à la variable désignée par le pointeur. 
  /// \return	La variable désignée par le pointeur. 
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  T & operator * () const	;

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	T * operator -> () const
  /// \brief	Opérateur d'accès aux attributs / méthodes de la variable pointée. 
  /// \return	adresse de la variable désignée par le pointeur.
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  T * operator -> () const ;

private:
  //------------------------------------------------------------------------
  // méthodes d'implémentation
  //-----------------------------------------------------------------------

  // acquérir la ressource désignée par cp
  void acquerir(const counted_ptr<T> & cp) ;

  // idem entre un counted_ptr<T> et un counted_ptr<U>
  template <class U>
  void acquerir(const counted_ptr<U> & cp) ;

  // libérer la ressource
  void liberer() ;

private:
  //------------------------------------------------------------------------
  // attributs
  //-----------------------------------------------------------------------
  unsigned int * m_counter ; // Pointeur vers le compteur de références
  T   * m_ptr ;	    // Pointeur vers l'objet désigné
}; // counted_ptr<T>

///--------------------------------------------------------------------------------
/// méthodes publiques
///--------------------------------------------------------------------------------

// constructeur "normal"
template <class T>
counted_ptr<T>::counted_ptr(T * pointer)
{
  if (pointer != 0) 
  {
    m_ptr = static_cast<T*>(pointer) ;
    m_counter = new unsigned int(1) ;
  }
  else		    
  {
    m_ptr = 0 ;
    m_counter = 0 ;
  }
}

// destructeur
template <class T>
counted_ptr<T>::~counted_ptr() { 
  liberer();
}

// constructeur de copie. 
template <class T>
counted_ptr<T>::counted_ptr(const counted_ptr<T> & smartPointer)
{ 
  acquerir(smartPointer);
}

// Opérateur d'affectation. 
template <class T>
counted_ptr<T> & 
counted_ptr<T>::operator = (const counted_ptr<T> & smartPointer)
{
  if(m_counter != smartPointer.m_counter)
  {
    // les deux smart pointers ne désignent pas la même variable
    liberer();
    acquerir(smartPointer);
  }
  return *this;
}

// constructeur de transtypage
template <class T>
template <class U>
counted_ptr<T>::counted_ptr(const counted_ptr<U> & smartPointer)
{ 
  acquerir(smartPointer);
}

// déterminer si le pointeur désigne quelque chose
template <class T>
bool
counted_ptr<T>::isnull() const { return m_ptr == 0; }

// opérateur d'indirection *
template <class T>
T &
counted_ptr<T>::operator * () const 
{
  assert (! isnull());
  return *m_ptr;
}

// opérateur d'indirection ->
template <class T>
T *
counted_ptr<T>::operator -> () const 
{
  assert (! isnull());
  return m_ptr ;
}

//------------------------------------------------------------------------
// méthodes privées d'implémentation
//-----------------------------------------------------------------------

// acquérir la ressource désignée par cp
template <class T>
void
counted_ptr<T>::acquerir(const counted_ptr<T> & cp)
{
  if (! cp.isnull()) {
    m_ptr = cp.m_ptr ;
    m_counter = cp.m_counter ;
    (*m_counter)++ ;
  }
  else 
  {
    m_ptr = 0 ;
    m_counter = 0 ;
  }
}

// idem entre un counted_ptr<T> et un counted_ptr<U>
template <class T>
template <class U>
void
counted_ptr<T>::acquerir(const counted_ptr<U> & cp)
{
  if (! cp.isnull()) {
    m_ptr = static_cast<T*>(cp.m_ptr) ;
    m_counter = cp.m_counter ;
    (*m_counter)++ ;	
  }
  else 
  {
    m_ptr = 0 ;
    m_counter = 0 ;
  }
}

// libérer la ressource
template <class T>
void
counted_ptr<T>::liberer()
{
  if (m_ptr != 0) {
    (*m_counter)-- ;
    if ((*m_counter) == 0) {
      delete m_ptr;
      delete m_counter ;
    } // détruire la variable qui n'est plus utilisée
  }
}
#endif // COUNTED_PTR_H
