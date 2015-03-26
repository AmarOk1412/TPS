#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {
	cv::Mat save_filter (cv::Mat src)
	{
		printf("Image enregistrée sous le nom Blur_Image.jpg\n");
		cv::imwrite("Blur_Image.jpg", src); //enregistrer l'image sur le dd
		return src;
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
