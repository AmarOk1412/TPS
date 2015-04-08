
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
public class DatabaseUserInterface extends java.applet.Applet implements ActionListener {

 private TextField mStat, m1, m2, m3;
TextArea mRes;
 private Button b1, b2, b3, b4;
 private static final long serialVersionUID = 1L; 
 
 // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://mysql.istic.univ-rennes1.fr:3306/base_13002155";

   //  Database credentials
   static final String USER = "user_13002155";
   static final String PASS = "55espece99";  
   
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
     //m1 = new TextField(80);
     //m1.setText("What are you going to do when the light is:");
     //m1.setEditable(false);
     mStat = new TextField(150);
     mStat.setEditable(false);
     m1 = new TextField(150);
     m2 = new TextField(150);
     m3 = new TextField(150);
     mRes = new TextArea(10,150);
     mRes.setEditable(false);
    
     
     
     /**
      * First we define the buttons, then we add to the Applet, finally add and ActionListener 
      * (with a self-reference) to capture the user actions.  
      */
     b1 = new Button("CONNECT");
     b2 = new Button("DISCONNECT");
     b3 = new Button("QUERY");
     b4 = new Button("INSERT");
     add(b1) ;
     add(b2) ;
     add(b3) ;
     add(b4);
     b1.addActionListener(this);
     b2.addActionListener(this);
     b3.addActionListener(this);
     b4.addActionListener(this);
     
     add(mStat);
     add(new Label("Input fields: ", Label.CENTER));
     add(m1);
     add(m2);
     add(m3);
     m1.setText("Name (e.g. John Smith) - Please enter here!");  //According to the database schema
     m2.setText("Age (e.g. 23)  - Please enter here!"); //According to the database schema
     m3.setText("Color of the eye (e.g. green) - Please enter here!");  //According to the database schema
     add(new Label("Query results: ", Label.CENTER));
     add(mRes);
     mRes.setText("Query results");
     
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
     
     //Button QUERY
     if (cause == b3)
     {
    	 queryDatabase();
     }
     
     //Button INSERT
     if (cause == b4)
     {
         insertDatabase();
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
 * Execute a query and display the results. Implement the database querying and the 
 * display of the results here 
 */
private void queryDatabase(){
	System.out.println("Creating statement...");
    try {
		stmt = conn.createStatement();
	    String sql;
	    sql = "SELECT * FROM TP5";
	    ResultSet rs = stmt.executeQuery(sql);
	    

		mRes.setText("The query result is presented here.\n");
	    //STEP 5: Extract data from result set
	    while(rs.next()){
	       //Retrieve by column name
	       String nom = rs.getString("Nom");
	       String age = rs.getString("Age");
	       String color = rs.getString("Color");
	
	       //Display values
	       mRes.append("Nom: " + nom);
	       mRes.append(", Age: " + age);
	       mRes.append(", Color: " + color + "\n");
	    }
	    
	    stmt.close();
	    rs.close();
	} catch (SQLException e) {
		e.printStackTrace();
	}
}

/**
 * Insert tuples to the database. 
 */
private void insertDatabase(){
	try{
		System.out.println("Creating statement...");
	    stmt = conn.createStatement();
	    String sql;
		String name = m1.getText();
		String age = m2.getText();
		String color = m3.getText();
	    sql = "INSERT INTO TP5 VALUES( '" + name + "', '" + age + "', '" + color + "' );";
	    stmt.executeUpdate(sql);
		setStatus("Inserting --( " + name + ", " + age + ", " + color + " )-- to the database");
		stmt.close();
	} catch(Exception e){
			System.err.println(e.getMessage());
			setStatus("Insertion failed");
		}
	
}


}
