#include <cv.h>
#include <stdio.h>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	void save_filter ()
	{
		 imwrite( "Blur_Image.jpg", blur_image ); //enregistrer l'image sur le dd
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "save_filter",
		    "Enregistre une image",
		    save_filter);
  }
};
