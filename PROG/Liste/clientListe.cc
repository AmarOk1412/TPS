#include <iostream>
#include <string>
#include <algorithm>
#include "liste.hh"

/**------------------------------------------------------------------------
 * Test de la partie 1 (listes de réels et de chaînes)
 *------------------------------------------------------------------------*/

/** 1.2 initialiser une liste (T=double)			*/
static void initialiser(Liste<double> & l) {
  for (int i = 1; i <= 5; ++i) {
    double x = 1.1;
    l.push_front(i * x);
    l.push_back(i * x);
  }
}

/** 1.2 initialiser une liste (T=string)			*/
static void initialiser(Liste<std::string> & l) {
  for (int i = 1; i <= 5; ++i) {
    std::string ch(i, i + 'A');
    l.push_front(ch);
    l.push_back(ch);
  }
}

/** 1.2 afficherVider : affichage destructif...
 * @warning T doit posséder l'opérateur <<
 */
template <class T> 
static void afficherVider(Liste<T> & l) {
  // afficher chaque élément de la liste l,
  // le copier dans la liste copie
  // puis le supprimer de la liste l
  Liste<T> copie;
  std::cout << "<";
  while (!l.empty()) {
    T courant = l.back();
    std::cout << courant << ":";
    copie.push_back(courant);
    l.pop_back();
  }
  std::cout << ">\n";
  // la liste l est vide
  // la liste copie contient les éléments de l
} // destruction de la liste copie

static void testPartie1() {
  std::cout << "Test Partie 1\n=============\n";
  // 1.2 placer des éléments dans une liste et afficher la liste
  Liste<double> uneliste;
  initialiser(uneliste);
  std::cout << "\nListe de réels   : ";
  afficherVider(uneliste);

  // idem avec une liste de chaînes
  Liste <std::string> listeChaines;
  initialiser(listeChaines);
  std::cout << "Liste de chaînes : ";
  afficherVider(listeChaines);
} 
/**------------------------------------------------------------------------
 * Test de la partie 2 (liste de chaînes)
 *------------------------------------------------------------------------*/
/** 2.4 afficherIter : afficher une liste avec un itérateur
 * @warning T doit posséder l'opérateur <<
 */

template <class T>
static void afficherIter(const Liste<T> & l) {
  std::cout << "<";
  typename Liste<T>::const_iterator it  = l.begin();
  typename Liste<T>::const_iterator fin = l.end();
  while (it != fin) {
    std::cout << *it << " ";
    ++it;
  }
  std::cout << ">\n";
}


template <class T>
static Liste<T> * testPartie2() {
  std::cout << "\nTest Partie 2 (const_itérateur)\n===============================\n";

  // 1.2 placer des éléments dans une liste
  Liste<T> * uneliste = new Liste<T>();
  initialiser(*uneliste);

  // 2.4 afficher la liste avec un itérateur
  std::cout << "\nListe            : ";
  afficherIter(*uneliste);

  // 2.4 test de l'opérateur Liste<T>::const_iterator::operator ->
  // @warning T doit posséder la méthode size()
  const Liste<T> * l = uneliste;
  std::cout << "Test Opérateur ->: <";
  typename Liste<T>::const_iterator it  = l->begin();
  typename Liste<T>::const_iterator fin = l->end();
  while (it != fin) {
    std::cout << it->size() << " : ";
    ++it;
  }
  std::cout << ">\n";
  return uneliste;
}


/**------------------------------------------------------------------------
 * Test de la partie 2.5 : iterator et modification de liste de réels
 *------------------------------------------------------------------------*/

static void testPartie2bis(void) {
  std::cout << "\nTest Partie 2.5  (itérateur)\n============================\n";

  // 1.2 placer des éléments dans une liste
  Liste<double> * uneliste = new Liste<double>();
  initialiser(*uneliste);

  // 2.4 afficher la liste avec un itérateur
  std::cout << "\nListe            : ";
  afficherIter(*uneliste);

  std::cout << "Liste modifiée   : ";
  Liste<double>::iterator it  = uneliste->begin();
  Liste<double>::iterator fin = uneliste->end();
  while (*it != *fin) {
//  while (it != fin) {
    *it *= *it;
    ++it;
  }
  afficherIter(*uneliste);
  delete uneliste;
}

/**------------------------------------------------------------------------
 * Test de la partie 3 (liste de réels)
 *------------------------------------------------------------------------*/

/// 3. opérations sur une liste de réels
static Liste<double> * bricoler(Liste<double> * maliste) {
  std::cout << "\nVous allez devoir saisir une suite de nombres, terminée par une valeur finale.\n";
  std::cout << "Saisissez d'abord la valeur finale : ";
  double valeurFin; // valeur de fin de saisie
  std::cin >> valeurFin;
  std::cout << "\nSaisissez chaque nombre (x) de la suite : \n";
  std::cout << "  - si x > 0, x sera cherché dans la liste :\n";
  std::cout << "     - si x est présent, x sera ajouté en tête de liste\n";
  std::cout << "     - si x est absent,  x sera ajouté en fin  de liste\n";
  std::cout << "  - si x < 0, -x sera cherché dans la liste :\n";
  std::cout << "     - si -x est présent, il sera supprimé de la liste\n";
  std::cout << "     - si -x est absent,  x  sera ajouté en tête de liste\n";
  std::cout << "La saisie du nombre 0 vide la liste de son contenu\n";

  while (true) {
    double nb; // nombre courant
    std::cin >> nb;

    if (nb == valeurFin)  break;

    if (nb == 0) {
      std::cout << nb << " on détruit tout ";
      delete maliste;
      maliste = new Liste<double>();
    }
    else if (nb > 0) {
      // 3. chercher nb dans la liste
      Liste<double>::iterator pos = find(maliste->begin(), maliste->end(), nb);
      if (pos != maliste->end()) {
        std::cout << nb << " est présent\t";
        maliste -> insert(maliste->begin(), nb);	// 3. ajout en tête
      }
      else {
        std::cout << nb << " est absent\t";
        maliste -> insert(pos, nb);			// 3. ajout en fin
      }
    }
    else { // nb < 0
      // 3. chercher -nb dans la liste
      Liste<double>::iterator pos = find(maliste->begin(), maliste->end(), -nb);
      if (pos != maliste->end()) {
        std::cout << -nb << " est présent\t";
        maliste -> erase(pos);			       // 3. retirer l'élément
      } else {
        std::cout << nb << " est absent\t";
        maliste -> insert(maliste->begin(), nb);	// 3. ajout en tête
      }
    }
    afficherIter(*maliste);
  }
  return maliste;
}

