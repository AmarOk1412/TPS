#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	cv::Mat display_filter(cv::Mat src)
	{
		cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
		printf("Image transformée en niveaux de gris !\n");
		return src;
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "gray_filter",
		    "Transforme une image en niveau de gris",
		    display_filter);
  }
};
