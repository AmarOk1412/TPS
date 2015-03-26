#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pluginmanager.h"

int main(int nbarg, char* args[])	
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
    
    plugin_manager* pm = make_manager();
    unsigned int nbPlugin = discover_plugins(word, pm);
    if(nbPlugin == 0)
		  printf("\nPas de plugins\n");
		else
      display_menu(pm);
      
    int  number;

		printf("Choisissez une fonction : \n");
		scanf("%d", &number);
		filter_function f = get_plugin(pm, number)->m_filtre;
		f(cv::Mat());
    
    //release_manager(pm);
    
    return 0;
}
