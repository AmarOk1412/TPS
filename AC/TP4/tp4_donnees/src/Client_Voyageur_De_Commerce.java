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
		double prob_mut=0.008;
		int nbr_villes = 64;
		double[] coord_x = new double[nbr_villes];
		double[] coord_y = new double[nbr_villes];
		charge_coords("../data_vdc/"+nbr_villes+"coords.txt",nbr_villes, coord_x, coord_y);
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
		Display_VDC disp = new Display_VDC((Individu_VDC)_p.individu_maximal());
		while(it < 1000)
		{
			System.out.println("Génération " + it);
			_p.reproduction(prob_mut);
			best = 1/((Individu_VDC)_p.individu_maximal()).adaptation();
			System.out.println("Score : " + best);
			if(it%50 == 0)
				disp.refresh((Individu_VDC)_p.individu_maximal());
			++it;
		}
		disp.refresh((Individu_VDC)_p.individu_maximal());
		int[] val= ((Individu_VDC)_p.individu_maximal()).get_parcours();
			System.out.println("Résultat : ");
		for(int b : val)
			System.out.print(b);
		System.out.println("\nAvec un score de :"+_p.individu_maximal().adaptation());
		
	}
}
