/*
 * main.cpp
 *
 *  Created on: 8 mars 2013
 *      Author: engel
 */

#include "constantes.h"
#include "enregistreur_fichier.h"
#include "enregistreur_fichier_texte.h"
#include "harmonique.h"
#include "signal_constant.h"

void
q2_signal_constant() {
  signal_constant sc(0.5);
  enregistreur_fichier_texte enr("02_sc.txt", 1);
  enr.connecterEntree(sc.getSortie(0), 0);
  // générer 5 valeurs
  for (unsigned int i = 0; i < 5; ++i) {
    sc.calculer();
    enr.calculer();
  }
}

void q7_harmonique() {
  harmonique h(440);					// la 440Hz
  enregistreur_fichier enr("07_harmonique.raw", 1);	// fichier mono
  enr.connecterEntree(h.getSortie(0), 0);
  // produire 2 secondes de son
  for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
    h.calculer();
    enr.calculer();
  }
}

int
main() {
  q2_signal_constant();
  q7_harmonique();
  return 0;
}
