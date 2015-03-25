// Charger la bibliothèque mathématique (libm.so)
// et calculer racine carrée de 2

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "afficher.h"

// Tcalc est le type d'une fonction à deux paramètres int qui rend un int
typedef
int (* Tcalc) (int, int);
/*------------------------------------------------------------
	Afficher le résultat Version 1
  -----------------------------------------------------------*/
/*void afficher(char txt[], Tcalc calculer, int x, int y)*/
/*{*/
/*    printf("%-10s de %2d et %2d : %4d\n", txt, x, y, calculer(x, y));*/
/*}*/

/*------------------------------------------------------------
	Afficher le résultat Version 2
  -----------------------------------------------------------*/
void afficher(char txt[], int x, int y, int z)
{
    printf("%-10s de %2d et %2d : %4d\n", txt, x, y, z);
}

int
main(int argc, char * argv[])
{
  // ouverture de la bibliothèque de calcul
  void * handle = dlopen("libcalcul2.so", RTLD_LAZY);
  if (handle == NULL) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  dlerror();    /* Clear any existing error */
  
  //Entrée de 2 nombres
  int             a, b;

  printf("Donner deux nombres entiers: ");
  scanf("%d%d", &a, &b);

  printf("Fonctions disponibles : \n\
  plus\n\
  moins\n\
  mult\n");
  
  //Fonction choisie
  printf("Choisissez une fonction: ");
  char *word;
  char buf[100]; /*buffer*/
  scanf("%s", buf); /*read string in buffer*/
  word = (char*) malloc(strlen(buf) + 1);
  if (word == NULL) {
    printf("Error: out of memory ...\n");
    exit(1);
  }
  strcpy(word, buf); 
  // chercher la fonction sqrt dans la bibliothèque
  Tcalc root =  dlsym(handle, word);

  char * error = dlerror();
  if ((error) != NULL)  {
    // erreur : fonction non trouvée
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }
  
/*  afficher("Résultat de la fonction : ", root,  a, b);*/
	root(a,b);
  
  free(word);
  dlclose(handle);
  exit(EXIT_SUCCESS);
}
