/**** on va ici implémenter la transformée de Fourier rapide 1D ****/
import java.lang.Math;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;
import static java.lang.Math.pow;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;


public class FFT_1D {

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
	
	//"combine" c1 et c2 selon la formule vue en TD
	// c1 et c2 sont de même taille
	// la taille du résultat est le double de la taille de c1
	public static CpxTab combine(CpxTab c1, CpxTab c2) {
		assert (c1.taille()==c2.taille()) : "combine: c1 et c2 ne sont pas de même taille, taille c1="+c1.taille()+" taille c2="+c2.taille();
		int taille = c1.taille()+c2.taille();
		CpxTab res = new CpxTab(taille);
		for(int i=0; i<c1.taille(); i++)
		{
			//première partie du tableau
			double termeReel =c2.get_p_reel(i)*Math.cos(2*Math.PI*i/taille)-c2.get_p_imag(i)*Math.sin(2*Math.PI*i/taille);
			double termeImag = c2.get_p_imag(i)*Math.cos(2*Math.PI*i/taille)+c2.get_p_reel(i)*Math.sin(2*Math.PI*i/taille);
			
			res.set_p_reel(i,c1.get_p_reel(i)+termeReel);
			res.set_p_imag(i,c1.get_p_imag(i)+termeImag);
			//deuxième partie du tableau
			res.set_p_reel(c1.taille()+i,c1.get_p_reel(i)-termeReel);
			res.set_p_imag(c1.taille()+i,c1.get_p_imag(i)-termeImag);
			
		}
		return res;
	}

	//renvoie la TFD d'un tableau de complexes
	//la taille de x doit être une puissance de 2
	public static CpxTab FFT(CpxTab x) {
		//A FAIRE : Test d'arrêt
		if(x.taille()==1)
		  return x;
		assert (x.taille()%2==0) : "FFT: la taille de x doit être une puissance de 2";
		
		CpxTab pair = new CpxTab(x.taille()/2);
		CpxTab impair = new CpxTab(x.taille()/2);
		for(int i=0; i<x.taille(); i++)
		{
			if(i%2==0)
			{
				pair.set_p_reel(i/2,x.get_p_reel(i));
				pair.set_p_imag(i/2,x.get_p_imag(i));
			}
			else
			{
				impair.set_p_reel((i-1)/2,x.get_p_reel(i));
				impair.set_p_imag((i-1)/2,x.get_p_imag(i));
			}
		}

		return combine(FFT(pair), FFT(impair));
	}

	//renvoie la TFD d'un tableau de réels
	//la taille de x doit être une puissance de 2
	public static CpxTab FFT(double[] x) {
		return FFT(new CpxTab(x));
	}
			
	//renvoie la transformée de Fourier inverse de y
	public static CpxTab FFT_inverse(CpxTab y) {
		//A FAIRE
		CpxTab t = new CpxTab(y.taille());
		for(int i = 0; i < y.taille(); ++i)
			t.set_p_reel(i, 1./(double)y.taille());
		return CpxTab.multiplie(t, (FFT(y.conjuge())).conjuge());
	}
	
	//calcule le produit de deux polynômes en utilisant la FFT
	//tab1 et tab2, sont les coefficients de ces polynômes
	// CpxTab sera le tableau des coefficients du polynôme produit (purement réel)
	public static CpxTab multiplication_polynome_viaFFT(double[] tab1, double[] tab2) {
		
		//on commence par doubler la taille des vecteurs en rajoutant des zéros à la fin (cf TD)
		double[] t1 = new double[2*tab1.length], t2 = new double[2*tab1.length];
		for (int i = 0; i < tab1.length; i++) {
			t1[i] = tab1[i];
			t2[i] = tab2[i];
		}
		CpxTab fftTab1 = FFT(t1);
		CpxTab fftTab2 = FFT(t2);
		
		CpxTab toInv = CpxTab.multiplie(fftTab1, fftTab2);
		
		return FFT_inverse(toInv);
	}

	
	//renvoie un tableau de réels aléatoires
	//utile pour tester la multiplication de polynômes
	public static double[] random(int n) {
		double[] t = new double[n];

		for (int i = 0; i < n; i++)
			t[i] = Math.random();
		return t;
	}

	//effectue la multiplication de polynômes représentés par coefficients
	// p1, p2 les coefficients des deux polynômes P1 et P2
	// renvoie les coefficients du polynôme P1*P2
	private static double [] multiplication_polynome_viaCoeff(double[] p1, double[] p2){
		
		int n = p1.length + p2.length - 1;
		double a,b;
		double [] out = new double[n];
		for (int k = 0; k < n; k++) {
			for (int i = 0; i <= k; i++) {
				a = (i<p1.length) ? p1[i]:0;
				b = (k-i<p2.length) ? p2[k-i] : 0;
				out[k] += a*b;
			}
		}
		return out;
	}
	

	//affiche un tableau de réels
	private static void afficher(double [] t){
		System.out.print("[");
		for(int k=0;k<t.length;k++){
			System.out.print(t[k]);
			if (k<(t.length-1))
				System.out.print(" ");
		}
		System.out.println("]");
	}
	
	public static void main(String[] args) {
		/* Pour tester exo 2: calculez et affichez TFD(1,2,3,4) */
		double [] t1 = {1,2,3,4};
		CpxTab T = FFT(t1);
		System.out.println(T.toString());
		/* Pour tester exo 3: calculez et affichez TFD_inverse(TFD(1,2,3,4)) */
		CpxTab Tinv = FFT_inverse(T);
		System.out.println(Tinv.toString());
		/* Pour tester Partie 3 : multiplication polynomiale */
	
		System.out.println("-----------------------------------------------------");
		System.out.println("   Comparaison des 2 méthodes de multiplications polynomiales");
		double[] t5 = {1,2,3,4};
		double[] t6 = {-3,2,0,-5};
		System.out.println("mult via FFT  --> "+multiplication_polynome_viaFFT(t5, t6));
		System.out.print(  "mult via coeff -> ");afficher(multiplication_polynome_viaCoeff(t5, t6));
		
		// Pour étude du temps de calcul 
		int n = 16384;  // taille des polynômes à multiplier (testez différentes valeurs en gardant des multiples de 2)
		
		List<Integer> tab_temps = new ArrayList<Integer>();
		List<Integer> tab_taille = new ArrayList<Integer>();
		for(int taille = 1; taille <= n; taille*=2)
		{
			double[] tab1 = new double[taille];
			double[] tab2 = new double[taille];
			for(int i = 0; i < taille; ++i)
			{
				tab1[i] = Math.random()*100;
				tab2[i] = Math.random()*100;
			}
			long date1 = System.currentTimeMillis(); //on lance le chrono
//			multiplication_polynome_viaCoeff(tab1, tab2); //on trie le tableau 
			multiplication_polynome_viaFFT(tab1, tab2);
			long date2 = System.currentTimeMillis(); //on arrete le chrono
			tab_temps.add((int)(date2 - date1)); //on sauvegarde le temps
			tab_taille.add(taille);
			System.out.println(taille);
			
		}

		tab_to_matlab("tailles", tab_taille); 
		tab_to_matlab("temps", tab_temps);
	}

}
