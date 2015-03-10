#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fonctionnalités communes
#include "test_unitaire_common.hh"

// fichier qui contient l'implémentation de la classe Liste
#include "liste.hh"

//------------------------------------------------------------------------
// tests const_iterator (2.1, 2.2, 2.3)
//------------------------------------------------------------------------

// const_iterator : tester begin et op *
TEST_F(TestList, DISABLED_q22Begin)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_liste  = const_liste.begin();
  ASSERT_EQ(
	    5.5,
	    *it_liste)
    << "Erreur valeur élément de tête";
}

// const_iterator : tester assertion op *
TEST_F(TestList, DISABLED_q23AssertOpEtoile)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_liste  = const_liste.end();
  ASSERT_DEATH(*it_liste , "Assertion.*end().*failed");
}

// const_iterator : tester assertion op ++
TEST_F(TestList, DISABLED_q23AssertOpInc)
{
  const Liste<double>		liste;
  Liste<double>::const_iterator it  = liste.begin();
  ASSERT_DEATH(++it, "Assertion.*end().*failed");
}

// const_iterator : tester assertion op --
TEST_F(TestList, DISABLED_q23AssertOpDec)
{
  const Liste<double>		liste;
  Liste<double>::const_iterator it  = liste.begin();
  ASSERT_DEATH(--it, "Assertion.*begin().*failed");
}

// const_iterator : tester == et !=
TEST_F(TestList, DISABLED_q23EgaliteIterateurs)
{
  Liste<double>		liste;
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_liste = const_liste.begin();
  Liste<double>::const_iterator it_fin   = const_liste.end();
  EXPECT_TRUE (it_liste == it_fin) << "ERREUR : les deux itérateurs devraient être égaux";
  EXPECT_FALSE(it_liste != it_fin) << "ERREUR : les deux itérateurs ne devraient pas être différents";
}

// const_iterator : tester == et !=
TEST_F(TestList, DISABLED_q23EgaliteIterateursBis)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  const Liste<double> & const_liste(liste);
  Liste<double>::const_iterator it_liste = const_liste.begin();
  Liste<double>::const_iterator it_fin   = const_liste.end();
  EXPECT_FALSE(it_liste == it_fin) << "ERREUR : les deux itérateurs ne devraient pas être égaux";
  EXPECT_TRUE (it_liste != it_fin) << "ERREUR : les deux itérateurs devraient être différents";
}

// const_iterator : assertion op ->
TEST_F(TestList, DISABLED_q23AssertionOpFleche)
{
  const Liste<std::string> liste;
  Liste<std::string>::const_iterator it(liste.begin());
  ASSERT_DEATH(it->size(), "Assertion.*end().*failed");
}

// const_iterator : tester op ->
TEST_F(TestList, DISABLED_q23OpFleche)
{
  Liste<std::string> liste;
  std::deque<int>    longueurs;
  // mettre des chaînes de longueurs différentes dans la liste
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    longueurs.push_front(i+1);
    longueurs.push_back (i+1);
  }
  // vérifier les longueurs des éléments : op ->
  const Liste<std::string> & const_liste(liste);
  Liste<std::string>::const_iterator it_liste = const_liste.begin();
  Liste<std::string>::const_iterator it_fin   = const_liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    EXPECT_EQ(
	      longueurs[i],
	      it_liste->size()
	      )
      << "Erreur longueur élément " << i;
    ++it_liste;
    ++i;
  }
}

// const_iterator : parcours de liste en marche avant
TEST_F(TestList, DISABLED_q23Forward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  const Liste<double> & const_liste(liste);
  list_equals_deque_forward(const_liste, array);
}

// idem marche arrière
TEST_F(TestList, DISABLED_q23Backward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  const Liste<double> & const_liste(liste);
  list_equals_deque_backward(const_liste, array);
}

//------------------------------------------------------------------------
// tests iterator (2.5) ; idem const_iterator plus
// - modif avec op *
// - modif avec op ->
//------------------------------------------------------------------------

// iterator : tester begin et op * en consultation
TEST_F(TestList, DISABLED_q25Begin)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  Liste<double>::iterator it_liste  = liste.begin();
  ASSERT_EQ(
	    5.5,
	    *it_liste)
    << "Erreur valeur élément de tête";
}

