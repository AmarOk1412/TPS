/**
   Implementation des graphes par dictionnaires de successeurs.
*/

import java.util.*;

public class GrapheDicoSucc extends GrapheAbs {

    // attributs

    private int nmax; // nombre maximum de sommets

    private int nbS; // nombre de sommets
    private Hashtable valS; // valeur des sommets valides en fonction des identifiants de sommets
    // les cles sont des identifiants de sommet, et les valeurs des instances de Val

    private int nbA; // nombre d'arcs
    private Hashtable succ; // successeurs (et valeur de l'arc associe) en fonction des identifiants de sommets
    // les cles sont des identifiants de sommets, et les valeurs sont des Hashtable,
    // dont les cles sont les identifiants des sommets successeurs et les valeurs des instances de Val


    // constructeurs

    /**
       Construit un graphe vide represente par un dictionnaire de successeurs
       et un nombre limite de sommets.

       @param n est le nombre maximum de sommets
    */
    public GrapheDicoSucc(int n) {
	nmax = n;
	nbS = 0;
	valS = new Hashtable(n);
	nbA = 0;
	succ = new Hashtable(n);
    }

    public void recreer(int n) {
	nmax = n;
	nbS = 0;
	valS = new Hashtable(n);
	nbA = 0;
	succ = new Hashtable(n);
    }


    // verification des identificateurs de sommets

    private boolean validS(int i) {
	return valS.containsKey(new Integer(i));
    }

    private boolean validA(int i, int j) {
	Integer ii = new Integer(i);
	Integer jj = new Integer(j);
	return succ.containsKey(ii) && ((Hashtable) succ.get(ii)).containsKey(jj);
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
	succ.put(ii, new Hashtable(nmax));
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
	nbA = nbA - ((Hashtable) succ.get(ii)).size();
	succ.remove(ii);
	Enumeration it = succ.elements();
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
	Integer ii = new Integer(i);
	if (! validA(i,j)) { nbA++;};
	((Hashtable) succ.get(ii)).put(new Integer(j), w);
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
	return (Val) ((Hashtable) succ.get(new Integer(i))).get(new Integer(j));
    }

    public void changeValArc(int i, int j, Val w) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	Integer ii = new Integer(i);
	if (! validA(i,j)) { nbA++;};
	((Hashtable) succ.get(ii)).put(new Integer(j), w);
    }

    public void oterArc(int i, int j) throws Exception  {
	verifBorne(i);
	verifBorne(j);
	verifValid(i);
	verifValid(j);
	if (validA(i,j)) {
	    nbA--;
	    ((Hashtable) succ.get(new Integer(i))).remove(new Integer(j));
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

    public Set ensPred(int j) throws Exception  {
	verifBorne(j);
	verifValid(j);
	Integer jj = new Integer(j);
	Set preds = new TreeSet();
	Iterator it = succ.keySet().iterator();
	while (it.hasNext()) {
	    Integer ii = (Integer) it.next();
	    if (((Hashtable) succ.get(ii)).containsKey(jj)) {
		preds.add(ii);
	    }
	};
	return preds;
    }
	
    public Set ensSucc(int i) throws Exception  {
	verifBorne(i);
	verifValid(i);
	return ((Hashtable) succ.get(new Integer(i))).keySet();
    }

} // class


