#include "filtre_base.h"

/**
 * Initialise un filtre de base
 * @param nbEntrees : nombre d'entrées du filtre 
 * @param nbSorties : nombre de sorties du filtre
 */
filtre_base::filtre_base(unsigned int nbEntrees, unsigned int nbSorties) : producteur_base(nbSorties), consommateur_base(nbEntrees)
{}
