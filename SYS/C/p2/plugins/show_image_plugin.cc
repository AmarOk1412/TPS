#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	cv::Mat display_filter(cv::Mat src)
	{
		cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );			// Create a window for display.
		cv::imshow( "Display window", src);                   // Show our image inside it.
		cv::waitKey(0);                                          // Wait for a keystroke in the window
		return src;
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
