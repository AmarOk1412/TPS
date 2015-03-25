#include <cv.h>
#include <stdio.h>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	void blur_filter (Char[] filename)
	{
	
		 cv::Mat image = imread(filename);
		 image = imread( imageName, 1 );


		 cv::Mat blur_image; //image résultat
     cv::blur(image,blur_image,cv::Size(5,5)); //appliquer l'effet de fou sur l'image
		 imwrite( "Blur_Image.jpg", blur_image ); //enregistrer l'image sur le dd


		 return 0;
		}

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
