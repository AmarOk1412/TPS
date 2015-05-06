import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;


public class TP1
{
	public static Graphe fermeture(Graphe g) throws Exception
	{
		//Algorithme de Floyd-Warshall
		int nbSommet = g.nmax();
		for(int k = 1; k<nbSommet; ++k)
			for(int i = 1; i<nbSommet; ++i)
				for(int j = 1; j<nbSommet; ++j)
					//Partie routage
					if(g.validArc(i, k) && g.validArc(k, j))
						//Si on a une valeur plus petite pour y aller, on la met
						//Vérifier si l'arc est déjà marqué
						if(g.valArc(i, k) instanceof ValEnt)
						  g.ajoutArc(i, j, g.valArc(i, k));
						//Sinon on met k
						else
						  g.ajoutArc(i, j, new ValEnt(k));
		return g;
	}

	public static void main(String[] args)
	{
		Graphe liaisons = new GrapheDicoSucc(10); // initialisation d'un graphe
		try
		{
			//Fichier d'entrée
			File file = new File("graphe");
			FileInputStream fis = null;

			try {
				fis = new FileInputStream(file);
			} catch (IOException e) {
				e.printStackTrace();
			}

			//Création du graphe
			System.out.println("Entrer la représentation de votre graphe suivant le format \"successeurs\"") ;	
			liaisons.lireSuccs(fis, new Val(), new Val());

			System.out.println("FICHIER GRAPHE LU");
			System.out.println("\nReprésentation du graphe suivant le format \"arcs explicites\"") ;
			//Fichier de sortie
			PrintStream fop = null;
			try {
				fop = new PrintStream(new FileOutputStream("grapheOut"));
			} catch (IOException e) {
				e.printStackTrace();
			}
			//Écriture du graphe
			liaisons.ecrireArcs(fop);
			fis.close();
			System.out.println("FICHIER GRAPHEOUT ÉCRIT");
			//fermeture transitive
			fermeture(liaisons);
			try {
				fop = new PrintStream(new FileOutputStream("fermetureGraphe"));
			} catch (IOException e) {
				e.printStackTrace();
			}
			//écriture et libération
			liaisons.ecrireArcs(fop);
			fis.close();
			System.out.println("FICHIER FERMETUREGRAPHE ÉCRIT");

		}
		catch (IOException e)
		{
			e.printStackTrace();
			System.err.println("Une erreur est survenue durant la lecture du fichier");
			System.exit(1);
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.err.println("Une erreur est survenue durant la construction du graphe");
			System.exit(1);
		}
	}
}

