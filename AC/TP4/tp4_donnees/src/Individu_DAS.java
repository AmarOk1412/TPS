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
	public double adaptation()
	{
		double adapt = 0;
		for(int i = 0; i < _individu.size(); ++i)
			if(_individu[i])
				adapt += _weights[i];
		if(adapt > _capacite)
			return 0;
		return adapt;
	}
	
	/**
	 * renvoie un tableau de 2 individus constituant les
	 * enfants de la reproduction entre this et conjoint
	 * @param conjoint à accoupler avec l'objet courant
	 * @return tableau des 2 enfants
	 */
	public Individu[] croisement(Individu conjoint);
	
	/**
	 * applique l'opérateur de mutation
	 * associé à la probabilité prob
	 */
	public void mutation(double prob)
	{
		for(int i = 0; i < _individu.size(); ++i)
			if(Math.random() < prob)
				_individu[i] = !_individu[i];
	}
}
