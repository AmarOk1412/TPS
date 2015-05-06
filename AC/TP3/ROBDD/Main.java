import java.util.LinkedList;
import java.util.List;

import robdd.ROBDD;
import expression.*;

public class Main {

	public static void main(String[] args) {
		//EXEMPLE 
		Expression exp = new Et(new Atome("x"),new Atome("y")); // représente (x ^ y)
		System.out.println(exp.atomes()); // affiche la liste des atomes (=variables booléennes) présents dans exp
		exp = exp.remplace("x",true); // exp vaut maintenant (true ^ y)
		//System.out.println(exp.evalue()); // <- erreur car (true ^ y) ne peut pas être évalué
		exp = exp.remplace("y",false); // exp vaut maintenant (true ^ false)
		System.out.println(exp.evalue());
		
		Expression ex2 = new Et(
											new Equiv(new Atome("x1"),new Atome("y1")), 
											new Equiv(new Atome("x2"),new Atome("y2"))
										);
		System.out.println(ex2.atomes());
		ex2 = ex2.remplace("x1",true);
		ex2 = ex2.remplace("y1",true);
		ex2 = ex2.remplace("x2",false);
		ex2 = ex2.remplace("y2",false);
		System.out.println(ex2.evalue());
		System.out.println(ex2.estVrai());
		System.out.println(ex2.estFaux());
		
		//Affichage de l'arbre associé à l'expression exp pour l'ordre x > y 
		List<String> ordre_atomes = new LinkedList<String>();
		ordre_atomes.add("x");
		ordre_atomes.add("y");
		System.out.println("\n Arbre de exp : \n" + exp.arbre(ordre_atomes)); // <- que se passe-t-il ? 
		Expression exp2 = new Et(new Atome("x"),new Atome("y")); // représente (x ^ y)
		System.out.println("\n Arbre de exp2 : \n" + exp2.arbre(ordre_atomes));		
	}
}
