/** \brief Ce fichier doit contenir la déclaration de la classe vecteur
    Attention, elle ne doit contenir aucune implémentation de méthode / fonction
*/

#ifndef _VECTEUR_H
#define _VECTEUR_H

#include <iostream>

// Déclaration de la classe vecteur
class Vecteur {
private :
	unsigned int m_dim;
	float *m_vecteur;

public :
  Vecteur(unsigned int nb_dim = 3, float val_init = .0);
  ~Vecteur();
  Vecteur(const Vecteur &o);
  const float& get(const int unsigned i) const;  
  float& get(int unsigned i);
  void set(int unsigned i,float v);
  unsigned int dimensions() const;
  Vecteur& operator=(const Vecteur &v1);
  Vecteur operator+(const Vecteur &v1);
  const float &operator[](const unsigned int i) const;
  float& operator[](unsigned int i);

private :
  // méthodes privées d'implémentation (si besoin)
};

// Prototypes des fonctions
void afficherVecteur(const Vecteur *v);
Vecteur * lireVecteur();
Vecteur add(const Vecteur *v1, const Vecteur * v2);
float operator*(const Vecteur &v1, const Vecteur &v2);

std::ostream & operator<<(std::ostream & out, const Vecteur &v1);
std::istream & operator>>(std::istream & in, Vecteur &v1);

#endif
