/**
   Classe Racine implementant l'interface en ligne de commande avec
   l'allocateur.
*/

import java.io.*;
import java.util.*;

public class Racine {

    private static Allocateur a; // une instance de votre allocateur

    private static int choix; // pour les selections de commandes dans les menus

    public static void main(String[] args) {
	try {
	    System.out.println("Création de l'allocateur");
	    System.out.print("Nombre maximum de processus ? ");
	    int nmaxProc = lireEntier();
	    System.out.print("Nombre de ressources ? ");
	    int nRess = lireEntier();
	    a = new Allocateur(nmaxProc, nRess);

	    menu();
	}
	catch (Exception e) {
	    e.printStackTrace();
	    System.exit(1);
	}
    }

    public static void menu() {
	afficherMenu();
	switch (choix) {
	case 0: cmdTerminer(); break;
	case 1: cmdCreer(); break;
	case 2: cmdDetruire(); break;
	case 3: cmdDemander(); break;
	case 4: cmdLiberer(); break;
	case 5: cmdAfficherFiles(); break;
	case 6: cmdAfficherActifs(); break;
	case 7: cmdAfficherAttentes(); break;
	case 8: cmdAfficherInterblocages(); break;
	default:
	    System.out.println("mauvais choix, recommencer");
	};
	if (choix != 0) {
	    menu();
	}
    }

    public static void afficherMenu() {
	System.out.println();
	System.out.println("Choisir une action : ");
	System.out.println("====================");
	System.out.println("  0 : sortir");
	System.out.println("  1 : création d'un processus");
	System.out.println("  2 : destruction d'un processus");
	System.out.println("  3 : demande de ressource(s) par un processus");
	System.out.println("  4 : libération d'une ressource par un processus");
	System.out.println("  5 : affichage des files d'attente par ressource");
	System.out.println("  6 : affichage des processus actifs");
	System.out.println("  7 : affichage des attentes entre processus");
	System.out.println("  8 : affichage des processus concernés par un interblocage");
	try {
	    choix = lireEntier();
	    //toNextLine() ;
	}
	catch (Exception e) {
	    choix = -1;
	}
    }

    private static void cmdTerminer() {
	try {
	    System.out.print("Confirmation (o/n) : ");
	    char c = (char) System.in.read();
	    if (c == 'o' || c == 'O') {
		choix = 0;
	    } else {
		choix = -1;
	    };
	    toNextLine();
	}
	catch (IOException e) {
	    choix = -1;
	}
    }

    private static void cmdCreer() {
	try {
	    System.out.print("Numéro du processus à créer : ");
	    int p = lireEntier();
	    a.creerProc(p);
	}
	catch (Exception e) {
	    System.out.println(e.getMessage());
	}
    }

    private static void cmdDetruire() {
	try {
	    System.out.print("Numéro du processus à détruire : ");
	    int p = lireEntier();
	    a.detruireProc(p);
	}
	catch (Exception e) {
	    System.out.println(e.getMessage());
	}
    }

    private static void cmdDemander() {
	Integer r;
	try {
	    System.out.print("Numéro du processus demandeur : ");
	    int p = lireEntier();
	    System.out.println("Liste des ressources demandées (séparées par des blancs et terminée par une ligne vide) : ");
	    Set lr = new TreeSet();
	    try {
		while (true) {
		    r = new Integer(lireEntier());
		    lr.add(r);
		}
	    }
	    catch (Exception e) {};
	    a.demanderRess(p,lr);
	}
	catch (Exception e) {
	    System.out.println(e.getMessage());
	}
    }

    private static void cmdLiberer() {
	try {
	    System.out.print("Numéro du processus libérateur : ");
	    int p = lireEntier();
	    System.out.print("Numéro de la ressource libérée : ");
	    int r = lireEntier();
	    a.libererRess(p,r);
	}
	catch (Exception e) {
	    System.out.println(e.getMessage());
	}
    }

    private static void cmdAfficherFiles() {
	System.out.println("Files d'attentes par ressource : ");
	a.afficherFiles();
	System.out.println();
    }

    private static void cmdAfficherActifs() {
	System.out.println("Processus actifs : ");
	a.afficherActifs();
	System.out.println();
    }

    private static void cmdAfficherAttentes() {
	System.out.println("Attentes entre processus : ");
	a.afficherAttentes();
	System.out.println();
    }

    private static void cmdAfficherInterblocages() {
	System.out.println("Processus concernés par un interblocage : ");
	a.afficherInterblocages();
	System.out.println();
    }


    private static int lireEntier() throws IOException {
    	StringBuffer buf = new StringBuffer();
    	try
    	{
    	    char c = (char) System.in.read ();
    	    while (c == ' ' || c == '\t')
    	    {
    	    	c = (char) System.in.read();
    	    }
    	    while (c >= '0' && c <= '9')
    	    {
    	    	buf.append(c);
    	    	c = (char) System.in.read ();
    	    }
    	    return Integer.parseInt(buf.toString());
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

    private static void toNextLine() throws IOException {
	for (char c = (char) System.in.read(); c != '\n'; c = (char) System.in.read()) {}
    }

} // class
