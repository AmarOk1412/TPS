import java.io.IOException;

public class TP1
{
	public static void main(String[] args)
	{
		Graphe liaisons = new GrapheDicoSucc(10); // initialisation d'un graphe
		try
		{
			System.out.println("Entrer la représentation de votre graphe suivant le format \"successeurs\"") ;	
			liaisons.lireSuccs(System.in, new Val(), new Val());
			System.out.println("\nReprésentation du graphe suivant le format \"arcs explicites\"") ;
			liaisons.ecrireArcs(System.out);
			
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
		
