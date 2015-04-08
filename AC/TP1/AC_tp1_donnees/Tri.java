import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Tri {

	/*Tri le tableau t via la méthode "Tri par insertion"
	 * cf TD1 exo 2
	 */
	public static void triInsertion(int[] t){
		//A FAIRE
	}
	
	/*Tri le tableau t via la méthode "Tri fusion"
	 * cf TD2 exo 5
	 */
	public static void triFusion(int[] t){
		if (t.length>0)
			triFusion(t, 0, t.length-1);
	}

	/* Sous-fonction (récursive) pour le tri fusion
	 * Trie le sous-tableau t[debut]..t[fin]
	 */
	private static void triFusion(int[] t, int debut, int fin){
		//A FAIRE
	}

	/* Sous-fonction pour le tri fusion
	 * Suppose que, dans le tableau t, 
	 *       les 2 sous-tableaux t[deb1]..t[fin1] et t[fin1+1]..[t[fin2] sont déjà triés
	 * Fusionne ces 2 sous-tableaux pour que le sous-tableau t[deb1]..t[fin2] soit trié
	 */
	private static void fusionner(int[] t, int deb1, int fin1, int fin2){
		int deb2 = fin1+1;
		//on recopie les éléments du début du tableau
		int[] t1 = new int[fin1-deb1+1];
		for(int i=deb1;i<=fin1;i++){
			t1[i-deb1]=t[i];
        }
		int compt1=deb1;
	    int compt2=deb2;
	    for(int i=deb1;i<=fin2;i++){        
	        if (compt1==deb2) //c'est que tous les éléments du premier tableau ont été utilisés
	            break; //tous les éléments ont donc été classés
	        else if (compt2==(fin2+1)){ //c'est que tous les éléments du second tableau ont été utilisés
	            t[i]=t1[compt1-deb1]; //on ajoute les éléments restants du premier tableau
	            compt1++;
	        }
	        else if (t1[compt1-deb1]<t[compt2]){
	            t[i]=t1[compt1-deb1]; //on ajoute un élément du premier tableau
	            compt1++;
	        }
	        else{
	            t[i]=t[compt2]; //on ajoute un élément du second tableau
	            compt2++;
	        }
        }
    }

	/* Affiche un tableau d'entiers
	 */
	public static void afficher(int [] t){
		System.out.print("[");
		for(int k=0;k<t.length;k++)
			System.out.print(" "+t[k]+" ");
		System.out.println("]");
	}
	
	/* Crée un fichier nomFichier.m contenant du code matlab initialisant un tableau T_nomFichier qui contient les éléments de tab
	*/
	public static void tab_to_matlab(String nomFichier, List<Integer> tab) {
		Iterator<Integer> i = tab.iterator();
		String s="T_"+nomFichier+"=[";
		while(i.hasNext())
				s += i.next()+" ";
		s += "];";
		PrintWriter fich;
		try {
			fich = new PrintWriter(new BufferedWriter (new FileWriter(nomFichier+".m")));
			fich.println(s);
		    fich.close();
		} catch (IOException e) {
			System.err.println("Problème: " + e.getMessage()) ;
		    System.exit(2) ;
		}
	}
	
	public static void main(String[] args) {
		//Vérification de l'implémentation des tris
		int [] t = new int[10];
		int [] t2 = new int[10];
		for(int k=0;k<t.length;k++){ //initialisation aléatoire
			t[k]=(int) (Math.random()*100);
			t2[k]=t[k];
		}
		System.out.print("Avant le tri : "); afficher(t);
		triInsertion(t);
		System.out.print("Après le tri par insertion: "); afficher(t);
		triFusion(t2);
		System.out.print("Après le tri fusion:        "); afficher(t2);
		
		//Analyse du temps d'exécution
		
		//A FAIRE : modifier les 3 valeurs suivantes
		int taille_init = 1;
		int taille_incr = 1;
		int taille_fin  = 1;
		
		List<Integer> tab_tailles = new ArrayList<Integer>();
		List<Integer> tab_temps = new ArrayList<Integer>();
		for(int n = taille_init; n<taille_fin; n=n+taille_incr){			  
			tab_tailles.add(n); //on sauvegarde la taille
			t = new int[n];
			//A FAIRE : initialisation de t

			long date1 = System.currentTimeMillis(); //on lance le chrono
			triInsertion(t); //on trie le tableau 
			long date2 = System.currentTimeMillis(); //on arrête le chrono
			tab_temps.add((int)(date2 - date1)); //on sauvegarde le temps
			System.out.println("Temps de calcul pour n="+n+" : "+ tab_temps.get(tab_temps.size()-1)+" millisecondes.");
		}
		
		//conversion des tableaux au format matlab
		tab_to_matlab("tailles", tab_tailles); 
		tab_to_matlab("temps", tab_temps);
	}

}
