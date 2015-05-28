import java.util.Random;
import java.util.Arrays;
import java.util.List;

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
		double adapt = 0;
		for(int i = 1; i < _ind.length; ++i)
			adapt += Math.abs(Math.sqrt(Math.pow(_x[i-1]-_x[i],2)+Math.pow(_y[i-1]-_y[i],2)));
		return 1/adapt;
	}

	@Override
	public Individu[] croisement(Individu conjoint) {
		Individu[] res = new Individu[1];
		Individu_VDC ind = new Individu_VDC(_x,_y);
		int index = 0;
		Random random = new Random();
		index = random.nextInt(_ind.length-1);
		for(int i=0; i<=index; ++i)
			((Individu_VDC)ind)._ind[i] =_ind[i];
		++index;		
		for(int i=0; i<_ind.length; ++i)
		{
			if(!Arrays.asList(res).contains(((Individu_VDC)conjoint)._ind[i]))
			{
				((Individu_VDC)ind)._ind[index]=((Individu_VDC)conjoint)._ind[i];
				++index;
			}
		}
		res[0] = ind;
		return res;
	}
	@Override
	public void mutation(double prob) {
		for(int i = 0; i < _ind.length; ++i)
			if(Math.random() < prob)
			{
				int r = (int)(Math.random()*((double)_ind.length));
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
