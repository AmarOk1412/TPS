/**
   Implementation partielle des graphes, independante de la representation concrete.
*/

import java.util.*;
import java.io.*;

public abstract class GrapheAbs implements Graphe, Cloneable {

    public void copie(Graphe src) throws Exception {
	// le graphe est d'abord vide
	recreer(src.nmax());
	// copie des sommets et de leur valeur
	Iterator its = src.iterSom();
	while (its.hasNext()) {
	    int s = ((Integer) its.next()).intValue();
	    ajoutSom(s,src.valSom(s));
	};
	// copie des arcs et de leur valeur
	Iterator ita = src.iterSom();
	while (ita.hasNext()) {
	    int i = ((Integer) ita.next()).intValue();
	    Iterator itsucc = src.ensSucc(i).iterator();
	    while (itsucc.hasNext()) {
		int j = ((Integer) itsucc.next()).intValue();
		ajoutArc(i,j,src.valArc(i,j));
	    }
	}
    }

    public void ajoutSom(int i) throws Exception {
	ajoutSom(i, new Val());
    }

    public void ajoutArc(int i, int j) throws Exception  {
	ajoutArc(i, j, new Val());
    }

    public boolean vide() {
	return (this.nbSom() == 0);
    }

    public Iterator iterSom() {
	return this.ensSom().iterator();
    }

    public Set ensPtsEntree() {
	Iterator it = this.iterSom();
	Set res = new TreeSet(); // resultat initial
	while (it.hasNext()) {
	    int i = ((Integer) it.next()).intValue();
	    try {
		if (this.ensPred(i).isEmpty()) { // i est un point d'entree
		    res.add(new Integer(i)); // ajouter i aux points d'entree
		}
	    }
	    catch(Exception e) {} // l'iteration garantit que i est valide
	};
	return res;
    }

    public Set ensPtsSortie() {
	Iterator it = this.iterSom();
	Set res = new TreeSet(); // resultat initial
	while (it.hasNext()) {
	    int i = ((Integer) it.next()).intValue();
	    try {
		if (this.ensSucc(i).isEmpty()) { // i est un point de sortie
		    res.add(new Integer(i)); // ajouter i aux points de sortie
		}
	    }
	    catch(Exception e) {} // l'iteration garantit que i est valide
	};
	return res;
    }

    public void oterEnsSom(Set ens) throws Exception {
	Iterator it = ens.iterator();
	while (it.hasNext()) { // pour tout sommet dans ens
	    int i = ((Integer) it.next()).intValue();
	    this.oterSom(i);  // on l'ote du graphe
	};
    }


    /*
       Ecriture d'un graphe valué représenté par des arcs explicites.
       Format : nmax ( sommet valeur-sommet )* 0 ( sommet sommet valeur-arc)* 0 0
       Nombre max de sommets puis liste des sommets (avec valeur) puis liste des arcs (avec valeur).
    */
    public void ecrireArcs(PrintStream out) throws IOException, Exception {
	// ecriture de nmax et creation du graphe
	out.println(nmax()-1);
	// ecriture des sommets
	Iterator itSom = iterSom();
	int i = 0;
	while (itSom.hasNext()) {
	    i = ((Integer) itSom.next()).intValue();
	    out.print(i);
	    out.print(' ');
	    valSom(i).ecrire(out);
	    out.println();
	};
	out.println("0");
	// ecriture des arcs
	itSom = iterSom(); // nouvel iterateur
	while (itSom.hasNext()) {
	    i = ((Integer) itSom.next()).intValue();
	    Set succs = ensSucc(i);
	    Iterator itSucc = succs.iterator();
	    while (itSucc.hasNext()) {
		int j = ((Integer) itSucc.next()).intValue();
		out.print(i);
		out.print(' ');
		out.print(j);
		out.print(' ');
		valArc(i,j).ecrire(out);
		out.println();
	    }
	};
	out.println("0 0");
    }


