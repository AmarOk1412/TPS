#include "afficher.h"
/*------------------------------------------------------------
	Les trois fonctions ...
  -----------------------------------------------------------*/
int plus (int x, int y) 
{ 
	afficher("Somme : ", x, y, x+y);
	return (x + y); 
}

int moins(int x, int y) 
{
	afficher("Soustraction : ", x, y, x-y); 
	return (x - y); 
}

int mult (int x, int y) 
{ 
	afficher("Multiplication : ", x, y, x*y); 
	return (x * y); 
}
