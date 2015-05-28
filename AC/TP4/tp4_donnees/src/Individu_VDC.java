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
			_ind[i] = i;
		shuffleArray(_ind);
	}

	public static void shuffleArray(int[] a) {
    int n = a.length;
    Random random = new Random();
    random.nextInt();
    for (int i = 0; i < n; i++) {
      int change = i + random.nextInt(n - i);
      swap(a, i, change);
    }
  }

  private static void swap(int[] a, int i, int change) {
    int helper = a[i];
    a[i] = a[change];
    a[change] = helper;
  }


	/* Classes de l'interface Individu
	 */
	@Override
	public double adaptation() {
		double adapt = 0;
		for(int i = 1; i < _ind.length; ++i)
			adapt += Math.abs(Math.sqrt(Math.pow(_x[_ind[i-1]]-_x[_ind[i]],2)+Math.pow(_y[_ind[i-1]]-_y[_ind[i]],2)));
		return 1/adapt;
	}

	@Override
	public Individu[] croisement(Individu conjoint) {
		Individu[] res = new Individu[1];
		Individu_VDC ind = new Individu_VDC(_x,_y);
		int index = 0;
		Random random = new Random();
		index = random.nextInt(_ind.length-1);
		//On copie la première partie du parent 1
		for(int i=0; i<_ind.length; ++i)
			ind._ind[i] = -1;
		for(int i=0; i<=index; ++i)
			ind._ind[i] =_ind[i];
		++index;
		for(int i=0; i<_ind.length; ++i)
		{
			boolean p = false;
			for(int t : ind._ind)
				if(t == ((Individu_VDC)conjoint)._ind[i])
					p = true;
			if(!p)
			{
				ind._ind[index]=((Individu_VDC)conjoint)._ind[i];
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
