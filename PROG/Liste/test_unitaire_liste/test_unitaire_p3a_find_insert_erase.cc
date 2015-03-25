#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fonctionnalités communes
#include "test_unitaire_common.hh"

// fichier qui contient l'implémentation de la classe Liste
#include "liste.hh"

//------------------------------------------------------------------------
// test find q3.1
//------------------------------------------------------------------------

// test find dans liste vide
TEST_F(TestList, q31FindListeVide)
{
  Liste<double>	liste;
  Liste<double>::iterator pos = find(liste.begin(), liste.end(), 3.141519);
  EXPECT_EQ(
	    liste.end(),
	    pos
	    )
    << "Erreur recherche liste vide";
}

// test find dans liste d'un élément
TEST_F(TestList, q31FindListe1Element)
{
  Liste<double>	liste;
  liste.push_back(3.141519);
  // élément absent
  Liste<double>::iterator pos = find(liste.begin(), liste.end(), -10.5);
  EXPECT_EQ(
	    liste.end(),
	    pos
	    )
    << "Erreur recherche élément absent";

  // élément présent
  pos = find(liste.begin(), liste.end(), 3.141519);
  EXPECT_EQ(
	    liste.begin(),
	    pos
	    )
    << "Erreur recherche élément présent";
}

// test find dans liste de n éléments
TEST_F(TestList, q31FindListe)
{
  Liste<double>	liste;
  std::deque<double> array;
  ajouter_elts(liste, array);

  // chercher dans la liste tous les éléments du array
  for (unsigned int i = 0; i < array.size(); ++i) {
    // chercher un élément présent
    Liste<double>::iterator pos = find(liste.begin(), liste.end(), array[i]);
    ASSERT_NE(
	      liste.end(),
	      pos
	      )
      << "Erreur recherche élément présent à l'indice " << i << " valeur " << array[i];

    EXPECT_EQ(
	      array[i],
	      *pos
	      )
      << "Erreur valeur trouvée par la recherche";

    // chercher un élément absent (Attention : -0 = 0 !)
    pos = find(liste.begin(), liste.end(), -array[i]-1);
    EXPECT_EQ(
	      liste.end(),
	      pos
	      )
      << "Erreur recherche élément absent de valeur " << -array[i]-1;
  }
}

//------------------------------------------------------------------------
// test insert q3.2
//------------------------------------------------------------------------

// insert : assertion itérateur sur liste courante...
TEST_F(TestList, q32InsertCurrentListAssertion)
{
  Liste<double> liste1;
  liste1.push_back(3.14159);
  Liste<double> liste2;
  liste2.push_back(-77.77); 
  ASSERT_DEATH(liste1.insert(liste2.begin(), 3.14159), "Assertion.*== *this.*failed");  
}

// test insert dans liste vide
TEST_F(TestList, q32InsertListeVide)
{
  Liste<double>	liste;
  EXPECT_TRUE(liste.empty()) << "Liste devrait être vide";
  // insérer un élément
  Liste<double>::iterator new_elt = liste.insert(liste.begin(), 3.14159);
  // vérif taille
  EXPECT_FALSE(liste.empty()) << "Liste ne devrait PAS être vide";
  EXPECT_EQ(
	    (unsigned int) 1,
	    (unsigned int) liste.size()) << "Erreur taille liste";
  // vérif valeur élément inséré
  EXPECT_EQ(
	    3.14159,
	    *liste.begin())
    << "Erreur valeur élément de tête";
  EXPECT_EQ(
	    3.14159,
	    *new_elt)
    << "Erreur valeur élément inséré";
}

// test insert en tête de liste non vide
TEST_F(TestList, q32InsertTeteListe)
{
  Liste<double>		liste;
  std::deque<double>	array;
  // initialiser la liste et le tableau avec push_back/front
  ajouter_elts(liste, array);

  // insertion en tête et vérification
  inserer_elts(liste, array, front);

  // encore une vérification
  list_equals_deque_forward(liste, array);
}

// test insert en fin de liste non vide
TEST_F(TestList, q32InsertFinListe)
{
  Liste<double>		liste;
  std::deque<double>	array;
  // initialiser la liste et le tableau avec push_back/front
  ajouter_elts(liste, array);

  // insertion en fin et vérification
  inserer_elts(liste, array, back);

  // encore une vérification
  list_equals_deque_forward(liste, array);
}

// test insert au hasard dans liste non vide
TEST_F(TestList, q32InsertHasardListe)
{
  Liste<double>		liste;
  std::deque<double>	array;
  // initialiser la liste et le tableau avec push_back/front
  ajouter_elts(liste, array);

  // insertion en fin et vérification
  inserer_elts(liste, array, alea);

  // encore une vérification
  list_equals_deque_forward(liste, array);
}

//------------------------------------------------------------------------
// tests erase q3.3
//------------------------------------------------------------------------

// erase : assertion itérateur sur liste courante...
TEST_F(TestList, q33EraseCurrentListAssertion)
{
  Liste<double> liste1;
  liste1.push_back(3.14159);
  Liste<double> liste2;
  liste2.push_back(-77.77); 
  ASSERT_DEATH(liste1.erase(liste2.begin()), "Assertion.*== *this.*failed");  
}

// erase : assertion itérateur fin de liste
TEST_F(TestList, q33EraseEndListAssertion)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.erase(liste.begin()), "Assertion.*end().*failed");  
}

// erase : suppression dans liste d'un élément
TEST_F(TestList, q33EraseListe1Element)
{
  Liste<double> liste;
  liste.push_back(3.14159);
  Liste<double>::iterator next = liste.erase(liste.begin());
  EXPECT_TRUE(liste.empty());
  EXPECT_EQ(
	    liste.end(),
	    next
	    )
    << "Erreur itérateur résultat";
}

// erase : suppression dans liste quelconque
TEST_F(TestList, q33Erase)
{
  // mettre des éléments dans une liste et un tableau
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array);
  // vérification préalable
  list_equals_deque_forward(liste, array);
  // supprimer des éléments de la liste et du tableau
  for (unsigned int i = 0; i < array.size(); ++i) {
    Liste<double>::iterator	 liste_it = liste.begin();
    std::deque<double>::iterator array_it = array.begin();
    int pos = rand() % array.size();
    // positionner les itérateurs
    while (pos >= 0) {
      ++liste_it ; ++array_it ; --pos;
    }
    // effectuer la suppression
    liste_it = liste.erase(liste_it);
    array_it = array.erase(array_it);
    // vérifier tailles
    EXPECT_EQ(
	      array.size(),
	      liste.size())
      << "Erreur taille liste";

    if (array_it == array.end()) {
      EXPECT_EQ(
		liste.end(),
		liste_it)
	<< "Erreur itérateur résultat";
    }
    else {
      // vérifier valeur
      EXPECT_EQ(
		*array_it,
		*liste_it)
	<< "Erreur valeur élément inséré";
    }
  }
}
