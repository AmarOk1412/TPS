#include "ComparerNombrePassagers.h"

ComparerNombrePassagers::ComparerNombrePassagers(bool sensTri): Comparator(sensTri), ordre(sensTri)	
{}

ComparerNombrePassagers::~ComparerNombrePassagers()
{}

bool ComparerNombrePassagers::operator()(const Vehicule* v1, const Vehicule* v2) const
{
	return ordre?v1->getPassagers()<v2->getPassagers():v1->getPassagers()>=v2->getPassagers();
}
