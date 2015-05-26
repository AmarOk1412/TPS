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
	public Individu[] croisement(Individu conjoint);
	
	/**
	 * applique l'opérateur de mutation
	 * associé à la probabilité prob
	 */
	public void mutation(double prob);
}
