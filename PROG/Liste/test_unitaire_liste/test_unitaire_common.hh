#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>
#include "liste.hh"

enum Position { front, alea, back };

// To use a test fixture, derive a class from testing::Test.
class TestList : public testing::Test
{
protected:

  // The UTC time (in seconds) when the test starts
  time_t m_start_time;

  // SetUp() is run immediately before a test starts.
  virtual void SetUp() {
    m_start_time = time(NULL);
    srand48(m_start_time);
  }

  // TearDown() is invoked immediately after a test finishes.
  virtual void TearDown() {
    // Gets the time when the test finishes
    const time_t end_time = time(NULL);

    // Asserts that the test took no more than ~1 second.
    EXPECT_TRUE(end_time - m_start_time <= 1)
      << "The test took too long.";
  }

  //------------------------------------------------------------------------
  // fonctions utilitaires
  //------------------------------------------------------------------------

  // ajouter des élts dans un tableau et une liste
  // avec push_front ou push_back
  void
  ajouter_elts(
	       Liste<double> & liste,
	       std::deque<double> & array,
	       Position ici = alea
	       )
  {
    const int array_size = 100 + rand() % 100;
    for (int i = 0; i < array_size; ++i) {
      double x = 5 + drand48();
      bool ajoutTete = (ici == front) || (ici == alea && rand() % 2 == 0);
      if (ajoutTete) {
	// ajout en tête
	array.push_front(i * x * x);
	liste.push_front(i * x * x);
      }
      else {
	// ajout en fin
	array.push_back(i * x + 1);
	liste.push_back(i * x + 1);
      }
    }
  }

  // ajouter des éléments dans un tableau
  void
  ajouter_elts(
	       std::deque<double> & array
	       )
  {
    const int array_size = 100 + rand() % 100;
    for (int i = 0; i < array_size; ++i) {
      array.push_back(5 + drand48());
    }
  }

  // copier un tableau dans une liste
  void
  copier_array_list(
		    const std::deque<double> & array,
		    Liste<double> & liste
		    )
  {
    std::deque<double>::const_iterator it     = array.begin();
    std::deque<double>::const_iterator it_fin = array.end();
    while (it != it_fin) {
      liste.push_back(*it);
      ++it;
    }
  }

  // ajouter des élts dans un array et une liste
  // avec insert
  // vérifier que l'insertion est correcte
  void
  inserer_elts(
	       Liste<double> & liste,
	       std::deque<double> & array,
	       Position ici = alea
	       )
  {
    const int array_size = 100 + rand() % 100;
    for (int i = 0; i < array_size; ++i) {
      double x = 5 + drand48();
      if (ici == front) {
			// insertion en tête
	array.push_front(i * x * x);
	Liste<double>::iterator new_elt = liste.insert(liste.begin(), i * x * x);
	// vérifier tailles
	EXPECT_EQ(
		  array.size(),
		  liste.size()) << "Erreur taille liste";
	// vérifier valeur
	EXPECT_EQ(
		  *array.begin(),
		  *liste.begin())
	  << "Erreur valeur élément de tête";
	EXPECT_EQ(
		  *array.begin(),
		  *new_elt)
	  << "Erreur valeur élément inséré";
      } // insertion en tête
      else if (ici == back) {
	// insertion en fin
	array.push_back(i * x + 1);
	Liste<double>::iterator new_elt = liste.insert(liste.end(), i * x + 1);
	// vérifier tailles
	EXPECT_EQ(
		  array.size(),
		  liste.size()) << "Erreur taille liste";
//	 vérifier valeur
	EXPECT_EQ( *--array.end(), *--liste.end()) << "Erreur valeur élément de tête";
	EXPECT_EQ( *--array.end(), *new_elt) << "Erreur valeur élément inséré";
      } // insertion en fin
      else {
	// insertion à une position quelconque...
	Liste<double>::iterator	     liste_it = liste.begin();
	std::deque<double>::iterator array_it = array.begin();
	int pos = rand() % (1+array.size());
	// positionner les itérateurs
	while (pos >= 0) {
	  ++liste_it ; ++array_it ; --pos;
	}
//	// effectuer l'insertion
//	liste_it = liste.insert(liste_it, i * i * x + 1);
//	array_it = array.insert(array_it, i * i * x + 1);
	// vérifier tailles
	EXPECT_EQ(
		  array.size(),
		  liste.size())
	  << "Erreur taille liste";
	// vérifier valeur
	EXPECT_EQ(
		  *array_it,
		  *liste_it)
	  << "Erreur valeur élément inséré";
      } // insertion en position quelconque
    } // for
  }

