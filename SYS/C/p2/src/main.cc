#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pluginmanager.h"

int loadDir(plugin_manager* pm)
{
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
		printf("Dossier choisi : ");
		printf(word);
		printf("\n");
		
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
		else if(number >= nbFunction)
			printf("Pas de fonction à cet indice !\n");
	}

	release_manager(pm);

  return 0;
}
