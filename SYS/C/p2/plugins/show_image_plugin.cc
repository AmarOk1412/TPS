#include <cv.h>
#include <stdio.h>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	void display_filter (cv:: Mat image)
	{
	
		namedWindow( "Display window", WINDOW_AUTOSIZE );			// Create a window for display.
		imshow( "Display window", image );                   // Show our image inside it.

		waitKey(0);                                          // Wait for a keystroke in the window
   
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "display_filter",
		    "Affiche une image",
		    display_filter);
  }
};
