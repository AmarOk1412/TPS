/**
 Objet encapsulant une chaîne de caractères , pouvant être rattaché à un sommet
 ou à un arc de graphe.
 */

import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;

public class ValChaine extends Val
{
	/**
	  Valeur enregistrée
 	*/
	private String valeurChaine ;
	
	/**
	 Constructeur enregistrant la chaîne vide.
   
   */
	public ValChaine ()
	{
		super () ;
		valeurChaine = "" ;
	}
	
	/**
	 Constructeur enregistrant la chaîne demandée.

   	@param i est la chaîne de caractères à enregistrer
   */
	public ValChaine (String chaine)
	{
		super () ;
		valeurChaine = chaine ;
	}
	
	public String valeur()
	{
		return valeurChaine ;
	}
	
	public String toString()
	{
		return valeurChaine ;
	}
	
    public Val lire(InputStream in) throws IOException
	{
    	StringBuffer buf = new StringBuffer();
    	try
    	{
    	    char c = (char) in.read ();
    	    while (c == ' ' || c == '\n' || c == '\t')
    	    {
    	    	c = (char) in.read();
    	    }
    	    boolean guillemetPresent = (c == '\"') ;
    	    if (guillemetPresent)
    	    {
    	    	c = (char) in.read();
    	    }
    	    boolean finChaine = false ;
    	    while (! finChaine)
    	    {
    	    	if (guillemetPresent && c == '\"')
    	    	{
    	    		c = (char) in.read();
    	    		finChaine = (c != '\"') ;
    	    	}
    	    	else
    	    	{
    	    		finChaine = !guillemetPresent && (c == ' ' || c == '\n' || c == '\t') ;
    	    	}
    	    	if (! finChaine)
    	    	{
    	    		buf.append(c);
    	    		c = (char) in.read ();
    	    	}
    	    };
    	    return new ValChaine (buf.toString());
    	}
    	catch (EOFException e)
    	{
    	    if (buf.length() == 0)
    	    {
    	    	throw e;
    	    }
    	    else
    	    {
    	    	return new ValChaine (buf.toString()) ;
    	    }
    	}
    }

    public void ecrire(PrintStream out) throws IOException
    {
    	out.print(this.toString()) ;
	}
    
}
