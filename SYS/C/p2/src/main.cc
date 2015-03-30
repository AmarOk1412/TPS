#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pluginmanager.h"

// Recherche le nombre de plugins présents dans un répertoire donné
int loadDir(plugin_manager* pm)
{
		//Entrer un nom de répertoire
		printf("Choisissez un dossier: ");
		char *word;
		char buf[100]; /*buffer*/
		scanf("%s", buf); /*read string in buffer*/
		word = (char*) malloc(strlen(buf) + 1);
		if (word == NULL) {
		  printf("Error: out of memory ...\n");
		  exit(1);
		}
		strcpy(word, buf); 
		
		//Affiche le nom du répertoire choisi
		printf("Dossier choisi : ");
		printf(word);
		printf("\n");
		
		//Cherche le nombre de plugins présents dans le répertoire
		int nbPlugin = discover_plugins(word, pm);
		if(nbPlugin == 0)
			printf("Pas de plugins\n");
		return nbPlugin;
}

int main(int nbarg, char* args[])	
{
	cv::Mat img;
	plugin_manager* pm = make_manager();
	int nbFunction = 0;
	
	for (int nArg=0; nArg < nbarg; nArg++)
	{
		printf("Dossier choisi : ");
		printf(args[nArg]);
		printf("\n");
		
		int nbPlugin = discover_plugins(args[nArg], pm);
		if(nbPlugin == 0)
			printf("Pas de plugins\n");
		else
			nbFunction += nbPlugin;
	}
  int  number = -1;
  while(number != -3)
  {
  	if(number == -2)
  	{
  		nbFunction += loadDir(pm);
  		number = -1;
  	}
  	if(number == -1)
			display_menu(pm);
		printf("Choisissez une fonction : \n");
		scanf("%d", &number);
		if(number > -1 && number < nbFunction)
		{
			filter_function f = get_plugin(pm, number)->m_filtre;
			if(f != NULL)
				img = f(img);
		}
		else if(number >= nbFunction || number < -3)
			printf("Pas de fonction à cet indice !\n");
	}

	release_manager(pm);

  return 0;
}
