#include "impl_flot.h"
//constructeur
impl_flot::impl_flot() : flot(), _flot(new std::deque<double>())
{}
//destructeur
impl_flot::~impl_flot()
{}
/**
 * @brief	Insertion d'un echantillon dans le flot. 
 * @param	echantillon	L'echantillon a inserer dans le flot.
 */
void impl_flot::inserer(double echantillon)
{
	_flot->push_front(echantillon);
}
/**
 * @brief	Extraction de l'echantillon situe en tete du flot. 
 * @pre	!vide()
 * @return	L'echantillon en tete de flot. 
 */
double impl_flot::extraire()
{
	assert(!vide());
	double back = _flot->back();
	_flot->pop_front();
	return back;
}
/**
 * @brief	Permet de savoir si le flot est vide ou non. 
 * @return	Vrai si le flot est vide, faux sinon. 
 */
bool impl_flot::vide() const
{
	return _flot->empty();
}
