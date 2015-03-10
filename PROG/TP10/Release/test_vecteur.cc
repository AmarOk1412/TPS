#include <gtest/gtest.h>
#include "vecteur.h"

//------------------------------------------------------------------------
// fonctions utilitaires
//------------------------------------------------------------------------

// vérifier la dimension et les valeurs d'un vecteur (utilise get)
void check_dim_values_with_get(const Vecteur & v, unsigned int dim, float expected) {
  ASSERT_EQ(dim, v.dimensions());
  for (unsigned int i = 0; i < dim; ++i) {
    EXPECT_EQ(expected, v.get(i));
  }
}
// vérifier la dimension et les valeurs d'un vecteur (utilise get)
void check_dim_values_with_get(const Vecteur & v, unsigned int dim, float expected[]) {
  ASSERT_EQ(dim, v.dimensions());
  for (unsigned int i = 0; i < dim; ++i) {
    EXPECT_EQ(expected[i], v.get(i));
  }
}

// vérifier la dimension et les valeurs d'un vecteur (utilise operator [])
void check_dim_values_with_opr(const Vecteur & v, unsigned int dim, float expected) {
  ASSERT_EQ(dim, v.dimensions());
  for (unsigned int i = 0; i < dim; ++i) {
    EXPECT_EQ(expected, v[i]);
  }
}

// vérifier la dimension et les valeurs d'un vecteur (utilise operator [])
void check_dim_values_with_opr(const Vecteur & v, unsigned int dim, float expected[]) {
  ASSERT_EQ(dim, v.dimensions());
  for (unsigned int i = 0; i < dim; ++i) {
    EXPECT_EQ(expected[i], v[i]);
  }
}

// vérifier l'égalité de deux vecteurs
void check_vectors_equality(const Vecteur & v1, const Vecteur & v2) {
  ASSERT_EQ(v1.dimensions(), v2.dimensions());
  for (unsigned int i = 0; i < v1.dimensions(); ++i) {
    EXPECT_EQ(v1.get(i), v2.get(i));
  }
}

// initialiser un tableau à une valeur initiale + incrément
void init_array(float v[], unsigned int dim, float valinit, float inc = 0)
{
  float vc = valinit;
  for (unsigned int i = 0; i < dim; ++i) {
    v[i] = vc; vc += inc;
  }
}

// initialiser un vecteur et un tableau à une valeur initiale + incrément
void init_vector_and_array(Vecteur & v, float t[], unsigned int dim,
			   float valinit, float inc = 0)
{
  float vc = valinit;
  for (unsigned int i = 0; i < dim; ++i) {
    v.set(i, vc); t[i] = vc; vc += inc;
  }
}

//------------------------------------------------------------------------
// les tests
//------------------------------------------------------------------------

// test assertion constructeur
TEST(TestVecteur, DISABLED_assertConstructeur)
{
  ASSERT_DEATH(Vecteur v1(0, 5.), "Assertion.*failed");
}

// test assertion get
TEST(TestVecteur, DISABLED_assertGet)
{
  unsigned int dim1(15);
  float val1(10);
  Vecteur v1(dim1, val1);
  ASSERT_DEATH(v1.get(dim1), "Assertion.*failed");
}

// test constructeur à 2 paramètres
// vérifier dimension et valeurs
// méthodes utilisées : 
// - constructeur à 2 paramètres
// - dimensions
// - get
TEST(TestVecteur, DISABLED_q1Constructeur2Param)
{
  unsigned int dim1(15);
  float val1(10);
  Vecteur v1(dim1, val1);
  check_dim_values_with_get(v1, dim1, val1);
}

// vérifier dimension et valeurs
// méthodes utilisées : 
// - constructeur à 1 paramètre
// - dimensions
// - get
TEST(TestVecteur, DISABLED_q1Constructeur1Param)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  check_dim_values_with_get(v1, dim1, 0.);
}

TEST(TestVecteur, DISABLED_q1Constructeur0Param)
{
  unsigned int dim1(3);
  Vecteur v1;
  check_dim_values_with_get(v1, dim1, 0.);
}

TEST(TestVecteur, DISABLED_assertSet)
{
  unsigned int dim1(15);
  float val1(10);
  Vecteur v1(dim1, val1);
  ASSERT_DEATH(v1.set(dim1, -999.), "Assertion.*failed");
}

TEST(TestVecteur, DISABLED_q1Set)
{
  unsigned int dim1(15);
  float val1(10);
  Vecteur v1(dim1, val1);
  float expected[dim1];

  // modification du vecteur v1
  init_vector_and_array(v1, expected, dim1, val1, 1);
  // vérifier les valeurs
  check_dim_values_with_get(v1, dim1, expected);
}

