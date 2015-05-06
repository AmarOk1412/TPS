/**
 Objet encapsulant une valeur, pouvant être rattaché à un sommet ou à un arc de graphe.
 */
import java.io.*;

public class Val
{
    /**
       Constructeur par defaut.
    */
    public Val() {}

    /**
       Lecture d'une valeur sur une entree.
       L'objet appelant peut etre un objet quelconque de la classe (delegue).
       
       @param in est l'entree sur laquelle il faut lire
    */
    public Val lire(InputStream in) throws IOException
    {
    	return new Val();
    }

    /**
       Ecriture d'une valeur sur une sortie

       @param out est la sortie sur laquelle il faut ecrire
    */
    public void ecrire(PrintStream out) throws IOException {}
    
}
