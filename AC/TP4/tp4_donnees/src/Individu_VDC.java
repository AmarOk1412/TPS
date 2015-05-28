import java.util.Random;

public class Individu_VDC implements Individu {

	private double[] _x;
	private double[] _y;
	private int[] _ind;

	//Constructeur
	public Individu_VDC(double[] coord_x, double[] coord_y) {
		_x = coord_x;
		_y = coord_y;
		_ind = new int[_x.length];
		for(int i = 0; i < _ind.length; ++i)
		{
			_ind[i] = i;
		}
		shuffleArray(_ind);
		System.out.println(_ind);
	}

  // Implementing Fisher–Yates shuffle
  static void shuffleArray(int[] ar)
  {
    Random rnd = new Random();
    for (int i = ar.length - 1; i > 0; i--)
    {
      int index = rnd.nextInt(i + 1);
      // Simple swap
      int a = ar[index];
      ar[index] = ar[i];
      ar[i] = a;
    }
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
		Individu[] res = new Individu[];
		int index = 0;
		Random random = new Random();
		index = random.nextInt(_ind.length-1);
		for(int i=0; i<=index; ++i)
		{
			res[i]=_ind[i];
		}
		++index;		
		for(int i=0; i<_ind.length; ++i)
		{
			if(!Arrays.asList(res).contains(conjoint._ind[i])
			{
				res[index]=conjoint._ind[i];
				++index;
			}
		}
		return res;
	}
	@Override
	public void mutation(double prob) {
		for(int i = 0; i < _ind.length; ++i)
			if(Math.random() < prob)
			{
				int r = Math.random()*_ind.length;
				int temp = _ind[r];
				_ind[r] = _ind[i];
				_ind[i] = temp;
			}
	}
	
	/* Accesseurs (pour Display_VDC)
	 */
	public int[] get_parcours(){
		return _ind;
	}
	public double[] get_coord_x(){
		return _x;
	}
	
	public double[] get_coord_y(){
		return _y;
	}	
}
