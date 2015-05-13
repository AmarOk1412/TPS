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
		
		ROBDD ro = ex2.robdd();
		System.out.println(ro);
		System.out.println(ex2.atomes());
//		ex2 = ex2.remplace("x1",true);
//		ex2 = ex2.remplace("y1",true);
//		ex2 = ex2.remplace("x2",false);
//		ex2 = ex2.remplace("y2",false);
//		System.out.println(ex2.evalue());
//		System.out.println(ex2.estVrai());
//		System.out.println(ex2.estFaux());
		List<String> ordre_atomes = new LinkedList<String>();
		ordre_atomes.add("x1");
		ordre_atomes.add("y1");
		ordre_atomes.add("x2");
		ordre_atomes.add("y2");
		System.out.println("\n Arbre de ex2 : \n" + ex2.arbre(ordre_atomes)); // <- que se passe-t-il ? 
		
		System.out.println(ex2.robdd().trouve_sat());
		
		
		//Affichage de l'arbre associé à l'expression exp pour l'ordre x > y 
		ordre_atomes = new LinkedList<String>();
		ordre_atomes.add("x");
		ordre_atomes.add("y");
		System.out.println("\n Arbre de exp : \n" + exp.arbre(ordre_atomes)); // <- que se passe-t-il ? 
		Expression exp2 = new Et(new Atome("x"), new Non(new Atome("y"))); // représente (x ^ y)
		System.out.println("\n Arbre de exp2 : \n" + exp2.arbre(ordre_atomes));
		System.out.println(exp2.robdd().trouve_sat());
		
		
		//2:
		int n = 4;
		Expression expDame = new Atome("true");
		//Au moins une dame par ligne
		for(int i = 0; i < n; ++i)
		{
			Expression temp2 = new Atome("false");
			for(int k = 0; k < n; ++k)
			{
				Expression temp = new Atome("true");
				for(int j = 0; j < n; ++j)
				{
					if(j != k)
						temp = new Et(new Non(new Atome("x"+ i + j)), temp);
					else
						temp = new Et(new Atome("x"+ i + j), temp);
				}
				temp2 = new Ou(temp2, temp);
			}
			expDame = new Et(expDame, temp2);
		}
		
		
		//Au moins une dame par colonne
		for(int j = 0; j < n; ++j)
		{
			Expression temp2 = new Atome("false");
			for(int k = 0; k < n; ++k)
			{
				Expression temp = new Atome("true");
				for(int i = 0; i < n; ++i)
				{
					if(i != k)
						temp = new Et(new Non(new Atome("x"+ i + j)), temp);
					else
						temp = new Et(new Atome("x"+ i + j), temp);
				}
				temp2 = new Ou(temp2, temp);
			}
			expDame = new Et(expDame, temp2);
		}
		
		//Diagonales !
		for(int j = 0; j < n; ++j)
		{
			Expression temp2 = new Atome("false");
			for(int k = 0; k < n; ++k)
			{
				Expression temp = new Atome("x"+ k + j);
				for(int i = n; j+k-i < n; --i)
				{
					if(i != k)
						temp = new Et(new Non(new Atome("x"+ k + Integer.toString(j+k-i))), temp);
				}
				temp2 = new Implique(temp2, temp);
			}
			expDame = new Et(expDame, temp2);
		}
		
		System.out.println(expDame.robdd().trouve_sat());
	}
}
