#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	cv::Mat invert_filter(cv::Mat src)
	{
		src =  cv::Scalar::all(255) - src;
		printf("Couleurs inversées\n");
		return src;
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "invert_filter",
		    "Inverse les couleurs d'une image",
		    invert_filter);
  }
};
