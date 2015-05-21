/**
   Squelette a completer de la classe implementant votre allocateur.
   Si necessaire, vous pouvez creer d'autres classes qui seront
   utilises dans Allocateur. Mais la classe principale Racine ne
   s'adressera qu'a la classe Allocateur.

   Dans chaque methode, verifiez bien que les parametres sont
   valides. Par exemple, pour creer un processus 'p', il faut que 'p'
   ne soit pas deja un numero de processus valide. Dans le cas
   contraire, on levera une exception de type IllegalArgumentException
   avec un message pertinent.

   Completer egalement les commentaires associes a chaque methode si
   necessaire.
 */

import java.util.*;

public class Allocateur {

	// attributs

	private Graphe _alloc;
	private int max_proc; // nombre maximum de processus
	private int nb_proc; // nombre effectif de processus
	private int nb_ress;

	// constructeurs

	/**
       Creation d'un allocateur pouvant gerer jusqu'a 'nmaxProc' processus (numerotes de 0 a (nmaxProc-1))
       et exactement 'nRess' ressources (numerotees de 0 a (nRess-1).
	 */
	public Allocateur(int nmaxProc, int nRess) {
		max_proc = nmaxProc;
		nb_proc = 0;
		nb_ress = nRess;
		_alloc = new GrapheDicoSucc(nmaxProc+nRess);

		//À la création du graphe, nous créons un sommet par ressource.
		for(int i = 0; i < nRess; ++i)
		{
			try {
				_alloc.ajoutSom(i);
			} catch (Exception e) {
				System.out.println("Erreur lors de la création de la ressource");
			}
		}
	}

	// methodes

	/**
       Retourne vrai si et seulement si 'p' est un processus connu de l'allocateur
	 * @throws Exception 
	 */
	public boolean validProc(int p) throws Exception {
		return _alloc.validSom(p);
	}

	/**
       Retourne vrai si et seulement si 'r' est une ressource connue de l'allocateur
	 * @throws Exception 
	 */
	public boolean validRess(int r) throws Exception {
		return _alloc.validSom(r);
	}

	/**
       O1: Creation du nouveau processus 'p'.
	 */
	public void creerProc(int p) {
		try {
			//Si le processus a déjà été créé
			if(validProc(nb_ress + p))
			{
				System.out.println("Le processus a déjà été créé");
				return;
			}
		} catch (Exception e1) {
			System.out.println("Erreur lors de la vérification de présence du processus");
		}
		try {
			_alloc.ajoutSom(nb_ress + p);
			nb_proc++;
			System.out.println("Creation du processus " + p);
		} catch (Exception e) {
			System.out.println("Erreur lors de la création du processus");
		}
	}

	/**
       O2: Destruction du processus 'p'.
	 */
	public void detruireProc(int p) {
		// a completer
		System.out.println("Destruction du processus " + p);
	}

	/**
       O3: Demande d'un ensemble de ressources 'lr' par le processus 'p'.
	 */
	public void demanderRess(int p, Set lr) {
		// a completer
		System.out.println("Demande de " + lr.size() + " ressource(s) par le processus " + p);
	}

	/**
       O4: Liberation d'une ressource 'r' par le processus 'p'.
	 */
	public void libererRess(int p, int r) {
		// a completer
		System.out.println("Liberation de la ressource " + r + " par le processus " + p);
	}

	/**
       O5: Affichage des files d'attentes des ressources.
	 */
	public void afficherFiles() {
		// a completer
		System.out.println("Affichage des files d'attentes");
	}

	/**
       O6: Affichage des processus actifs.
	 */
	public void afficherActifs() {
		System.out.println("Affichage des processus actifs :");
		Iterator<Integer> iterator = _alloc.ensPtsEntree().iterator();
	    while (iterator.hasNext()) {
	      Integer element = iterator.next();
	      if(element >= nb_ress)
	      System.out.println(new Integer(element.intValue()-nb_ress) + " est un processus actif");
	    }
	}

	/**
       O7: Affichage des attentes entre processus.
	 */
	public void afficherAttentes() {
		// a completer
		System.out.println("Affichage des attentes entre processus");
	}

	/**
       O8: Affichage des interblocages.
	 */
	public void afficherInterblocages() {
		// a completer
		System.out.println("Affichage des interblocages");
	}

} // class

