import java.io.InputStream;


public class Client_Sac_A_Dos {


	/**
	 * lit une liste de poids dans un fichier
	 * @param nomFichier  nom du fichier texte contenant les poids
	 * @param nbr_objets nombre d'objets possibles
	 * @return tableau de poids
	 */
	public static double[] charge_poids(String nomFichier, int nbr_objets){
		double[] poids = new double[nbr_objets];
    	InputStream IS = Lecture.ouvrir(nomFichier);
    	if (IS==null){
    		System.err.println("Impossible d'ouvrir le fichier \""+nomFichier+"\" (n'existe pas ? pas au bon endroit ?)");
    	}
    	int i=0;
    	int somme=0;
    	while(!Lecture.finFichier(IS) && i<nbr_objets){
    		poids[i] = Lecture.lireDouble(IS);
    		somme += poids[i];
    		i++;
    	}
    	System.out.println("charge_poids ("+nomFichier+") : poids total des objets = "+somme);
    	Lecture.fermer(IS);
    	return poids;
	}

	
	public static void main(String[] args){
		
		/* paramètres */ 
		int nbr_indiv=100;
		double prob_mut=0.1;
		
		/* On initialise les poids en lisant un fichier 
		 */
		
		int nbr_objets=28;
		int capacite=1581;
		
//		int nbr_objets=70;
//		int capacite=350;		
		
		double[] poids = charge_poids("../data_sad/nbrobj"+nbr_objets+"_capacite"+capacite+".txt",nbr_objets);
		
		
		/* on crée une population (aléatoire)
		 * de nbr_indiv individus de taille nbr_objets
		 */
		Individu_SAD[] pop = new Individu_SAD[nbr_indiv];
		for(int i = 0; i < nbr_indiv; ++i)
			pop[i] = new Individu_SAD(poids, capacite);
		Population _p = new Population(pop);

		
		/* on génére les générations successives
		 * en faisant se reproduire la population
		 * et on affiche l'adaptation moyenne et maximale de chaque génération
		 * on s'arrête si on a atteint la capacité ou si on fait un nombre donné (paramètre) d'itérations
		 * le résultat est alors donné par l'individu maximal de la dernière génération
		 */
		int it = 0;
		double best = -1;
		while(it < 10000 && best < capacite)
		{
			System.out.println("Génération " + it);
			System.out.println("Adaptation moyenne : " + _p.adaptation_moyenne());
			System.out.println("Adaptation maximale : " + _p.adaptation_maximale());
			_p.reproduction(prob_mut);
			best = _p.individu_maximal().adaptation();
			++it;
		}
		
		boolean[] val= ((Individu_SAD)_p.individu_maximal()).getIndividu();
			System.out.println("Résultat : ");
		for(boolean b : val)
			System.out.print(b?"1":"0");
		System.out.println("\nAvec un score de :"+_p.individu_maximal().adaptation());
	}
}