  // comparer les élts d'une liste et ceux d'un deque
  // vide la liste de son contenu
  // requiert size, front, pop_front, back, pop_back
  template <class T>
  void
  list_equals_deque(
		    Liste<T> & list,
		    const std::deque<T> & array,
		    Position ici
		    )
  {
    unsigned int nb = array.size();
    EXPECT_EQ(
	      (unsigned int) nb,
	      (unsigned int) list.size())
      << "Erreur taille liste";
    unsigned int ideb = 0, ifin = array.size() - 1;
    while (! list.empty())
      {
	EXPECT_EQ(
		  (unsigned int) nb,
		  (unsigned int) list.size())
	  << "Erreur taille liste";

	// ôter soit en tête, soit en queue
	bool retraitTete = (ici == front) || (ici == alea && rand() % 2 == 0);
	if (retraitTete) {
	  EXPECT_EQ(
		    array[ideb],
		    list.front())
	    << "Erreur élément de rang " << ideb;
	  list.pop_front();
	  ++ideb;
	}
	else {
	  EXPECT_EQ(
		    array[ifin],
		    list.back())
	    << "Erreur élément de rang " << ifin;
	  list.pop_back();
	  --ifin;
	}
	nb -= 1;
      }
  }

  // comparer les élts d'une liste et ceux d'un deque
  // parcours de la liste avec const_iterator
  // requiert begin, end, ++, *, !=
  template <class T>
  void
  list_equals_deque_forward(
			    const Liste<T>      & list,
			    const std::deque<T> & array
			    )
  {
#ifdef DEBUG
    std::cout << "test égalité avec const_iterator forward\n";
#endif
    EXPECT_EQ(
	      (unsigned int) array.size(),
	      (unsigned int) list.size())
      << "Erreur taille liste";

    unsigned int i_tab = 0;
    typename Liste<T>::const_iterator it_liste  = list.begin();
    typename Liste<T>::const_iterator it_fin    = list.end();
    while (it_liste != it_fin)
      {
	EXPECT_EQ(
		  array[i_tab],
		  *it_liste)
	  << "Erreur élément de rang " << i_tab;
	++i_tab;
	++it_liste;
      }
  }

  // comparer les élts d'une liste et ceux d'un deque
  // parcours de la liste avec const_iterator
  // requiert begin, end, --, *
  template <class T>
  void
  list_equals_deque_backward(
			     const Liste<T>      & list,
			     const std::deque<T> & array
			     )
  {
#ifdef DEBUG
    std::cout << "test égalité avec const_iterator backward\n";
#endif
    EXPECT_EQ(
	      (unsigned int) array.size(),
	      (unsigned int) list.size())
      << "Erreur taille liste";

    unsigned int i_tab = array.size();
    typename Liste<T>::const_iterator it_liste  = list.end();
    typename Liste<T>::const_iterator it_fin    = list.begin();
    while (it_liste != it_fin)
      {
	--i_tab;
	--it_liste;
	EXPECT_EQ(
		  array[i_tab],
		  *it_liste)
	  << "Erreur élément de rang " << i_tab;
      }
  }

  //------------------------------------------------------------------------
  // idem avec iterator
  //------------------------------------------------------------------------

  // comparer les élts d'une liste et ceux d'un deque
  // parcours de la liste avec iterator
  // requiert begin, end, ++, *, !=
  template <class T>
  void
  list_equals_deque_forward(
			    Liste<T>		& list,
			    const std::deque<T> & array
			    )
  {
#ifdef DEBUG
    std::cout << "test égalité avec iterator forward\n";
#endif
    EXPECT_EQ(
	      (unsigned int) array.size(),
	      (unsigned int) list.size())
      << "Erreur taille liste";

    unsigned int i_tab = 0;
    typename Liste<T>::iterator it_liste  = list.begin();
    typename Liste<T>::iterator it_fin    = list.end();
    while (it_liste != it_fin)
      {
	EXPECT_EQ(
		  array[i_tab],
		  *it_liste)
	  << "Erreur élément de rang " << i_tab;
	++i_tab;
	++it_liste;
      }
  }

  // comparer les élts d'une liste et ceux d'un deque
  // parcours de la liste avec iterator
  // requiert begin, end, --, *
  template <class T>
  void
  list_equals_deque_backward(
			     Liste<T>		 & list,
			     const std::deque<T> & array
			     )
  {
#ifdef DEBUG
    std::cout << "test égalité avec iterator backward\n";
#endif
    EXPECT_EQ(
	      (unsigned int) array.size(),
	      (unsigned int) list.size())
      << "Erreur taille liste";

    unsigned int i_tab = array.size();
    typename Liste<T>::iterator it_liste  = list.end();
    typename Liste<T>::iterator it_fin    = list.begin();
    while (it_liste != it_fin)
      {
	--i_tab;
	--it_liste;
	EXPECT_EQ(
		  array[i_tab],
		  *it_liste)
	  << "Erreur élément de rang " << i_tab;
      }
  }
};
