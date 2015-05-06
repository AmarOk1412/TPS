/**
   Implementation matricielle des graphes.
*/

import java.util.*;

public class GrapheMatr extends GrapheAbs {

    // attributs

    private int nmax; // nombre maximum de sommets

    private int nbS; // nombre de sommets
    private Val valS[]; // valeur des sommets (null si invalide)

    private int nbA; // nombre d'arcs
    private Val valA[][]; // valeur des arcs (null si invalide)


    // constructeurs

    /**
       Construit un graphe vide avec representation matricielle
       et un nombre limite de sommets.

       @param n est le nombre maximum de sommets
    */
    public GrapheMatr(int n) {
	nmax = n;
	nbS = 0;
	valS = new Val[n];
	nbA = 0;
	valA = new Val[n][n];
    }

    public void recreer(int n) {
	nmax = n;
	nbS = 0;
	valS = new Val[n];
	nbA = 0;
	valA = new Val[n][n];
    }


    // verification des identificateurs de sommets

    private void verifBorne(int i) throws Exception {
	if (i < 0 || i >= nmax) { throw new Exception("Le numero de sommet " + i + " est en dehors des bornes");};
    }

    private void verifNonValid(int i) throws Exception {
	if (valS[i] != null) { throw new Exception("Le sommet " + i + " est deja valide."); };
    }

    private void verifValid(int i) throws Exception  {
	if (valS[i] == null) { throw new Exception("Le sommet " + i + " n'est pas valide."); };
    }

    private void verifValidArc(int i, int j) throws Exception  {
	if (valA[i][j] == null) { throw new Exception("L'arc (" + i + "," + j + ") n'est pas valide");};
    }


    // operations sur les sommets

    public void ajoutSom(int i, Val v) throws Exception  {
	verifBorne(i);
	verifNonValid(i);
	nbS++;
	valS[i] = v;
    }

    public boolean validSom(int i) throws Exception  {
	verifBorne(i);
	return (valS[i] != null);
    }

    public Val valSom(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	return valS[i];
    }

    public void changeValSom(int i, Val v) throws Exception  {
	verifBorne(i);
	verifValid(i);
	valS[i] = v;
    }

    public void oterSom(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	nbS--;
	valS[i] = null;
	for (int j=0; j < nmax; j++) {
	    if (valA[i][j] != null) {
		nbA--;
		valA[i][j] = null;
	    };
	    if (valA[j][i] != null) {
		nbA--;
		valA[j][i] = null;
	    }
	}
    }


    // operations sur les arcs

    public void ajoutArc(int i, int j, Val w) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	if (valA[i][j] == null) {
	    nbA++;
	};
	valA[i][j] = w;
    }

    public boolean validArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	return (valA[i][j] != null);
    }

    public Val valArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	verifValidArc(i,j);
	return valA[i][j];
    }

    public void changeValArc(int i, int j, Val w) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	if (valA[i][j] == null) { nbA++;};
	valA[i][j] = w;
    }

    public void oterArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	if (valA[i][j] != null) { nbA--;};
	valA[i][j] = null;
    }


    // acces au graphe

    public int nmax() {
	return nmax;
    }

    public int nbSom() {
	return nbS;
    }

    public int nbArc() {
	return nbA;
    }

    public Set ensSom() {
	Set ens = new TreeSet();
	for (int i=0; i<nmax; i++) {
	    if (valS[i] != null) {
		ens.add(new Integer(i));
	    }
	};
	return ens;
    }

    public Set ensPred(int j) throws Exception  {
	verifBorne(j);
	verifValid(j);
	Set preds = new TreeSet();
	for (int i=0; i<nmax; i++) {
	    if (valS[i] != null && valA[i][j] != null) {
		preds.add(new Integer(i));
	    }
	};
	return preds;
    }
	
    public Set ensSucc(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	Set succs = new TreeSet();
	for (int j=0; j<nmax; j++) {
	    if (valS[j] != null && valA[i][j] != null) {
		succs.add(new Integer(j));
	    }
	};
	return succs;
    }

} // class

