#include <cv.h>
#include <stdio.h>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	void blur_filter (cv:: Mat image)
	{
	
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "blur_filter",
		    "Affiche une image",
		    blur_filter);
  }
};