// iterator : tester assertion op *
TEST_F(TestList, DISABLED_q25AssertOpEtoile)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  Liste<double>::iterator it_liste  = liste.end();
  ASSERT_DEATH(*it_liste , "Assertion.*end().*failed");
}

// iterator : tester assertion op ++
TEST_F(TestList, DISABLED_q25AssertOpInc)
{
  Liste<double>		liste;
  Liste<double>::iterator it  = liste.begin();
  ASSERT_DEATH(++it, "Assertion.*end().*failed");
}

// iterator : tester assertion op --
TEST_F(TestList, DISABLED_q25AssertOpDec)
{
  Liste<double>		liste;
  Liste<double>::iterator it  = liste.begin();
  ASSERT_DEATH(--it, "Assertion.*begin().*failed");
}

// iterator : tester == et !=
TEST_F(TestList, DISABLED_q25EgaliteIterateurs)
{
  Liste<double>		  liste;
  Liste<double>::iterator it_liste = liste.begin();
  Liste<double>::iterator it_fin   = liste.end();
  EXPECT_TRUE (it_liste == it_fin) << "ERREUR : les deux itérateurs devraient être égaux";
  EXPECT_FALSE(it_liste != it_fin) << "ERREUR : les deux itérateurs ne devraient pas être différents";
}

// iterator : tester == et !=
TEST_F(TestList, DISABLED_q25EgaliteIterateursBis)
{
  Liste<double>		  liste;
  liste.push_back(5.5);
  Liste<double>::iterator it_liste = liste.begin();
  Liste<double>::iterator it_fin   = liste.end();
  EXPECT_FALSE(it_liste == it_fin) << "ERREUR : les deux itérateurs ne devraient pas être égaux";
  EXPECT_TRUE (it_liste != it_fin) << "ERREUR : les deux itérateurs devraient être différents";
}

// iterator : assertion op ->
TEST_F(TestList, DISABLED_q25AssertionOpFleche)
{
  Liste<std::string> liste;
  Liste<std::string>::iterator it(liste.begin());
  ASSERT_DEATH(it->insert(0, "?"), "Assertion.*end().*failed");
}

// iterator : tester op -> (consultation)
TEST_F(TestList, DISABLED_q25OpFleche)
{
  Liste<std::string> liste;
  std::deque<int>    longueurs;
  // mettre des chaînes de longueurs différentes dans la liste
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    longueurs.push_front(i+1);
    longueurs.push_back (i+1);
  }
  // vérifier les longueurs des éléments : op ->
  Liste<std::string>::iterator it_liste = liste.begin();
  Liste<std::string>::iterator it_fin   = liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    EXPECT_EQ(
	      longueurs[i],
	      it_liste->size()
	      )
      << "Erreur longueur élément " << i;
    ++it_liste;
    ++i;
  }
}

// iterator : parcours de liste en marche avant
TEST_F(TestList, DISABLED_q25Forward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  list_equals_deque_forward(liste, array);
}

// idem marche arrière
TEST_F(TestList, DISABLED_q25Backward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  list_equals_deque_backward(liste, array);
}

// iterator : test op * modification
TEST_F(TestList, DISABLED_q25opEtoileModif)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  // modifier les éléments de la liste et du deque
  Liste<double>::iterator it_liste = liste.begin();
  Liste<double>::iterator it_fin   = liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    *it_liste  *= *it_liste;
    array[i] *= array[i];
    ++it_liste; ++i;
  }
  // vérifier l'égalité de la liste et du array
  list_equals_deque_forward(liste, array);
}

// iterator : test op -> modification
TEST_F(TestList, DISABLED_q25opFlecheModif)
{
  Liste<std::string>	  liste;
  std::deque<std::string> array;
  // mettre des chaînes de longueurs différentes dans la liste
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    array.push_front(std::string(i+1, i + 'A'));
    array.push_back (std::string(i+1, i + '1'));
  }
  // modifier les chaînes
  Liste<std::string>::iterator it_liste = liste.begin();
  Liste<std::string>::iterator it_fin   = liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    it_liste->insert(0, "(");
    it_liste->append(")");
    array[i].insert(0, "(");
    array[i].append(")");
    ++it_liste; ++i;
  }
  // vérifier l'égalité de la liste et du array
  list_equals_deque_forward(liste, array);
}