/** 3.1 chercher une valeur dans une liste triée
 * @param l : liste où se fait la recherche
 * @param x : valeur à chercher
 * @return position du premier élément de valeur >= x <br>
 * ou end() si un tel élément n'existe pas
 * @warning T doit posséder l'opérateur <
 */

template <class T>
static typename Liste<T>::iterator chercherTri(Liste<T> & l,const T & x) {
	typename Liste<T>::iterator it(l.begin());
	while(*it<x && it != l.end())
		it++;
	return it;
}

/** 3.1 créer une copie triée par valeurs croissantes d'une liste
 * @param l : liste à copier
 * @warning T doit posséder l'opérateur <
 * @return liste triée
 */

template <class T>
static Liste<T> * copierTri(const Liste<T> & l) {
	Liste<T> *res = new Liste<T>();
	typename Liste<T>::const_iterator it = l.begin();
	typename Liste<T>::const_iterator it2 = l.end();
	while(it!=it2){
		typename Liste<T>::iterator itRes = chercherTri(*res,*it);
		res->insert(itRes,*it);
		++it;
	}	
	return res;
}


static Liste<double> * testPartie3() {
  std::cout << "\nTest Partie 3 (find, insert, erase)\n===================================\n";
  // placer des éléments dans une liste
  Liste<double> * uneliste = bricoler(new Liste<double>());

  // 2.4 afficher la liste
  std::cout << "\nListe initiale\n";
  afficherIter(*uneliste);

  // 3.1 copier les élts dans une liste triée en ordre croissant
  Liste<double> * listeTriee = copierTri(*uneliste);
  // afficher la liste triée
  std::cout << "\nListe triée\n";
  afficherIter(*listeTriee);

  // lui ajouter quelques éléments
  listeTriee->push_back(-314.159);
  listeTriee->push_front(1984);
  listeTriee->push_front(1515);
  std::cout << "\najout de quelques éléments\n";
  afficherIter(*listeTriee);
  
  chercherTri(*listeTriee, 1984.);
  chercherTri(*listeTriee, 1412.);
 

  delete uneliste;
  return listeTriee;
}

/**------------------------------------------------------------------------
 * Test de la partie 4 (générique)
 *------------------------------------------------------------------------*/

template <class T> static void testPartie4(Liste<T> * listeInitiale) {
  std::cout << "\nTest Partie 4 (cdc, opérateurs =, + et <<)\n==========================================\n";

  // 4.4 opérateur d'affichage
  std::cout << "\nListe initiale\t\t: " << * listeInitiale;

  // 3.1 copier les élts dans une liste triée en ordre croissant
  const Liste<T> * listeTriee = copierTri(*listeInitiale);
  // afficher la liste triée
  std::cout << "Liste triée\t\t: " << * listeTriee;

  // 4.1 en faire une copie (constructeur de copie)
  std::cout << "Copie de la précédente\t: ";
  Liste<T> * copie = new Liste<T>(*listeTriee);
  std::cout << *copie;

  // modifier la liste initiale et la liste copiée
  T val;
  std::cout << "\nSaisir deux valeurs\t: ";
  std::cin >> val;
  listeInitiale->push_front(val);
  listeInitiale->push_back(val);
  std::cin >> val;
  copie->push_front(val);
  copie->push_back(val);
  std::cout << "\nListe initiale modifiée\t: " << * listeInitiale;
  std::cout << "Liste triée\t\t: " << * listeTriee;
  std::cout << "Copie triée modifiée\t: " << * copie;

  // 4.3 et concaténer
  std::cout << "\nConcaténation (listeTriee + listeInitiale + copie)\n";
  std::cout << *listeTriee << " + " << *listeInitiale << " + " << *copie << " = ";
  *listeTriee + *listeInitiale;
  Liste<T> lconc = *listeTriee + *listeInitiale + *copie;
  std::cout << lconc;

  // 4.2 opérateur d'affectation
  std::cout << "\nremplacer la première liste par la liste concaténée\n";
  *listeInitiale = lconc;
  std::cout << *listeInitiale;

  // et tout détruire
  delete listeTriee;
  delete copie;
} // testPartie4

//------------------------------------------------------------------------
// Le programme de test des classes Liste et iterator
//------------------------------------------------------------------------
int main() {
  // test partie 1 liste de réels
  testPartie1();

  // test partie 2 : const_iterator et liste de chaînes
  Liste<std::string> * listeChaines = testPartie2<std::string>();

  // test partie 2.5 : iterator et modification de liste de réels
  testPartie2bis();

  // test partie 3 (liste de réels)
  Liste<double> * listeReels = testPartie3();
   
   

  // test partie 4 (liste de réels)
  testPartie4(listeReels);

  // test partie 4 (liste de chaînes)
  testPartie4(listeChaines);

  delete listeReels;
  delete listeChaines;
  return 0;
}
