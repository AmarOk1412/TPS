/**
   Interface des graphes dont les sommets et les arcs peuvent etre values.
*/

import java.util.*;
import java.io.*;

public interface Graphe {

    /**
       Reinitialisation du graphe, avec une taille eventuellement differente.

       @param nmax est le nombre maximum de sommets
    */
    public void recreer(int nmax);

    /**
       Reinitialisation du graphe appelant en une copie profonde
       du graphe en argument. Permet des traductions d'une representation
       a une autre et des copies dans le cas d'algorithmes consommant
       les graphes. La copie profonde ne s'applique pas aux valeurs des
       sommets et des arcs qui sont supposes non modifiables.

       @param src est le graphe source a copier
    */
    public void copie(Graphe src) throws Exception;

    /**
       Nombre maximum de sommets (numerotes de 0 a n-1).

       @return le nombre maximum de sommets pour ce graphe
    */
    public int nmax();

    /**
       Toutes les methodes ci-dessous renvoie une exception si
       un identifiant de sommet est en dehors des bornes [0,nmax-1].
    */

    // operations sur les sommets

    /**
       Ajoute un sommet au graphe (sans valeur associee).

       @param i est l'identifiant du sommet
       @throws Exception si l'identifiant est deja valide
    */
    public void ajoutSom(int i) throws Exception;

    /**
       Ajoute un sommet au graphe avec une valeur associee.

       @param i est l'identifiant du sommet
       @param v est la valeur associee au sommet
       @throws Exception si l'identifiant est deja valide
    */
    public void ajoutSom(int i, Val v) throws Exception; 
    
    /**
       Verifie qu'un entier est bien un identifiant de sommet.

       @param i est entier
       @return vrai si <code>i</code> est un identifiant de sommet
    */
    public boolean validSom(int i) throws Exception;

    /**
       Retourne la valeur associee a un sommet.

       @param i est un identifiant de sommet
       @return la valeur associee au sommet <code>i</code> (potentiellement <code>null</code>)
       @throws Exception si l'identifiant est invalide
    */
    public Val valSom(int i) throws Exception;

    /**
       Change la valeur associee au sommet i.

       @param i est un identifiant de sommet
       @param v est une valeur
       @throws Exception si l'identifiant est invalide
    */
    public void changeValSom(int i, Val v) throws Exception;

    /**
       Ote un sommet du graphe, ainsi que les arcs adjacents.

       @param i est un identifiant de sommet
       @throws Exception si l'identifiant est invalide
    */
    public void oterSom(int i) throws Exception;


    // operations sur les arcs (values)

    /**
       Ajoute un arc entre deux sommets (sans valeur associee).
       Si l'arc est deja valide, sa valeur est ecrasee.

       @param i est un identifiant de sommet
       @param j est un identifiant de sommet
       @throws Exception si l'un des identifiants est invalide
    */
    public void ajoutArc(int i, int j) throws Exception;

    /**
       Ajoute un arc entre deux sommets avec une valeur associee.
       Si l'arc est deja valide, sa valeur est remplacee.

       @param i est un identifiant de sommet
       @param j est un identifiant de sommet
       @param w est une valeur associee a l'arc
       @throws Exception si l'un des identifiants est invalide
    */
    public void ajoutArc(int i, int j, Val w) throws Exception;

    /**
       Verifie l'existence d'un arc entre deux sommets.

       @param i est un identifiant de sommet
       @param j est un identifiant de sommet
       @return vrai si il existe un arc entre les sommets <code>i</code> et <code>j</code>
       @throws Exception si l'un des identifiants est invalide
    */
    public boolean validArc(int i, int j) throws Exception;

    /**
       Retourne la valeur associee a un arc si elle existe, <code>null</code> sinon.

       @param i est un identifiant de sommet
       @param j est un identifiant de sommet
       @return la valeur associee a l'arc entre <code>i</code> et <code>j</code> s'il existe, <code>null</code> sinon
       @throws Exception si l'un des identifiants ou l'arc est invalide
    */
    public Val valArc(int i, int j) throws Exception;

    /**
       Change la valeur associee a un arc.
       Si l'arc n'existe pas, il est cree.

       @param i est un identifiant de sommet
       @param j est un identifiant de sommet
       @param w est une valeur
       @throws Exception si l'un des identifiants est invalide
    */
    public void changeValArc(int i, int j, Val w) throws Exception;

    /**
       Ote un arc du graphe.
       Sans effet si l'arc n'est pas valide.

       @param i est un identifiant de sommet
       @param j est un identifiant de sommet
       @throws Exception si l'un des identifiants est invalide
    */
    public void oterArc(int i, int j) throws Exception;


