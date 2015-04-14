public class Permutations {
	public static void permutation(String target, String original,boolean afficher){
	    int i;
	    String target1, original1;
	    if (original.length() == 0 && afficher){
	        //System.out.println(target);
	    }
		else {
			i = 0;
			while (i < original.length()){
			    target1 = target + original.substring(i,i+1);
			    original1 = original.substring(0,i) + original.substring(i+1,original.length());
			    permutation(target1,original1,afficher);
			    i = i + 1;
			}
		} 
	}
	public static void main(String[] args) {
		String x="";
		String alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int n=10;
		
		long date1 = System.currentTimeMillis(); //on lance le chrono
			
		String y=alphabet.substring(0, n);
		permutation(x,y,true);
			long date2 = System.currentTimeMillis(); //on arrete le chrono
			System.out.println("Croissant : Temps de calcul pour n="+n+" : ");
			System.out.println(date2 - date1);
	}

}
