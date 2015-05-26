import java.util.Random;

public class Individu_SAD implements Individu {
	boolean[] _individu = null;
	double[] _weights = null;
	double _capacite = 0;
	
	public Individu_SAD(double[] weights, double capacite)
	{
		_weights = weights;
		_capacite = capacite;
		_individu = new boolean[weights.length];
		Random random = new Random();
		for(int i = 0; i < weights.length; ++i)
			_individu[i] = random.nextBoolean();
	}

	/**
	 * renvoie l'adaptation de cet individu
	 */
	public double adaptation()
	{
		double adapt = 0;
		for(int i = 0; i < _individu.length; ++i)
			if(_individu[i])
				adapt += _weights[i];
		if(adapt > _capacite)
			return 0;
		return adapt;
	}
	
	public boolean[] getIndividu()
	{
		return _individu;
	}
	
	/**
	 * renvoie un tableau de 2 individus constituant les
	 * enfants de la reproduction entre this et conjoint
	 * @param conjoint à accoupler avec l'objet courant
	 * @return tableau des 2 enfants
	 */
	public Individu[] croisement(Individu conjoint)
	{
		Individu_SAD[] crois = new Individu_SAD[2];
		boolean[] res = new boolean[_individu.length];
		boolean[] res2 = new boolean[_individu.length];
		int index = 0;
		Random random = new Random();
		index = random.nextInt(_individu.length-1);
		for(int i = 0; i < index; ++i)
		{
			res[i] = _individu[i];
			res2[i] = ((Individu_SAD)conjoint)._individu[i];
		}	
		for(int i = index + 1; i < _individu.length; ++i)
		{
			res[i] = ((Individu_SAD)conjoint)._individu[i];
			res2[i] = this._individu[i];
		}
		crois[0] = new Individu_SAD(_weights, _capacite);
		crois[1] = new Individu_SAD(_weights, _capacite);
		crois[0]._individu = res;
		crois[1]._individu = res2;
		return crois;
	}
	
	/**
	 * applique l'opérateur de mutation
	 * associé à la probabilité prob
	 */
	public void mutation(double prob)
	{
		for(int i = 0; i < _individu.length; ++i)
			if(Math.random() < prob)
				_individu[i] = !_individu[i];
	}
}
