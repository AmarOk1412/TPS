#include "Comparator.h"

Comparator::Comparator(bool sensTri) : ordre(sensTri) { }

Comparator::~Comparator() { }

bool Comparator::operator()(const Vehicule* v1, const Vehicule* v2) const
{
	return ordre?v1<v2:v1>=v2;
}
