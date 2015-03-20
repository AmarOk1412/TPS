#include "pluginmanager.h"

#include <dlfcn.h>
// À COMPLÉTER TODO: On va avoir des pitis problemes

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
	typedef struct node{
		struct node *next;
		plugin_descriptor* data; 
	} node;
	
  // le manager
  struct
  {
  	node *begin;
  } plugin_manager_t;


  //------------------------------------------------------------------------
  // fonctions destinées à l'application
  //------------------------------------------------------------------------

  // initialiser un manager
  plugin_manager *
  make_manager()
  {
    node* head = NULL;
    head = malloc(sizeof(node));
    plugin_manager* manager = malloc(sizeof(plugin_manager));
    manager->begin = head;
    return manager;
  }

  // libérer les ressources du gestionnaire
  void
  release_manager(plugin_manager * pm)
  {
    node* nxt = pm->begin;
    while(nxt != NULL)
    {
      node* tempMaillon = nxt;
      nxt = nxt->next;
      free(tempMaillon);
    }
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
    	char name[] = d->d_name;
    	if(strlen(name)-strlen(plugin_suffix) > 0 
    	&& subString(name,strlen(name)-strlen(plugin_suffix),strlen(name))==plugin_suffix)
    	{	
    		// Chargement de la bibliothèque
    		void * handle = dlopen(name, RTLD_LAZY);
				if (handle == NULL) {
					fprintf(stderr, "%s\n", dlerror());
					exit(EXIT_FAILURE);
				}

				dlerror();
				
				dlsym(handle, initfunc_name);
				
    		++compteur;
    	}
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
    int compteur = 1;
    node* maillon = pm->begin->next;
    while(maillon != NULL)
    {
      printf( maillon->data->m_name + "-%d : " + maillon->data->m_description + "\n", compteur);
      maillon = maillon->next;
      ++compteur;
    }
  }

  //------------------------------------------------------------------------
  // fonction destinée aux plugins
  //------------------------------------------------------------------------

  // enregistrer un plugin
  void
  register_plugin(plugin_manager * pm,
		  const char filter_name[],
		  const char filter_description[],
		  filter_function the_filter)
  {
    //Création du plugin 
    plugin_descriptor * plugin = malloc(sizeof(plugin_descriptor));>
    plugin->m_name=filter_name;
    plugin->m_description=filter_description;
    m_filtre=the_filter;
    //Création du maillon
    node* tnode = malloc(sizeof(node));
    tnode->data=plugin;
    tnode->next=NULL;
    //Ajout en fin
    node* maillon = pm->begin;
    while(maillon->next != NULL)
      maillon = maillon->next;
    maillon->next = tnode;
  }

};