TEST(TestVecteur, DISABLED_q2Lirevecteur)
{
  Vecteur * v1 = lireVecteur();
  int dimv2;
  std::cin >> dimv2;
  float expected[dimv2];
  for (int i = 0; i < dimv2; ++i) {
    std::cin >> expected[i];
  }
  check_dim_values_with_get(*v1, dimv2, expected);
  delete v1;
}

// test utilise le cdc
TEST(TestVecteur, DISABLED_q4Add)
{
  unsigned int dim1(15);
  Vecteur v1(dim1, 1);
  float   exp1[dim1];
  init_vector_and_array(v1, exp1, dim1, 1, 10);
  Vecteur v2(dim1);
  float   exp2[dim1];
  init_vector_and_array(v2, exp2, dim1, 100, 5);
  Vecteur v3(add(& v1, & v2));
  float   exp3[dim1];
  init_array(exp3, dim1, 101, 15);

  // vérifier si la somme est correcte et si les 2 vecteurs v1 et v2 sont inchangés
  check_dim_values_with_get(v1, dim1, exp1);
  check_dim_values_with_get(v2, dim1, exp2);
  check_dim_values_with_get(v3, dim1, exp3);
}

TEST(TestVecteur, DISABLED_q6ConstructeurDeCopie)
{
  unsigned int dim1(15);
  Vecteur v1(dim1, 1);
  float   expected1[dim1];
  init_vector_and_array(v1, expected1, dim1, 1, 10);
  {
    // faire une copie de m_v1
    Vecteur copie(v1);
    check_vectors_equality(v1, copie);
  }
  // vérifier si le vecteur v1 est toujours "en bon état"
  check_dim_values_with_get(v1, dim1, expected1);
}

TEST(TestVecteur, DISABLED_q6ConstructeurDeCopieModif)
{
  unsigned int dim1(15);
  float   valinit1(10);
  Vecteur v1(dim1, 1);
  float   expected1[dim1];
  init_vector_and_array(v1, expected1, dim1, 1, 10);

  {
    // faire une copie de v1
    Vecteur copie(v1);
    check_vectors_equality(v1, copie);
    // modifier la copie
    float new_expected[dim1];
    init_vector_and_array(copie, new_expected, dim1, valinit1, 7);
    // vérifier si la copie est correctement modifiée
    check_dim_values_with_get(copie, dim1, new_expected);
    // vérifier si l'original demeure inchangé
    check_dim_values_with_get(v1, dim1, expected1);
  }
  // vérifier si le vecteur v1 est toujours "en bon état"
  check_dim_values_with_get(v1, dim1, expected1);
}

// la taille du vecteur modifié diminue
TEST(TestVecteur, DISABLED_q7OperateurAffectationTailleDiminue)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   exp1[dim1];
  init_vector_and_array(v1, exp1, dim1, 1, 10);

  unsigned int dim2(7);
  Vecteur v2(dim2);
  float   exp2[dim2];
  init_vector_and_array(v2, exp2, dim2, 100, 5);

  v1 = v2;

  // vérifier v1 et v2
  check_dim_values_with_get(v1, dim2, exp2);
  check_dim_values_with_get(v2, dim2, exp2);

  // modifier v1
  float mod1[dim2];
  init_vector_and_array(v1, mod1, dim2, -10, -10);
  check_dim_values_with_get(v1, dim2, mod1);
  check_dim_values_with_get(v2, dim2, exp2);

  // modifier v2
  float mod2[dim2];
  init_vector_and_array(v2, mod2, dim2, 55, 11);
  check_dim_values_with_get(v1, dim2, mod1);
  check_dim_values_with_get(v2, dim2, mod2);
}

// la taille du vecteur modifié augmente
TEST(TestVecteur, DISABLED_q7OperateurAffectationTailleAugmente)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   exp1[dim1];
  init_vector_and_array(v1, exp1, dim1, 1, 10);

  unsigned int dim2(7);
  Vecteur v2(dim2);
  float   exp2[dim2];
  init_vector_and_array(v2, exp2, dim2, 100, 5);

  v2 = v1;

  // vérifier v1 et v2
  check_dim_values_with_get(v1, dim1, exp1);
  check_dim_values_with_get(v2, dim1, exp1);

  // modifier v1
  float mod1[dim1];
  init_vector_and_array(v1, mod1, dim1, -10, -10);
  check_dim_values_with_get(v1, dim1, mod1);
  check_dim_values_with_get(v2, dim1, exp1);

  // modifier v2
  float mod2[dim1];
  init_vector_and_array(v2, mod2, dim1, 55, 11);
  check_dim_values_with_get(v1, dim1, mod1);
  check_dim_values_with_get(v2, dim1, mod2);
}

