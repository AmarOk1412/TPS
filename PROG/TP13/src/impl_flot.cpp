#include "impl_flot.h"
#include <iostream>

impl_flot::impl_flot() : flot(), _flot(new std::deque<double>())
{}

impl_flot::~impl_flot()
{}

void impl_flot::inserer(double echantillon)
{
	_flot->push_front(echantillon);
}

double impl_flot::extraire()
{
	assert(!vide());
	double back = _flot->back();
	_flot->pop_front();
	return back;
}

bool impl_flot::vide() const
{
	return _flot->empty();
}
