import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Tri {

	/*Tri le tableau t via la methode "Tri par insertion"
	 * cf TD1 exo 2
	 */
	public static void triInsertion(int[] t){
		for (int i = 1; i < t.length; i++) {
			int valueToSort = t[i];
			int j = 0;
			for(j = i; j > 0 && t[j - 1] > valueToSort; --j) {
				t[j] = t[j - 1];
			}
			t[j] = valueToSort;
		}
	}
	
	/*Tri le tableau t via la methode "Tri fusion"
	 * cf TD2 exo 5
	 */
	public static void triFusion(int[] t){
		if (t.length>0)
			triFusion(t, 0, t.length-1);
	}

	/* Sous-fonction (recursive) pour le tri fusion
	 * Trie le sous-tableau t[debut]..t[fin]
	 */
	private static void triFusion(int[] t, int debut, int fin){
		if(debut < fin)
		{
			int milieu = (debut+fin)/2;
			triFusion(t, debut, milieu);
			triFusion(t, milieu+1, fin);
			fusionner(t, debut, milieu, fin);
		}
	}

	/* Sous-fonction pour le tri fusion
	 * Suppose que, dans le tableau t, 
	 *       les 2 sous-tableaux t[deb1]..t[fin1] et t[fin1+1]..[t[fin2] sont deja tries
	 * Fusionne ces 2 sous-tableaux pour que le sous-tableau t[deb1]..t[fin2] soit trie
	 */
	private static void fusionner(int[] t, int deb1, int fin1, int fin2){
		int deb2 = fin1+1;
		//on recopie les elements du debut du tableau
		int[] t1 = new int[fin1-deb1+1];
		for(int i=deb1;i<=fin1;i++){
			t1[i-deb1]=t[i];
        }
		int compt1=deb1;
	    int compt2=deb2;
	    for(int i=deb1;i<=fin2;i++){        
	        if (compt1==deb2) //c'est que tous les elements du premier tableau ont ete utilises
	            break; //tous les elements ont donc ete classes
	        else if (compt2==(fin2+1)){ //c'est que tous les elements du second tableau ont ete utilises
	            t[i]=t1[compt1-deb1]; //on ajoute les elements restants du premier tableau
	            compt1++;
	        }
	        else if (t1[compt1-deb1]<t[compt2]){
	            t[i]=t1[compt1-deb1]; //on ajoute un element du premier tableau
	            compt1++;
	        }
	        else{
	            t[i]=t[compt2]; //on ajoute un element du second tableau
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
	
	/* Cree un fichier nomFichier.m contenant du code matlab initialisant un tableau T_nomFichier qui contient les elements de tab
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
			System.err.println("Probleme: " + e.getMessage()) ;
		    System.exit(2) ;
		}
	}
	
	public static void main(String[] args) {
		//Verification de l'implementation des tris
		int [] t = new int[10];
		int [] t2 = new int[10];
		int [] tCroissant = new int[10];
		int [] tDecroissant = new int[10];
		for(int k=0;k<t.length;k++){ //initialisation aleatoire
			t[k]=(int) (Math.random()*100);
			t2[k]=t[k];
			tCroissant[k] = k;
			tDecroissant[k] = t.length -k;
		}
		System.out.print("Avant le tri : "); afficher(t);
		triInsertion(t);
		System.out.print("Apres le tri par insertion: "); afficher(t);
		
		
		System.out.print("Avant le tri : "); afficher(tCroissant);
		triInsertion(tCroissant);
		System.out.print("Apres le tri par insertion: "); afficher(tCroissant);
		
		
		System.out.print("Avant le tri : "); afficher(tDecroissant);
		triInsertion(tCroissant);
		System.out.print("Apres le tri par insertion: "); afficher(tDecroissant);
		
		triFusion(t2);
		System.out.print("Apres le tri fusion:        "); afficher(t2);
		
		//Analyse du temps d'execution
		
		//A FAIRE : modifier les 3 valeurs suivantes
		int taille_init = 66000000;
		int taille_incr = 66000000;
		int taille_fin  = 67000000;
		
		List<Integer> tab_tailles = new ArrayList<Integer>();
		List<Integer> tab_temps = new ArrayList<Integer>();
		for(int n = taille_init; n<taille_fin; n=n+taille_incr){			  
			tab_tailles.add(n); //on sauvegarde la taille
			t = new int[n];
			tCroissant = new int[n];
			tDecroissant = new int[n];
			//A FAIRE : initialisation de t
			for(int k=0;k<n;k++){ //initialisation aleatoire
				t[k]=(int) (Math.random()*100);
				tCroissant[k] = k;
				tDecroissant[k] = n - k;
			}
			
//			long date1 = System.currentTimeMillis(); //on lance le chrono
//			triFusion(t); //on trie le tableau 
//			long date2 = System.currentTimeMillis(); //on arrete le chrono			
//			tab_temps.add((int)(date2 - date1)); //on sauvegarde le temps
//			System.out.println("Random : Temps de calcul pour n="+n+" : "+ tab_temps.get(tab_temps.size()-1)+" millisecondes.");
			long date1 = System.currentTimeMillis(); //on lance le chrono
			triInsertion(tCroissant); //on trie le tableau 
			long date2 = System.currentTimeMillis(); //on arrete le chrono
			tab_temps.add((int)(date2 - date1)); //on sauvegarde le temps
			System.out.println("Croissant : Temps de calcul pour n="+n+" : "+ tab_temps.get(tab_temps.size()-1)+" millisecondes.");
//			date1 = System.currentTimeMillis(); //on lance le chrono
//			triInsertion(tDecroissant); //on trie le tableau 
//			date2 = System.currentTimeMillis(); //on arrete le chrono
			//tab_temps.add((int)(date2 - date1)); //on sauvegarde le temps
			//System.out.println("Decroissant : Temps de calcul pour n="+n+" : "+ tab_temps.get(tab_temps.size()-1)+" millisecondes.");
		}
		
		//conversion des tableaux au format matlab
		tab_to_matlab("tailles", tab_tailles); 
		tab_to_matlab("temps", tab_temps);
	}

}
