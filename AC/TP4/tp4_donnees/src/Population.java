import java.util.List;
import java.util.LinkedList;

public class Population<Indiv extends Individu> {
	
	// Liste contenant les différents individus d'une génération
	private List<Indiv> population;
	
	
	/**
	 * construit une population à partir d'un tableau d'individu
	 */
	public  Population(Indiv[] popu){
		population = new LinkedList<Indiv>();
		for(Indiv i : popu)
			population.add(i);
	}
	
	/**
	 * sélectionne un individu (sélection par roulette par exemple, cf TD)
	 * @param adapt_totale somme des adaptations de tous les individus (pour ne pas avoir à la recalculer)
	 * @return indice de l'individu sélectionné
	 */
	public int selection(double adapt_totale){
		//TODO
		return -1;
	}
	
	/**
	 * remplace la génération par la suivante
	 * (croisement + mutation)
	 * @param prob_mut probabilité de mutation
	 */
	@SuppressWarnings("unchecked")
	public void reproduction(double prob_mut) {
		
		/***** on construit la nouvelle génération ****/
		List<Indiv> new_generation = new LinkedList<Indiv>();
		
		/* élitisme */
		//TODO (dans un second temps)

		double adapt = 0;
		for(Indiv i : population)
			adapt += i.adaptation();
		// tant qu'on n'a pas le bon nombre 
		while (new_generation.size()<population.size()){
			// on sélectionne les parents
			Indiv p1 = population.get(selection(adapt));
			Indiv p2 = population.get(selection(adapt));
			
			// ils se reproduisent
			Individu[] enfants = p1.croisement(p2);
			
			// on les ajoute à la nouvelle génération
			for(int i = 0; i < enfants.length; ++i)
				new_generation.add((Indiv) enfants[i]);
		}
		
		// on applique une éventuelle mutation à toute la nouvelle génération
		for(Indiv i : new_generation)
			i.mutation(prob_mut);

		//on remplace l'ancienne par la nouvelle
		population = new_generation;
	}
	
	/**
	 * renvoie l'individu de la population ayant l'adaptation maximale
	 */	
	public Indiv individu_maximal(){
		Indiv max = null;
		double maxScore = 0;
		for(Indiv i : population)
			if(i.adaptation() > maxScore)
				max = i;
		return max;
	}

	/**
	 * renvoie l'adaptation moyenne de la population
	 */
	public double adaptation_moyenne(){
		double adapt = 0;
		for(Indiv i : population)
			adapt += i.adaptation();
		return adapt/population.size();
	}
	
	/**
	 * renvoie l'adaptation maximale de la population
	 */	
	public double adaptation_maximale(){
		return individu_maximal().adaptation();
	}
}
