#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	cv::Mat blur_filter(cv::Mat src)
	{
		cv::Mat image = cv::imread("Blur_Image.jpg");
		cv::Mat blur_image; //image résultat
		cv::blur(image,blur_image,cv::Size(5,5)); //appliquer l'effet de flou sur l'image
		return image;
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "blur_filter",
		    "Applique un l'effet blur",
		    blur_filter);
  }
};
