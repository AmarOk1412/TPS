public class Individu_VDC implements Individu {

	//Constructeur
	public Individu_VDC(double[] coord_x, double[] coord_y) {
		// TODO 
	}

	/* Classes de l'interface Individu
	 */
	@Override
	public double adaptation() {
		// TODO 
		return 0;
	}
	@Override
	public Individu[] croisement(Individu conjoint) {
		// TODO 
		return null;
	}
	@Override
	public void mutation(double prob) {
		// TODO 
		
	}
	
	/* Accesseurs (pour Display_VDC)
	 */
	public int[] get_parcours(){
		return null;
	}
	public double[] get_coord_x(){
		return null;
	}
	
	public double[] get_coord_y(){
		return null;
	}	
}