    // access au graphe

    /**
       Retourne le nombre de sommets du graphe.

       @return le nombre de sommets du graphe
    */
    public int nbSom();

    /**
       Retourne le nombre d'arcs du graphe.

       @return le nombre d'arcs du graphe
    */
    public int nbArc();

    /**
       Teste si le graphe est vide.

       @return vrai si le graphe est vide
    */
    public boolean vide();

    /**
       Retourne l'ensemble des sommets.

       @return l'ensemble des identifiants des sommets
    */
    public Set ensSom();

    /**
       Retourne l'ensemble des predecesseurs d'un sommet.

       @param j est un identifiant de sommets
       @return l'ensemble des identifiants des sommets predecesseurs de <code>j</code>
       @throws Exception si l'identifiant est invalide
    */
    public Set ensPred(int j) throws Exception;

    /**
       Retourne l'ensemble des successeurs d'un sommet.

       @param i est un identifiant de sommets
       @return l'ensemble des identifiants des sommets successeurs de <code>i</code>
       @throws Exception si l'identifiant est invalide
    */
    public Set ensSucc(int i) throws Exception;

    /**
       Retourne l'ensemble des points d'entree du graphe.

       @return l'ensemble des identifiants des sommets qui sont points d'entree du graphe
    */
    public Set ensPtsEntree();

    /**
       Retourne l'ensemble des points de sortie du graphe.

       @return l'ensemble des identifiants des sommets qui sont points de sortie du graphe
    */
    public Set ensPtsSortie();

    /**
       Ote du graphe un ensemble de sommets, ainsi que les arcs adjacents.

       @param ens est un ensemble d'identifiants de sommets du graphe
       @throws Exception si un des identifiants est invalide
    */
    public void oterEnsSom(Set ens) throws Exception;

    /**
       Retourne un iterateur sur l'ensemble des sommets du graphe.
       
       @return un iterateur sur l'ensemble des identifiants des sommets du graphe
    */
    public Iterator iterSom();


    // entree/sortie


    /**
       Lecture d'un graphe value représenté par des arcs explicites.
       Les sommets et arcs du graphe appelant sont ecrases.
       Format : nmax ( sommet valeur-sommet )* 0 ( sommet sommet valeur-arc)* 0 0
       Nombre max de sommets puis liste des sommets (avec valeur) puis liste des arcs (avec valeur).

       @param in est la flot d'entree
       @param delValSom est un delegue de la classe des valeurs de sommet
       @param delValArc est un delegue de la classe des valeurs des arcs
       @throws IOException si il y a une erreur au cours de la lecture
       @throws Exception si il y a une erreur au cours de la construction du graphe
    */
    public void lireArcs(InputStream in, Val delValSom, Val delValArc) throws Exception, IOException;

    /**
       Lecture d'un graphe valué représenté par un dictionnaire de successeurs.
       Les sommets et arcs du graphe appelant sont ecrases.
       Format : nmax ( sommet valeur-sommet ( sommet valeur-arc )* 0 )* 0
       Chaque sommet est suivi de la liste de ses successeurs,
       avec pour chaque successeur son numéro.

       @param in est la flot d'entree
       @param delValSom est un delegue de la classe des valeurs de sommet
       @param delValArc est un delegue de la classe des valeurs des arcs
       @throws IOException si il y a une erreur au cours de la lecture
       @throws Exception si il y a une erreur au cours de la construction du graphe
    */
    public void lireSuccs(InputStream in, Val delValSom, Val delValArc) throws Exception, IOException;

    /**
       Ecriture d'un graphe valué représenté par des arcs explicites.
       Format : nmax ( sommet valeur-sommet )* 0 ( sommet sommet valeur-arc)* 0 0
       Nombre max de sommets puis liste des sommets (avec valeur) puis liste des arcs (avec valeur).

       @param out est la flot de sortie
       @throws IOException si il y a une erreur au cours de l'ecriture
       @throws Exception si il y a une erreur au cours des acces au graphe
    */
    public void ecrireArcs(PrintStream out) throws Exception, IOException;

    /**
       Ecriture d'un graphe valué représenté par un dictionnaire de successeurs.
       Format : nmax ( sommet valeur-sommet ( sommet valeur-arc )* 0 )* 0
       Chaque sommet est suivi de la liste de ses successeurs,
       avec pour chaque successeur son numéro.

       @param out est la flot de sortie
       @throws IOException si il y a une erreur au cours de l'ecriture
       @throws Exception si il y a une erreur au cours des acces au graphe
    */
    public void ecrireSuccs(PrintStream out) throws Exception, IOException;
}

