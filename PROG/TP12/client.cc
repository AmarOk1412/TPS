#include <iostream>
#include <cstdlib>					// srand, rand
#include "ferry.h"
#include "auto.h"
#include "bus.h"
// #include "ambulance.h"

int main(void) 
{
  // initialiser "le hasard"
  srand( time(NULL) );

  // créer un ferry dont la capacité est comprise :
  // - entre  50 et 100 unités de longueur
  // - entre 150 et 250 personnes
  Ferry		jules(50 + rand() % 50, 150 + rand() % 100);
  std::cout << "\nContenu initial du ferry\n" << jules;

  while (true) {
    Vehicule * pv;			// désigne un véhicule à ajouter

    // Tirer au hasard le type de véhicule
    switch (rand() % 3) {
    case 0 :			// Auto : nombre de personnes, tout terrain ?
      pv = new Auto(rand() % 5, (rand() % 3) == 0 ? true : false);
      break;

    case 1 :			// Bus : longueur, nombre de personnes
      pv = new Bus(10 + rand() % 10, 20 + rand() % 60);
      break;

//     case 2 :			// Ambulance : nombre de personnes, tout terrain ?
//       pv = new Ambulance(rand() % 5, (rand() % 3) == 0 ? true : false);
//       break;

    default:			// Auto : nombre de personnes, tout terrain ?
      pv = new Auto(rand() % 5, (rand() % 3) == 0 ? false : true);
      break;
    }

    // Essayer d'ajouter ce nouveau véhicule dans le ferry
    std::cout << "Ajout de : " << *pv << std::endl;
    bool plein = ! jules.ajouter(pv);

    if (plein) {
      // Ajout impossible : fin de remplissage
      std::cout << std::flush;
      std::cerr << "\n*** Dépassement de capacité ***\n";
      break;
    }
    else {
      // Ajout effectué
      std::cout << "\nContenu du ferry\n" << jules;
    }
  }

  // trier par longueur croissante
//   jules.trier();
//   std::cout << "\nFerry trié par longueur croissante\n" << jules;

  // trier par longueur décroissante
//   jules.trier(false);
//   std::cout << "\nFerry trié par longueur décroissante\n" << jules;

  std::cout << "Fin du programme\n";
  return 0;
}
