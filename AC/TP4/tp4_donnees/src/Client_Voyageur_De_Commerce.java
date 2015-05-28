import java.io.*;

public class Client_Voyageur_De_Commerce {


	/**
	 * lit une liste de poids dans un fichier
	 * @param nomFichier  nom du fichier texte contenant les coordonnées des villes
	 * @param nbr_villes nombre de villes
	 * @param coord_x et coord_y : les 2 tableaux que la fonction remplit et qui vont contenir les coordonnées des villes
	 */
	public static void charge_coords(String nomFichier, int nbr_villes, double[] coord_x, double[] coord_y){
		assert(coord_x.length==coord_y.length) : "charge_coords : coord_x et coord_y n'ont pas la même taille ?";
		InputStream IS = Lecture.ouvrir(nomFichier);
		if (IS==null){
			System.err.println("pb d'ouverture du fichier "+nomFichier);
		}
		int i=0;
		while(!Lecture.finFichier(IS) && i<coord_x.length){
			coord_x[i] = Lecture.lireDouble(IS);
			coord_y[i] = Lecture.lireDouble(IS);
			i++;
		}
		Lecture.fermer(IS);
	}

	public static void main(String[] args) throws InterruptedException{

		/* on initialise les coordonnées des villes en les lisant ds un fichier 
		 */

		/* paramètres */ 
		int nbr_indiv=100;
		double prob_mut=0.1;
		int nbr_villes = 16;
		double[] coord_x = new double[nbr_villes];
		double[] coord_y = new double[nbr_villes];
		charge_coords("../data_vdc/"+nbr_villes+"coords.txt",nbr_villes, coord_x, coord_y);

		/* Exemple d'utilisation de Display_VDCC (il faut d'abord faire le constructeur pour ce test fonctionne, ainsi que compléter les accesseurs)
		 */
		Individu_VDC ind1 = new Individu_VDC(coord_x, coord_y); //on crée un individu aléatoire
		Display_VDC disp = new Display_VDC(ind1); //on l'affiche
		Thread.sleep(1000); //pause de 1 seconde (pour avoir le temps de voir le premier affichage)
		Individu_VDC ind2 = new Individu_VDC(coord_x, coord_y); //on en crée un autre
		disp.refresh(ind2); //on met à jour l'affichage avec le nouveau

		Individu_VDC[] pop = new Individu_VDC[nbr_indiv];
		for(int i = 0; i < nbr_indiv; ++i)
			pop[i] = new Individu_VDC(coord_x, coord_y);
		Population _p = new Population(pop);

		
		/* on génére les générations successives
		 * en faisant se reproduire la population
		 * et on affiche l'adaptation moyenne et maximale de chaque génération
		 * on s'arrête si on a atteint la capacité ou si on fait un nombre donné (paramètre) d'itérations
		 * le résultat est alors donné par l'individu maximal de la dernière génération
		 */
		int it = 0;
		double best = -1;
		while(it < 100)
		{
			System.out.println("Génération " + it);
			System.out.println("Adaptation moyenne : " + _p.adaptation_moyenne());
			System.out.println("Adaptation maximale : " + _p.adaptation_maximale());
			_p.reproduction(prob_mut);
			best = _p.individu_maximal().adaptation();
			++it;
		}
		
		int[] val= ((Individu_VDC)_p.individu_maximal()).get_parcours();
			System.out.println("Résultat : ");
		for(int b : val)
			System.out.print(b);
		System.out.println("\nAvec un score de :"+_p.individu_maximal().adaptation());
	}
}
