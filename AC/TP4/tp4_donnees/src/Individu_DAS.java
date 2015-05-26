import java.util.Random;

public interface Individu_SAD extends Individu {
	boolean[] _individu = null;
	double[] _weights = null;
	double _capacite = 0;
	
	public Individu_SAD(double[] weights, double capacite)
	{
		_weights = weights;
		_capacite = capacite;
		_individu = new double[weights.size()];
		Random random = new Random();
		for(int i = 0; i < weights.size(); ++i)
			_individu[i] = random.nextBoolean();
	}

	/**
	 * renvoie l'adaptation de cet individu
	 */
	public double adaptation();
	
	/**
	 * renvoie un tableau de 2 individus constituant les
	 * enfants de la reproduction entre this et conjoint
	 * @param conjoint à accoupler avec l'objet courant
	 * @return tableau des 2 enfants
	 */
	public Individu[] croisement(Individu conjoint)
	{
		Individu[] crois = new Individu[2];
		boolean[] res = new boolean[_individu.size()];
		boolean[] res2 = new boolean[_individu.size()];
		int index = 0;
		Random random = new Random();
		index = random.nextInt(_individu.size()-1);
		for(int i = 0; i < index; ++i)
		{
			res[i] = _individu[i];
			res2[i] = conjoint._individu[i];
		}	
		for(int i = index + 1; i < _individu.size(); ++i)
		{
			res[i] = conjoint._individu[i];
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
	public void mutation(double prob);
}
