#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	cv::Mat blur_filter(cv::Mat src)
	{
		cv::blur(src,src,cv::Size(5,5)); //appliquer l'effet de flou sur l'image
		printf("Flou appliqué\n");
		return src;
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "blur_filter",
		    "Applique un l'effet flou",
		    blur_filter);
  }
};
