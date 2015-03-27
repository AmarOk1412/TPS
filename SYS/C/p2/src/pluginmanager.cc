#include "pluginmanager.h"

#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// À COMPLÉTER

extern "C" {

  //------------------------------------------------------------------------
  // les constantes
  //------------------------------------------------------------------------
  // suffixe des bibliothèques de plugin
  char plugin_suffix[] = "_plugin.so";
  // nom de la fonction d'initialisation d'un plugin
  char initfunc_name[] = "init_";

  //------------------------------------------------------------------------
  // les types (À COMPLÉTER)
  //------------------------------------------------------------------------

  // type des éléments de la liste des plugins
	typedef struct _node{
		struct _node *next;
		plugin_descriptor* data; 
	} node;
	
  // le manager
  struct plugin_manager_t
  {
  	node *begin;
  };

	typedef void (*initFunction) (plugin_manager *);

  //------------------------------------------------------------------------
  // fonctions destinées à l'application
  //------------------------------------------------------------------------

  // initialiser un manager
  plugin_manager *
  make_manager()
  {
    node* head = (node*) malloc(sizeof(node));
    plugin_manager* manager = (plugin_manager*) malloc(sizeof(plugin_manager));
    head->next = NULL;
    manager->begin = head;
    return manager;
  }

  // libérer les ressources du gestionnaire
  void
  release_manager(plugin_manager * pm)
  {
    free(pm);
  }

  // découvrir les plugins ; résultat = nombre de plugins
  unsigned int
  discover_plugins(const char dirname[], plugin_manager * pm)
  {
  	unsigned int compteur = 0;
    DIR* dir = opendir(dirname);
    if(dir == NULL)
      return 0;
    struct dirent*  d = readdir(dir); 
    while(d != NULL)
    {
    	const char* name = d->d_name;
      
    	if(strstr(name,plugin_suffix) != NULL)
    	{
    		// Chargement de la bibliothèque
    		char* full;
				full = (char*)malloc(strlen(dirname)+strlen(name)+3); 
				strcpy(full, dirname); 
				strcat(full, "/"); 
				strcat(full, name);

    		printf("Chargement de %s \n", full);
    		void * handle = dlopen(full, RTLD_LAZY);
				if (handle == NULL) {
					fprintf(stderr, "%s\n", dlerror());
					exit(EXIT_FAILURE);
				}
				dlerror();
				initFunction IF = (initFunction) dlsym(handle, initfunc_name);
				IF(pm);
				free(full);
    		++compteur;
    	}
    	d = readdir(dir);
    }
    closedir(dir);
    return compteur;
  }

  // chercher et renvoyer le plugin de numéro donné (commence à 0)
  plugin_descriptor *
  get_plugin(plugin_manager * pm, unsigned int plugin_number)
  {
    unsigned int compteur = 0;
    node* maillon = pm->begin->next;
    while(maillon != NULL)
    {
    	if(compteur == plugin_number)
    		return maillon->data;
      maillon = maillon->next;
      ++compteur;
    }
    return NULL; 
  }

  // afficher le menu des plugins disponibles
  void
  display_menu(plugin_manager * pm)
  {
  	printf("#################################################\n\
###                  MENU                     ###\n\
#################################################\n\
 (-3) : Quitter\n\
 (-2) : Charge un dossier de plugins\n\
 (-1) : Affiche le menu\n");
		int compteur = 0;
    node* maillon = pm->begin->next;
    while(maillon != NULL)
    {
      printf(" (%d) : ", compteur);
    	printf(maillon->data->m_name);
      printf(" - ");
      printf(maillon->data->m_description);
      printf("\n");
      maillon = maillon->next;
      ++compteur;
    }
  }

  //------------------------------------------------------------------------
  // fonction destinée aux plugins
  //------------------------------------------------------------------------
  
  bool plugin_exist(plugin_manager * pm, const char filter_name[])
		{
			node* maillon = pm->begin;
  		while(maillon != NULL)
     	{
     		if(maillon->data->m_name == filter_name)
     			return true;
     		maillon = maillon->next;
     	}
     	return false;
		}

  // enregistrer un plugin
  void
  register_plugin(plugin_manager * pm,
		  const char filter_name[],
		  const char filter_description[],
		  filter_function the_filter)
  {
  	if(plugin_exist(pm, filter_name))
  		return;
    //Création du plugin 
    plugin_descriptor* plugin = (plugin_descriptor*) malloc(sizeof(plugin_descriptor));
    plugin->m_name=filter_name;
    plugin->m_description=filter_description;
    plugin->m_filtre=the_filter;
    //Création du maillon
    node* tnode = (node*) malloc(sizeof(node));
    tnode->data=plugin;
    tnode->next=NULL;
    //Ajout en fin
    node* maillon = pm->begin;
    while(maillon->next != NULL)
      maillon = maillon->next;
    maillon->next = tnode;
  }

};
