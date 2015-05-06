/**
 Objet encapsulant un entier, pouvant être rattaché à un sommet ou à un arc de graphe.
*/

import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;

public class ValEnt extends Val
{
	/**
	  Valeur enregistrée
	*/
	private int valeurEnt ;
	
	/**
	 Constructeur enregistrant la valeur zéro.
    
    */
	public ValEnt ()
	{
		super () ;
		valeurEnt = 0 ;
	}
	
	/**
	 Constructeur enregistrant la valeur entière demandée.

    	@param i est la valeure entière à enregistrer
    */
	public ValEnt (int i)
	{
		super () ;
		valeurEnt = i ;
	}
	
/**
    Valeur entière stockée
*/
	public int valeur()
	{
		return valeurEnt ;
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
    	    while (c >= '0' && c <= '9')
    	    {
    	    	buf.append(c);
    	    	c = (char) in.read ();
    	    }
    	    return new ValEnt (Integer.parseInt(buf.toString()));
    	}
    	catch (EOFException e)
    	{
    	    if (buf.length() == 0)
    	    {
    	    	throw e;
    	    }
    	    else
    	    {
    	    	return new ValEnt (Integer.parseInt(buf.toString()));
    	    }
    	}
    }

    public void ecrire(PrintStream out) throws IOException
    {
    	out.print(this.toString()) ;
	}
    
    public String toString()
    {
    	return new Integer(valeurEnt).toString() ;
    }

}
