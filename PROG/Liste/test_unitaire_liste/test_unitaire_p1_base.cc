#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fonctionnalités communes
#include "test_unitaire_common.hh"

// fichier qui contient l'implémentation de la classe Liste
#include "liste.hh"

//------------------------------------------------------------------------
// tests opérations bases liste (q1.1)
//------------------------------------------------------------------------

// initialiser liste vide
// - constructeur
// - empty
// - size
TEST_F(TestList, q11Init)
{
  Liste<double> liste;
  ASSERT_TRUE(liste.empty()) << "Liste devrait être vide";
  EXPECT_EQ(
	    (unsigned int) 0,
	    (unsigned int) liste.size()) << "Erreur taille liste";

  // test const : empty, size
  const Liste<double> & cl(liste);
  ASSERT_TRUE(cl.empty()) << "Liste devrait être vide";
  EXPECT_EQ(
	    (unsigned int) 0,
	    (unsigned int) cl.size()) << "Erreur taille liste";
}

// front() : assertion ! empty()
TEST_F(TestList, q11FrontAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.front(), "Assertion.*! *empty().*failed");
}

// front() const : assertion ! empty()
TEST_F(TestList, q11FrontAssertConst)
{
  const Liste<double> liste;
  ASSERT_DEATH(liste.front(), "Assertion.*! *empty().*failed");
}

// push_front, empty, size, front
TEST_F(TestList, q11Front)
{
  Liste<double> liste;
  unsigned int i;
  double x = 1.1;
  for (i = 1; i <= 5; ++i) {
    liste.push_front(i * x * x);
    ASSERT_TRUE(! liste.empty()) << "Liste ne devrait pas être vide";
    EXPECT_EQ(
	      (unsigned int) i,
	      (unsigned int) liste.size()) << "Erreur taille liste";
    EXPECT_EQ(
	      i * x * x,
	      liste.front()) << "Erreur élément tête";
  }

  // test const : empty, size, front
  const Liste<double> & cl(liste);
  ASSERT_TRUE(! cl.empty()) << "Liste ne devrait pas être vide";
  EXPECT_EQ(
	    (unsigned int) (i-1),
	    (unsigned int) cl.size()) << "Erreur taille liste";
  EXPECT_EQ(
	    (i-1) * x * x,
	    cl.front()) << "Erreur élément tête";
}

// back() : assertion ! empty()
TEST_F(TestList, q11BackAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.back(), "Assertion.*! *empty().*failed");
}

// back() const : assertion ! empty()
TEST_F(TestList, q11BackAssertConst)
{
  const Liste<double> liste;
  ASSERT_DEATH(liste.back(), "Assertion.*! *empty().*failed");
}

// push_back, empty, size, back
TEST_F(TestList, q11Back)
{
  Liste<double> liste;
  unsigned int i;
  double x = 1.1;
  for (i = 1; i <= 5; ++i) {
    liste.push_back(i * x + 1);
    ASSERT_TRUE(! liste.empty()) << "Liste ne devrait pas être vide";
    EXPECT_EQ(
	      (unsigned int) i,
	      (unsigned int) liste.size()) << "Erreur taille liste";
    EXPECT_EQ(
	      i * x + 1,
	      liste.back()) << "Erreur élément queue";
  }

  // test const : empty, size, back
  const Liste<double> & cl(liste);
  ASSERT_TRUE(! cl.empty()) << "Liste ne devrait pas être vide";
  EXPECT_EQ(
	    (unsigned int) (i-1),
	    (unsigned int) cl.size()) << "Erreur taille liste";
  EXPECT_EQ(
	    (i-1) * x + 1,
	    cl.back()) << "Erreur élément queue";
}

// push_front/back, empty, size, front/back
TEST_F(TestList, q11FrontAndBack)
{
  Liste<double> liste;
  unsigned int i;
  double x = 1.1;
  for (i = 1; i <= 5; ++i) {
    liste.push_front(i * x * x);
    liste.push_back(i * x + 1);
    ASSERT_TRUE(! liste.empty()) << "Liste ne devrait pas être vide";
    EXPECT_EQ(
	      (unsigned int) (i * 2),
	      (unsigned int) liste.size()) << "Erreur taille liste";
    EXPECT_EQ(
	      i * x * x,
	      liste.front()) << "Erreur élément tête";
    EXPECT_EQ(
	      i * x + 1,
	      liste.back()) << "Erreur élément queue";
  }

  // test const : empty, size, front/back
  const Liste<double> & cl(liste);
  ASSERT_TRUE(! cl.empty()) << "Liste ne devrait pas être vide";
  EXPECT_EQ(
	    (unsigned int) (i-1)*2,
	    (unsigned int) cl.size()) << "Erreur taille liste";
  EXPECT_EQ(
	    (i-1) * x * x,
	    cl.front()) << "Erreur élément tête";
  EXPECT_EQ(
	    (i-1) * x + 1,
	    cl.back()) << "Erreur élément queue";
}

// pop_front() : assertion ! empty()
TEST_F(TestList, q11PopFrontAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.pop_front(), "Assertion.*! *empty().*failed");
}

// push_front, empty, size, front, pop_front
TEST_F(TestList, q11PopFront)
{
  Liste<double>	liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, front);
  list_equals_deque(liste, array, front);
}

// pop_back() : assertion ! empty()
TEST_F(TestList, q11PopBackAssert)
{
  Liste<double> liste;
  ASSERT_DEATH(liste.pop_back(), "Assertion.*! *empty().*failed");
}

// push_back, empty, size, back, pop_back
TEST_F(TestList, q11PopBack)
{
  Liste<double>	liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, back);
  list_equals_deque(liste, array, back);
}

TEST_F(TestList, q11Tout)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  list_equals_deque(liste, array, alea);
}