TEST(TestVecteur, DISABLED_q8OperateurAdd2vecteurs)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   exp1[dim1];
  init_vector_and_array(v1, exp1, dim1, 1, 10);

  Vecteur v2(dim1);
  float   exp2[dim1];
  init_vector_and_array(v2, exp2, dim1, -5, -5);

  Vecteur v3(v1 + v2);
  float   exp3[dim1];
  init_array(exp3, dim1, -4, 5);

  // vérifier si la somme est correcte et si les 2 vecteurs v1 et v2 sont inchangés
  check_dim_values_with_get(v1, dim1, exp1);
  check_dim_values_with_get(v2, dim1, exp2);
  check_dim_values_with_get(v3, dim1, exp3);
}

TEST(TestVecteur, DISABLED_q8OperateurAdd3vecteurs)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   exp1[dim1];
  init_vector_and_array(v1, exp1, dim1, 1, 10);

  Vecteur v2(dim1);
  float   exp2[dim1];
  init_vector_and_array(v2, exp2, dim1, -5, -5);

  Vecteur v3(dim1);
  float   exp3[dim1];
  init_vector_and_array(v3, exp3, dim1, -20, 7);

  Vecteur v4(v1 + v2 + v3);
  float   exp4[dim1];
  init_array(exp4, dim1, -24, 12);

  // vérifier si la somme est correcte et si les vecteurs vi sont inchangés
  check_dim_values_with_get(v1, dim1, exp1);
  check_dim_values_with_get(v2, dim1, exp2);
  check_dim_values_with_get(v3, dim1, exp3);
  check_dim_values_with_get(v4, dim1, exp4);
}

TEST(TestVecteur, DISABLED_q9ProduitScalaire)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   exp1[dim1];
  init_vector_and_array(v1, exp1, dim1, 10, 10);

  Vecteur v2(dim1);
  float   exp2[dim1];
  init_vector_and_array(v2, exp2, dim1, -5, -5);

  float  ps = v1 * v2;
  float  exp3 = 0;
  for (unsigned int i = 0; i < dim1; ++i) {
    exp3 += v1.get(i) * v2.get(i);
  }
  ASSERT_EQ(exp3, ps);
}

TEST(TestVecteur, DISABLED_q10OperateurSaisie)
{
  int dimv;
  std::cin >> dimv;
  Vecteur v(dimv);
  std::cin >> v;
  float expected[dimv];
  for (int i = 0; i < dimv; ++i) {
    std::cin >> expected[i];
  }
  check_dim_values_with_get(v, dimv, expected);
}

TEST(TestVecteur, DISABLED_q11AssertOperateurIndexationConst)
{
  unsigned int dim1(15);
  float val1(10);
  Vecteur v1(dim1, val1);
  ASSERT_DEATH(v1[dim1], "Assertion.*failed");
}

TEST(TestVecteur, DISABLED_q11AssertOperateurIndexation)
{
  unsigned int dim1(15);
  float val1(10);
  Vecteur v1(dim1, val1);
  ASSERT_DEATH(v1[dim1] = 3., "Assertion.*failed");
}

TEST(TestVecteur, DISABLED_q11OperateurIndexationConsultation)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   expected1[dim1];
  init_vector_and_array(v1, expected1, dim1, -555.55, 2.2);
  check_dim_values_with_get(v1, dim1, expected1);
  check_dim_values_with_opr(v1, dim1, expected1);
}

TEST(TestVecteur, DISABLED_q11OperateurIndexationModification)
{
  unsigned int dim1(15);
  Vecteur v1(dim1);
  float   expected1[dim1];
  init_vector_and_array(v1, expected1, dim1, -555.55, 2.2);
  check_dim_values_with_get(v1, dim1, expected1);

  // modification du vecteur v1
  float new_expected[dim1];
  for (unsigned int i = 0; i < dim1; ++i) {
    v1[i]	    = expected1[i]   + i;
    new_expected[i] = expected1[i]   + i;
  }
  check_dim_values_with_opr(v1, dim1, new_expected);
  // remise à l'état initial de v1
  for (unsigned int i = 0; i < dim1; ++i) {
    v1[i] = expected1[i];
  }
  check_dim_values_with_opr(v1, dim1, expected1);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  return RUN_ALL_TESTS();
}
