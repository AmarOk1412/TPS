import java.util.LinkedList;
import java.util.List;

import robdd.ROBDD;
import expression.*;

public class Main {

	public static void main(String[] args) {
		System.out.println("PARTIE I :");
		Partie1();
		//2:
		System.out.println("PARTIE II :");
		NQueensProblem(4);
	}
	
	static void Partie1()
	{
		//EXEMPLE 
		Expression exp = new Et(new Atome("x"),new Atome("y")); // représente (x ^ y)
		System.out.println(exp.atomes()); // affiche la liste des atomes (=variables booléennes) présents dans exp
		exp = exp.remplace("x",true); // exp vaut maintenant (true ^ y)
		//System.out.println(exp.evalue()); // <- erreur car (true ^ y) ne peut pas être évalué
		exp = exp.remplace("y",false); // exp vaut maintenant (true ^ false)
		System.out.println(exp.evalue());
	
		//Construction d'un ROBBD
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
		//Affichage
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
		System.out.println("\n Arbre de exp : \n" + exp.arbre(ordre_atomes)); // <- que se passe-t-il ? Simplification 
		Expression exp2 = new Et(new Atome("x"), new Non(new Atome("y"))); // représente (x ^ y)
		System.out.println("\n Arbre de exp2 : \n" + exp2.arbre(ordre_atomes));
		System.out.println(exp2.robdd().trouve_sat());
	}
	
	static void NQueensProblem(int n)
	{
		Expression expDame = new Constante(true);
		//Une dame par ligne
		for(int i = 0; i < n; ++i)
		{
			Expression temp2 = new Constante(false);
			for(int k = 0; k < n; ++k)
			{
				Expression temp = new Constante(true);
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
		
		
		//Une dame par colonne
		for(int j = 0; j < n; ++j)
		{
			Expression temp2 = new Constante(false);
			for(int k = 0; k < n; ++k)
			{
				Expression temp = new Constante(true);
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
		
		//Traitement des diagonales 
		for(int i = 0; i < n; ++i)
		{
			Expression temp2 = new Constante(false);
			for(int j = 0; j < n; ++j)
			{
				Expression temp = new Constante(true);
				for(int k = 0; k < n; ++k)
				{
					int v = j+k-i;
					int w = j+i-k;
					boolean find = false;
					if(i != k && v < n && v >= 0)
					{
						temp = new Et(new Non(new Atome("x" + k + v)), temp);
						find = true;
					}
					if(i!=k && w < n && w >= 0)
					{
						temp = new Et(new Non(new Atome("x" + k + w)), temp);
						find = true;
					}
					if(!find)
						temp = new Et(new Atome("x" + i + j), temp);
						
				}
				temp2 = new Ou(temp2, temp);
			}
			expDame = new Et(expDame, temp2);
		}
		//La réponse fournit par un String
		System.out.println(expDame.robdd().trouve_sat());
		//Ou par affichage visuel
		expDame.robdd().reines_affiche_sat(n);
	}
}
