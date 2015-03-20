#ifndef __PLUGINMANAGER__H
#define __PLUGINMANAGER__H

#include <cv.h>

extern "C" {

  //------------------------------------------------------------------------
  // les types
  //------------------------------------------------------------------------

  // fonction de réalisation du plugin
  typedef
  cv::Mat (* filter_function)(cv::Mat src);

  // descripteur de plugin
  typedef 
  struct {
    const char *    m_name;		// nom du filtre
    const char *    m_description;	// description de l'effet du filtre
    filter_function m_filtre;		// fonction de réalisation du filtre
  } plugin_descriptor;

  // struct plugin_manager_t est le type du gestionnaire
  // c'est une structure dont le contenu est à définir dans pluginmanager.cc
  // et qui n'est pas dévoilé
  struct plugin_manager_t;

  // plugin_manager est synonyme de struct plugin_manager_t
  typedef
  struct plugin_manager_t
  plugin_manager;

  //------------------------------------------------------------------------
  // fonctions destinées à l'application
  //------------------------------------------------------------------------

  /**
   * initialiser un gestionnaire
   * @return manager initialisé
   */
  plugin_manager * make_manager();

  /**
   * libérer les ressources du gestionnaire
   * @param pm : le gestionnaire
   */
  void
  release_manager(plugin_manager * pm);

  /**
   * découvrir les plugins
   * @param dirname : répertoire où chercher les plugins
   * @param pm : le gestionnaire
   * @return : nombre de plugins
   */
  unsigned int
  discover_plugins(const char dirname[], plugin_manager * pm);

  /**
   * chercher et renvoyer le plugin de numéro donné
   * @param pm : le gestionnaire
   * @param plugin_number : numéro du plugin
   * @return le descripteur du plugin trouvé ; NULL si absent
   */
  plugin_descriptor *
  get_plugin(plugin_manager * pm, unsigned int plugin_number);

  /**
   * afficher le menu des plugins disponibles
   * @param pm : le gestionnaire
   */
  void
  display_menu(plugin_manager * pm);

  //------------------------------------------------------------------------
  // fonction destinée aux plugins
  //------------------------------------------------------------------------

  /**
   * enregistrer un nouveau plugin
   * @param pm : le gestionnaire
   * @param filter_name : nom du filtre
   * @param filter_description : description de son effet
   * @param the_filter : la fonction de filtrage
   */
  void
  register_plugin(plugin_manager * pm,
		  const char filter_name[],
		  const char filter_description[],
		  filter_function the_filter);

};
#endif // __PLUGINMANAGER__H