    /*
       Ecriture d'un graphe valué représenté par un dictionnaire de successeurs.
       Format : nmax ( sommet valeur-sommet ( sommet valeur-arc )* 0 )* 0
       Chaque sommet est suivi de la liste de ses successeurs,
       avec pour chaque successeur son numéro.
    */
    public void ecrireSuccs(PrintStream out) throws IOException, Exception {
	// ecriture de nmax et creation du graphe
	out.println(nmax()-1);
	// ecriture des sommets
	Iterator itSom = iterSom();
	while (itSom.hasNext()) {
	    int i = ((Integer) itSom.next()).intValue();
	    out.print(i);
	    out.print(' ');
	    valSom(i).ecrire(out);
	    out.print(' ');
	    // ecriture des successeurs
	    Set succs = ensSucc(i);
	    Iterator itSucc = succs.iterator();
	    while (itSucc.hasNext()) {
		int j = ((Integer) itSucc.next()).intValue();
		out.print(j);
		out.print(' ');
		valArc(i,j).ecrire(out);
		out.print(' ');
	    };
	    out.println(0);
	};
	out.println(0);
    }


    // lecture d'un entier
    private int lireEntier(InputStream in) throws IOException
    {
    	StringBuffer buf = new StringBuffer();
    	try
    	{
    		char c = (char) in.read ();
    		while (c == ' ' || c == '\n' || c == '\t')
    		{
    			c = (char) in.read();
    		}
    		while (c >= '0' && c <= '9')
    		{
    			buf.append(c);
    			c = (char) in.read ();
    		}
    		return Integer.parseInt(buf.toString()) ;
    	}
    	catch (EOFException e)
    	{
    		if (buf.length() == 0)
    		{
    			throw e;
    		}
    		else
    		{
    			return Integer.parseInt(buf.toString());
    		}
    	}
    }

    /*
       Lecture d'un graphe value représenté par des arcs explicites.
       Format : nmax (sommet (sommet)* 0 )* 0
       Nombre max de sommets puis liste des sommets et leurs scuccesseurs.
    */
    public void lireArcs(InputStream in, Val delValSom, Val delValArc) throws Exception, IOException {
	// lecture de nmax et creation du graphe
	int nmax = lireEntier(in)+1;  // 0 n'est pas utilise comme identifiant de sommet
	recreer(nmax);
	// lecture des sommets
	int s = lireEntier(in);
	while (s != 0) {
	    Val v = delValSom.lire(in);
	    ajoutSom(s,v);
	    s = lireEntier(in);
	};
	// lecture des arcs
	int i = lireEntier(in);
	int j = lireEntier(in);
	while (! (i==0 && j==0)) {
	    Val w = delValArc.lire(in);
	    ajoutArc(i,j,w);
	    i = lireEntier(in);
	    j = lireEntier(in);
	};
    }

    /*
       Lecture d'un graphe valué représenté par un dictionnaire de successeurs.
       Format : nmax ( sommet valeur-sommet ( sommet valeur-arc )* 0 )* 0
       Chaque sommet est suivi de la liste de ses successeurs,
       avec pour chaque successeur son numéro.
    */
    public void lireSuccs(InputStream in, Val delValSom, Val delValArc)
    	throws Exception, IOException
    {
    	// lecture de nmax et creation du graphe
    	int nmax = lireEntier(in)+1;
    	recreer(nmax);
    	// lecture des sommets
    	int i = lireEntier(in) ;
    	while (i != 0)
    	{
    		Val v = delValSom.lire(in);
    		if (validSom(i))
    		{
    			// si le sommet a ete cree precedemment (pour la creation des arcs)
    			changeValSom(i,v);
    		}
    		else
    		{
    			ajoutSom(i,v);
    		}
    		// lecture des successeurs
    		int j = lireEntier(in);
    		while (j != 0)
    		{
    			Val w = delValArc.lire(in);
    			if (! validSom(j))
    			{
    				ajoutSom(j);
    			}
    			ajoutArc(i,j,w);
    			j = lireEntier(in);
    		} // iteration sur les successeurs
    		i = lireEntier(in);
    	} // iteration sur les sommets
    }

}
