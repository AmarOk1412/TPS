package robdd;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

// Pour l'affichage
import java.util.regex.Pattern;
import java.util.regex.Matcher;

//Représente un ROBDD sous forme de liste de Noeud_ROBDD
public class ROBDD {

	//Constantes pour les numéros des "feuilles" VRAI et FAUX
	public static final int idFalse = 0;
	public static final int idTrue = 1;

	//liste représentant le ROBDD
	private List<Noeud_ROBDD> R;
	
	//construit un ROBDD vide
	public ROBDD(){
		R = new LinkedList<Noeud_ROBDD>();
	}
	//ajoute le Noeud_ROBDD n au ROBDD courant
	public void ajouter(Noeud_ROBDD n) {
		R.add(n);
	}

		
	//renvoie le nombre de noeuds du ROBDD
	public int nb_noeuds() {
		return R.size()+2; // longueur de la liste R + les 2 noeuds correspondants à VRAI et FAUX
	}

	@Override
	public String toString() {
		return R.toString();
	}
	
	// renvoie l'index, dans la liste R,  du noeud BDD associé à la variable nom et dont les fils droit et gauche sont d'indices respectifs fd et fg.
	// Si ce noeud n'existe pas dans le diagramme, la fonction renvoie -1.
	public int obtenirROBDDIndex(String nom, int fg, int fd) {
		Iterator<Noeud_ROBDD> it = R.iterator();
		while(it.hasNext())
		{
			Noeud_ROBDD n = it.next();
			if(n.getNom().equals(nom) && n.getIdFilsGauche() == fg && n.getIdFilsDroit() == fd)
			  return n.getId();
		}
		return -1;
	}
	
	//Trouve une solution si c'est SAT
	public String trouve_sat()
	{
	  String ret = "";
	  Iterator<Noeud_ROBDD> it = R.iterator();
	  int toSearch = 1;
		while(it.hasNext())
		{
			Noeud_ROBDD n = it.next();
			if(n.getIdFilsDroit() == toSearch)
			{
				toSearch = n.getId();
				ret += n.getNom() + ".";
			}
			if(n.getIdFilsGauche() == toSearch)
				toSearch = n.getId();
		}
		
		if(toSearch == 1)
			return "Non SAT";
		else
			return ret;
	}

	//Affiche le tableau solution pour le probleme des dames
	public void reines_affiche_sat(int n)
	{
		//Le tableau contenant true pour les cases possédant une dame
		boolean[] solution = new boolean[n*n];
	  Iterator<Noeud_ROBDD> it = R.iterator();
	  int toSearch = 1;
		while(it.hasNext())
		{
			Noeud_ROBDD node = it.next();
			if(node.getIdFilsDroit() == toSearch)
			{
				toSearch = node.getId();
				try
				{
					//Pour savoir quelle variable correspond à quelle case
					Pattern p = Pattern.compile("x([0-9])([0-9])");
					Matcher m = p.matcher(node.getNom());
					m.matches();
					solution[Integer.parseInt(m.group(1))*n+Integer.parseInt(m.group(2))] = true;
				}
				catch (Exception e)
				{
				
				}
			}
			if(node.getIdFilsGauche() == toSearch)
				toSearch = node.getId();
		}
		
	/**Affichage**/
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < 3*n; ++j)
			System.out.print("_");
		System.out.print("\n");
		for(int j = 0; j < n; ++j)
			if(solution[i*n+j])
				System.out.print("|X|");
			else
				System.out.print("| |");
		System.out.print("\n");
	}
	for(int j = 0; j < 3*n; ++j)
		System.out.print("_");
	System.out.print("\n");
	}
}
