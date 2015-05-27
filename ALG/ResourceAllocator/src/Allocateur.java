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

	private Graphe _alloc; //l'allocateur
	private int max_proc; // nombre maximum de processus
	private int nb_proc; // nombre effectif de processus
	private int nb_ress; //nombre effectif de ressources
	private int NIL = -1;

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
		try {
			if(!validProc(nb_ress + p))
			{
				System.out.println("Le processus à détruire n'existe pas !");
				return;
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			nb_proc--;
			//Suppression des arcs entre le proccessus p et l'ensemble de ses successeurs
			//			Set<Integer> successeurs = _alloc.ensSucc(p);
			//			for(Integer e : successeurs)
			//			{
			//				_alloc.oterArc(p, e);
			//			}
			_alloc.oterSom(p+nb_ress);
			System.out.println("Destruction du processus " + p);
		} catch (Exception e) {
			System.out.println("Erreur lors de la destruction du processus " + p);
		}
	}

	/**
       O3: Demande d'un ensemble de ressources 'lr' par le processus 'p'.
	 */
	public void demanderRess(int p, Set lr) {
		System.out.println("Demande de " + lr.size() + " ressource(s) par le processus " + p);
		//On vérifie que p est bien un processus, sinon on le créé
		try {
			if(!validProc(p+nb_ress))
				creerProc(p);
		} catch (Exception e) {
			System.out.println("Erreur lors de la vérification de la validité du processus !");
		}

		Set<Integer> lesRessources = lr;
		for(Integer rsc : lesRessources)
		{
			if(!_alloc.ensPtsEntree().contains(p+nb_ress))
			{
				System.out.println("Un processus bloqué ne peut pas demander de nouvelles ressources");
				return;
			}
			//On vérifie si la ressource est valide
			if(rsc > nb_ress)
			{
				System.out.println("Quit : Ressource invalide ! (" + rsc + ")");
				return;
			}

			//On se met dans la liste d'attente.
			try {
				//On prends la liste des prédecesseurs de la ressource
				Iterator<Integer> iterator = _alloc.ensPred(rsc).iterator();

				while (iterator.hasNext()) {
					//Pour chaque prédecesseur
					Integer element = iterator.next();
					try {
						Iterator<Integer> iteratorSucc = _alloc.ensSucc(element).iterator();
						boolean fullRes = true;
						//On vérifie s'il est en bout de file d'attente
						while(iteratorSucc.hasNext())
						{
							Integer temp = iteratorSucc.next();
							if(temp >= nb_ress && _alloc.ensSucc(temp).contains(rsc))
							{
								fullRes = false;
								break;
							}
						}
						//Si le processus trouvé est le dernier de la file d'attente
						if(fullRes)
						{
							// si il n'y a pas de successeurs on trace l'arc
							_alloc.ajoutArc(element, p+nb_ress);  
							System.out.println("Arc créé : " + new Integer(element - nb_ress) + " - " + p);
							if(isCyclic())
							{
								System.out.println("\nINTERBLOCAGE :");
								detruireProc(p);
								return;
							}
							break;
						}
					} catch (Exception e) {
						System.out.println("Erreur lors de la mise en fin de file d'attente du processus");
					}
				}
			} catch (Exception e1) {

			}

			//Si la ressource est valide, on trace un arc du sommet à la ressource
			try {
				_alloc.ajoutArc(p+nb_ress, rsc);
				System.out.println("Arc créé : " + p + " - R" + rsc);
			} catch (Exception e) {
				System.out.println("Erreur lors de l'ajout de l'arc");
			}
		}
	}

	/**
       O4: Liberation d'une ressource 'r' par le processus 'p'.
	 */
	public void libererRess(int p, int r) {
		Set<Integer> ensProcActifs = _alloc.ensPtsEntree();
		//On teste si le processus et la ressource existent et si la proccessus est un processus actif
		try {
			if((!validProc(nb_ress+p) || !validProc(r)) && !ensProcActifs.contains(p))
			{
				System.out.println("La libération est impossible !");
				return;
			}
		} catch (Exception e) {
			System.out.println("Erreur lors de la vérification de la présence du processus et de la ressource");
		} 
		//Si la libération est possible, on ôte les arcs
		try {
			_alloc.oterArc(p+nb_ress, r);
			Set<Integer> ensProcPred = _alloc.ensPred(r);
			for(int e : ensProcPred)
			{
				if(_alloc.validArc(p+nb_ress, e))
					_alloc.oterArc(p+nb_ress, e);
			}
		} catch (Exception e1) {
			System.out.println("Erreur lors de la libération de la ressource " + r + "par le proccessus " + p);
		}
		System.out.println("Liberation de la ressource " + r + " par le processus " + p);
	}

	/**
       O5: Affichage des files d'attentes des ressources.
	 */
	public void afficherFiles() {
		for(int i = 0; i < nb_ress; ++i)
		{
			System.out.println("File des processus sur la ressource "+i);
			try {
				for(Integer p : (Set<Integer>)_alloc.ensPred(i))
					System.out.print(new Integer(p-nb_ress)+";");
				System.out.print("\n");
			} catch (Exception e) {
				System.out.println("Erreur lors de l'affichage");
			}
		}
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
		System.out.println("Affichage des attentes entre processus");
		for(int i = nb_ress; i <= nb_ress+nb_proc; ++i)
		{
			try {
				if(validProc(i))
				{
					System.out.println("Le processus "+new Integer(i-nb_ress)+" attend :");
					for(Integer p : (Set<Integer>)_alloc.ensPred(i))
						System.out.print(new Integer(p-nb_ress)+";");
					System.out.print("\n");
				}
			} catch (Exception e) {
				System.out.println("Erreur lors de l'affichage");
			}
		}
	}

	/**
       O8: Affichage des interblocages.
	 */
	public void afficherInterblocages() {
		// a completer
		System.out.println("Affichage des interblocages");
		System.out.println("\nEst bloqué : "+isCyclic());
	}

	private boolean isCyclic()
	{
		Integer[] cfc = CFC();
		for(Integer i : cfc)
			System.out.print(i.toString() + ";");
		for(int i = 1; i <= nb_ress+nb_proc; ++i)
		{
			boolean p = false;
			for(int j = 0; j < cfc.length; ++j)
			{
				if(cfc[j] == i && p)
					return true;
				if(cfc[j] == i && !p)
					p = true;
			}
		}
		return false;
	}

	public Integer[] CFC()
	{
		Integer date = 0;
		Integer[] DEBUT = new Integer[nb_ress+max_proc];
		Deque<Integer> stack = new ArrayDeque<Integer>();
		Integer NCFC = 0;
		Integer[] _cfc = new Integer[nb_ress+max_proc];
		for(int i = 0; i < nb_ress+max_proc; ++i)
		{
			DEBUT[i] = 0;
			_cfc[i] = 0;
		}
		for(Integer i = 0; i < nb_ress + max_proc; ++i)
			if(DEBUT[i] == 0)
			{
				Integer[] temp = tarjan(i, date, DEBUT, stack, NCFC, _cfc);
				date = temp[2];
				NCFC = temp[1];
			}
		return _cfc;
	}

	public Integer[] tarjan(Integer i, Integer date, Integer[] DEBUT, Deque<Integer> stack, Integer NCFC, Integer[] _cfc)
	{
		Integer[] ret = new Integer[3];
		date+=1;
		DEBUT[i]=date;
		Integer min = date;
		try {
			if(i >= nb_ress && validProc(i))
				stack.push(i);
		} catch (Exception e1) {
			// TODO Bloc catch généré automatiquement
			e1.printStackTrace();
		}
		_cfc[i] = date;
		try {
			if(i >= nb_ress && validProc(i))
			{
				for(Integer adj : (Set<Integer>)_alloc.ensPred(i))
				{
					if(adj >= nb_ress && validProc(adj))
					{
						if(DEBUT[adj]==0)
						{
							Integer[] temp = tarjan(adj, date, DEBUT, stack, NCFC, _cfc);
							NCFC = temp[1];
							date = temp[2];
							min = Math.min(temp[0], min);
							System.out.println("Sommet:"+i+"min:"+min);
						}
						else if(_cfc[adj] == 0)
							min = Math.min(DEBUT[adj], min);
					}
				}
				if(min == DEBUT[i])
				{
					NCFC+=1;
					int k;
					if(!stack.isEmpty())
					do
					{
						k = stack.pop();
						_cfc[k] = NCFC;
					}while(stack.peek() != i && !stack.isEmpty());
				}
			}
			else
				_cfc[i] = 0;
		} catch (Exception e) {
			// TODO Bloc catch généré automatiquement
			e.printStackTrace();
		}
		ret[0] = min;
		ret[1] = NCFC;
		ret[2] = date;
		return ret;
	}
} // class

