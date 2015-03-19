// Charger la bibliothèque mathématique (libm.so)
// et calculer racine carrée de 2

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef
double (* RealFunction)(double);

int
main(int argc, char * argv[])
{
  // ouverture de la bibliothèque mathématique
  void * handle = dlopen("libm.so", RTLD_LAZY);
  if (handle == NULL) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  dlerror();    /* Clear any existing error */
  
  // tout est correct
  printf("Fonction de la bibliothèque mathématique : ");
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
  RealFunction root =  dlsym(handle, word);

  char * error = dlerror();
  if ((error) != NULL)  {
    // erreur : fonction non trouvée
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }
  
  printf("Saisir un nombre réel >= 0 : ");
  double x;
  scanf("%lf", &x);
  
  printf("%lf = %lf\n", x, root(x));
  free(word);
  dlclose(handle);
  exit(EXIT_SUCCESS);
}
