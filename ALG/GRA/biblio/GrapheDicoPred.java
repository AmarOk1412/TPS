/**
   Implementation des graphes par dictionnaires de predecesseurs.
*/

import java.util.*;

public class GrapheDicoPred extends GrapheAbs {

    // attributs

    private int nmax; // nombre maximum de sommets

    private int nbS; // nombre de sommets
    private Hashtable valS; // valeur des sommets valides en fonction des identifiants de sommets
    // les cles sont des identifiants de sommet, et les valeurs des instances de ValeurGraphe

    private int nbA; // nombre d'arcs
    private Hashtable pred; // predecesseurs (et valeur de l'arc associe) en fonction des identifiants de sommets
    // les cles sont des identifiants de sommets, et les valeurs sont des Hashtable,
    // dont les cles sont les identifiants des sommets predecesseurs et les valeurs des instances de ValeurGraphe


    // constructeurs

    /**
       Construit un graphe vide represente par un dictionnaire de predecesseurs
       et un nombre limite de sommets.

       @param n est le nombre maximum de sommets
    */
    public GrapheDicoPred(int n) {
	nmax = n;
	nbS = 0;
	valS = new Hashtable(n);
	nbA = 0;
	pred = new Hashtable(n);
    }

    public void recreer(int n) {
	nmax = n;
	nbS = 0;
	valS = new Hashtable(n);
	nbA = 0;
	pred = new Hashtable(n);
    }


    // verification des identificateurs de sommets

    private boolean validS(int i) {
	return valS.containsKey(new Integer(i));
    }

    private boolean validA(int i, int j) {
	Integer ii = new Integer(i);
	Integer jj = new Integer(j);
	return pred.containsKey(jj) && ((Hashtable) pred.get(jj)).containsKey(ii);
    }

    private void verifBorne(int i) throws Exception {
	if (i < 0 || i >= nmax) { throw new Exception("Le numero de sommet " + i + " est en dehors des bornes");};
    }

    private void verifNonValid(int i) throws Exception {
	if (validS(i)) { throw new Exception("Le sommet " + i + " est deja valide."); };
    }

    private void verifValid(int i) throws Exception  {
	if (! validS(i)) { throw new Exception("Le sommet " + i + " n'est pas valide."); };
    }

    private void verifValidArc(int i, int j) throws Exception  {
	if (! validA(i,j)) { throw new Exception("L'arc (" + i + "," + j + ") n'est pas valide");};
    }


    // operations sur les sommets

    public void ajoutSom(int i, Val v) throws Exception  {
	verifBorne(i);
	verifNonValid(i);
	nbS++;
	Integer ii = new Integer(i);
	valS.put(ii, v);
	pred.put(ii, new Hashtable(nmax));
    }

    public boolean validSom(int i) throws Exception  {
	verifBorne(i);
	return validS(i);
    }

    public Val valSom(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	return (Val) valS.get(new Integer(i));
    }

    public void changeValSom(int i, Val v) throws Exception  {
	verifBorne(i);
	verifValid(i);
	valS.put(new Integer(i), v);
    }

    public void oterSom(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	Integer ii = new Integer(i);
	nbS--;
	valS.remove(ii);
	// suppression des arcs adjacents
	nbA = nbA - ((Hashtable) pred.get(ii)).size();
	pred.remove(ii);
	Enumeration it = pred.elements();
	while (it.hasMoreElements()) {
	    Hashtable h = (Hashtable) it.nextElement();
	    if (h.containsKey(ii)) {
		nbA--;
		h.remove(ii);
	    }
	}
    }


    // operations sur les arcs

    public void ajoutArc(int i, int j, Val w) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	Integer jj = new Integer(j);
	if (! validA(i,j)) { nbA++;};
	((Hashtable) pred.get(jj)).put(new Integer(i), w);
    }

    public boolean validArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	return validA(i,j);
    }

    public Val valArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	verifValidArc(i,j);
	return (Val) ((Hashtable) pred.get(new Integer(j))).get(new Integer(i));
    }

    public void changeValArc(int i, int j, Val w) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	Integer jj = new Integer(j);
	if (! validA(i,j)) { nbA++;};
	((Hashtable) pred.get(jj)).put(new Integer(i), w);
    }

    public void oterArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	if (validA(i,j)) {
	    nbA--;
	    ((Hashtable) pred.get(new Integer(j))).remove(new Integer(i));
	};
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
	return valS.keySet();
    }

    public Set ensSucc(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	Integer ii = new Integer(i);
	Set succs = new TreeSet();
	Iterator it = pred.keySet().iterator();
	while (it.hasNext()) {
	    Integer jj = (Integer) it.next();
	    if (((Hashtable) pred.get(jj)).containsKey(ii)) {
		succs.add(jj);
	    }
	};
	return succs;
    }
	
    public Set ensPred(int j) throws Exception  {
	verifBorne(j);
	verifValid(j);
	return ((Hashtable) pred.get(new Integer(j))).keySet();
    }

} // class


