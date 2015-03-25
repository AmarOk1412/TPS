#include <stdio.h>

// Tcalc est le type d'une fonction à deux paramètres int qui rend un int
typedef
int (* Tcalc) (int, int);

/*-----		PROTOTYPES	-----*/
int  plus	(int, int);
int  moins	(int, int);
int  mult	(int, int);
// le 2ème paramètre de afficher 
// est une fonction à deux paramètres int qui rend un int
void afficher	(char [], Tcalc, int, int);

/*------------------------------------------------------------
	Programme principal
  -----------------------------------------------------------*/
int main(int argc, char * argv[])
{
    int             a, b;

    printf("Donner deux nombres entiers: ");
    scanf("%d%d", &a, &b);

    afficher("Somme     ", plus,  a, b);
    afficher("Difference", moins, a, b);
    afficher("Produit   ", mult,  a, b);
    return 0;
}

/*------------------------------------------------------------
	Afficher le résultat
  -----------------------------------------------------------*/
void afficher(char txt[], Tcalc calculer, int x, int y)
{
    printf("%-10s de %2d et %2d : %4d\n", txt, x, y, calculer(x, y));
}

/*------------------------------------------------------------
	Les trois fonctions ...
  -----------------------------------------------------------*/
int plus (int x, int y) { return (x + y); }
int moins(int x, int y) { return (x - y); }
int mult (int x, int y) { return (x * y); }

/*
    Donnez deux nombres entiers: 4 7
    Somme      de 4 et 7 : 11
    Difference de 4 et 7 : -3
    Produit    de 4 et 7 : 28
*/
