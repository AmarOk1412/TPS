
import java.awt.*;
import java.awt.event.*;
import java.sql.*;

/**
 * This is a skeleton for realizing a very simple database user interface in java. 
 * The interface is an Applet, and it implements the interface ActionListener. 
 * If the user performs an action (for example he presses a button), the procedure actionPerformed 
 * is called. Depending on his actions, one can implement the database connection (disconnection), 
 * querying or insert. 
 * 
 * @author zmiklos
 *
 */
public class TP6 extends java.applet.Applet implements ActionListener {

 private TextField mStat, mCours, mParcours, mSalle, mEnseignant, mEtudiant, mHoraireMin, mHoraireMax;
TextArea mRes;
 private Button b1, b2, bEnseignant, bEtudiant, bHoraireCours, bHoraireParcours, bSalle;
 private static final long serialVersionUID = 1L; 
 
 // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://mysql.istic.univ-rennes1.fr:3306/base_13002155";

   //  Database credentials
   static final String USER = "user_13002155";
   static final String PASS = "VousCroyezQu'onMetUnMotDePasseICI. LOL";  
   
		Connection conn = null;
		Statement stmt = null;
 
 
 /**
  * This procedure is called when the Applet is initialized.
  * 
  */
 public void init ()
 {    
	 /**
	  * Definition of text fields
	  */
     mStat = new TextField(150);
     mStat.setEditable(false);
     mRes = new TextArea(10,150);
     mRes.setEditable(false);
     mCours = new TextField(150);
     mParcours = new TextField(150);
     mSalle = new TextField(150);
     mEnseignant = new TextField(150);
     mEtudiant= new TextField(150);
     mHoraireMin = new TextField(150);
     mHoraireMax = new TextField(150);
    
     
     
     /**
      * First we define the buttons, then we add to the Applet, finally add and ActionListener 
      * (with a self-reference) to capture the user actions.  
      */
     b1 = new Button("CONNECT");
     b2 = new Button("DISCONNECT");
     bEnseignant = new Button("ENSEIGNANT");
     bEtudiant = new Button("ETUDIANT");
     bHoraireCours = new Button("HORAIRES COURS");
     bHoraireParcours = new Button("HORAIRES PARCOUR");
     bSalle = new Button("Salle");
     add(b1) ;
     add(b2) ;
     add(bEnseignant) ;
     add(bEtudiant) ;
     add(bHoraireCours);
     add(bHoraireParcours);
     add(bSalle);
     b1.addActionListener(this);
     b2.addActionListener(this);
     bEnseignant.addActionListener(this);
     bEtudiant.addActionListener(this);
     bHoraireCours.addActionListener(this);
     bHoraireParcours.addActionListener(this);
     bSalle.addActionListener(this);
     
     add(mStat);
     add(new Label("Cours: ", Label.LEFT));
     add(mCours);
     add(new Label("Parcours: ", Label.LEFT));
     add(mParcours);
     add(new Label("Salle: ", Label.LEFT));
     add(mSalle);
     add(new Label("Enseignant: ", Label.LEFT));
     add(mEnseignant);
     add(new Label("Etudiant: ", Label.LEFT));
     add(mEtudiant);
     add(new Label("Horaire min: ", Label.LEFT));
     add(mHoraireMin);
     add(new Label("Horaire max: ", Label.LEFT));
     add(mHoraireMax);
     add(new Label("Query results: ", Label.LEFT));
     add(mRes);
     
     setStatus("Waiting for user actions.");
 }
 
 
 /**
  * This procedure is called upon a user action.
  * 
  *  @param event The user event. 
  */
  public void actionPerformed(ActionEvent event)
 {
  
	 // Extract the relevant information from the action (i.e. which button is pressed?)
	 Object cause = event.getSource();

	 // Act depending on the user action
	 // Button CONNECT
     if (cause == b1)
     {
        connectToDatabase();
     }
     
     // Button DISCONNECT
     if (cause == b2)
     {
    	 disconnectFromDatabase();
     }
     
     if (cause == bEnseignant)
     {
    	 QueryEnseignant();
     }
     
     if (cause == bEtudiant)
     {
    	 QueryEtudiant();
     }
     
     if (cause == bHoraireCours)
     {
    	 QueryHoraireCours();
     }
     
     if (cause == bHoraireParcours)
     {
    	 QueryHoraireParcours();
     }

     if (cause == bSalle)
     {
    	 QuerySalle();
     }
 }
 

/**
 * Set the status text. 
 * 
 * @param text The text to set. 
 */
private void setStatus(String text){
	    mStat.setText("Status: " + text);
  }

/**
 * Procedure, where the database connection should be implemented. 
 */
private void connectToDatabase(){
	try{
		//STEP 2: Register JDBC driver
		Class.forName("com.mysql.jdbc.Driver");

		//STEP 3: Open a connection
		System.out.println("Connecting to database...");
		conn = DriverManager.getConnection(DB_URL,USER,PASS);
		if(conn != null)
			setStatus("Connected to the database");
	} catch(Exception e){
		System.err.println(e.getMessage());
		setStatus("Connection failed" + e.toString());
	}
}


/**
 * Procedure, where the database connection should be implemented. 
 */
private void disconnectFromDatabase(){
	try{
	setStatus("Disconnected from the database");
	} catch(Exception e){
        if(conn!=null)
			try {
				conn.close();
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
		System.err.println(e.getMessage());
		setStatus("Disconnection failed");
	}
}

/**
 * Search Enseignant in Enseigne 
 */
private void QueryEnseignant(){
	try{
		stmt = conn.createStatement();
	    String sql;
	    sql = "SELECT prenom, nom FROM Enseigne as E, Enseignant WHERE Enseignant.idEnseignant = E.Enseignant_idEnseignant";
	    if(!mCours.getText().isEmpty())
	    	sql += " AND Cours_idCours = " + mCours.getText();
	    System.out.println(sql);
	    ResultSet rs = stmt.executeQuery(sql);
	    
	    //STEP 5: Extract data from result set
	    while(rs.next()){
	       //Retrieve by column name
	       String prenom = rs.getString("prenom");
	       String nom = rs.getString("nom");
	
	       //Display values
	       mRes.append("Enseignant: " + nom + " " + prenom + "\n");
	    }
	    
	    stmt.close();
	    rs.close();
	} catch(Exception e){
			System.err.println(e.getMessage());
			setStatus("Requete ratée");
		}
	
}

/**
 * Horaire
 */
private void QueryEtudiant(){
	try{
		stmt = conn.createStatement();
	    String sql;
	    sql = "SELECT nom, prenom FROM estInscrit EI, Etudiant E WHERE  EI.idEtudiant = E.idEtudiant";
	    if(!mParcours.getText().isEmpty())
	    	sql += " And E.Parcours_idPar = " + mParcours.getText();
	    if(!mCours.getText().isEmpty())
	    	sql += " And EI.idCours = " + mCours.getText();
	    System.out.println(sql);
	    ResultSet rs = stmt.executeQuery(sql);
	    
	    //STEP 5: Extract data from result set
	    while(rs.next()){
	       //Retrieve by column name
	       String prenom = rs.getString("prenom");
	       String nom = rs.getString("nom");
	
	       //Display values
	       mRes.append("Etudiant: " + nom + " " + prenom + "\n");
	    }
	    
	    stmt.close();
	    rs.close();
	} catch(Exception e){
			System.err.println(e.getMessage());
			setStatus("Requete ratée");
		}
	
}


/**
 * Horaire
 */
private void QueryHoraireCours(){
	try{
		stmt = conn.createStatement();
	    String sql;
	    sql = "SELECT * FROM estDans WHERE";
	    System.out.println(sql);
	    if(!mCours.getText().isEmpty())
	    	sql += " Cours_idCours= " + mCours.getText();
	    else if(!mEnseignant.getText().isEmpty())
	    	sql += " Cours_idCours = (SELECT Cours_idCours FROM Enseigne WHERE Enseignant_idEnseignant = "+mEnseignant.getText()+")";
	    else if(!mEtudiant.getText().isEmpty())
	    	sql += " Cours_idCours = (SELECT idCours FROM estInscrit WHERE idEtudiant= "+mEtudiant.getText()+")";
	    else
	    	sql += " Salle_idSalle = " + mSalle.getText();
	    
	    if(!mHoraireMax.getText().isEmpty() && !mHoraireMin.getText().isEmpty())
	    	sql += "AND horaire > '"+mHoraireMin.getText()+"' AND horaire < '"+mHoraireMax.getText()+"'";
	    
	    System.out.println(sql);
	    ResultSet rs = stmt.executeQuery(sql);
	    
	    //STEP 5: Extract data from result set
	    while(rs.next()){
	       //Retrieve by column name
		   String cours = rs.getString("Cours_idCours");
		   String salle = rs.getString("Salle_idSalle");
	       String horaire = rs.getString("horaire");
	
	       //Display values
	       mRes.append("Horaire: " + cours + "-" + salle + "-" + horaire + "\n");
	    }
	    
	    stmt.close();
	    rs.close();
	} catch(Exception e){
			System.err.println(e.getMessage());
			setStatus("Requete ratée");
		}
	
}

/**
 * Horaire
 */
private void QueryHoraireParcours(){
	try{
		stmt = conn.createStatement();
	    String sql;
	    sql = "SELECT DISTINCT horaire FROM estDans eD, Cours C, estInscrit eI, Etudiant E WHERE eD.Cours_idCours=C.idCours AND C.idCours=eI.idCours AND eI.idEtudiant=E.idEtudiant AND E.Parcours_idPar=" + mParcours.getText();
	    System.out.println(sql);
	    ResultSet rs = stmt.executeQuery(sql);
	    
	    //STEP 5: Extract data from result set
	    while(rs.next()){
	       //Retrieve by column name
	       String horaire = rs.getString("horaire");
	
	       //Display values
	       mRes.append("Horaire: " + horaire + "\n");
	    }
	    
	    stmt.close();
	    rs.close();
	} catch(Exception e){
			System.err.println(e.getMessage());
			setStatus("Requete ratée");
		}
	
}

/**
 * Salle
 */
private void QuerySalle(){
	try{
		stmt = conn.createStatement();
	    String sql;
	    sql = "SELECT DISTINCT Salle_idSalle FROM estDans ";
	    if(!mHoraireMax.getText().isEmpty() && !mHoraireMin.getText().isEmpty())
	    	sql += "WHERE horaire > '"+mHoraireMin.getText()+"' AND horaire < '"+mHoraireMax.getText()+"'";
	    System.out.println(sql);
	    ResultSet rs = stmt.executeQuery(sql);
	    
	    //STEP 5: Extract data from result set
	    while(rs.next()){
	       //Retrieve by column name
	       String Salle = rs.getString("Salle_idSalle");
	
	       //Display values
	       mRes.append("Salle: " + Salle + "\n");
	    }
	    
	    stmt.close();
	    rs.close();
	} catch(Exception e){
			System.err.println(e.getMessage());
			setStatus("Requete ratée");
		}
	
}


}
