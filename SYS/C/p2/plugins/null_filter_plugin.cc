#include <cv.h>
#include <stdio.h>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

  // filtre sans effet
  cv::Mat
  null_filter(cv::Mat src)
  {
    printf("\nnull_filter : bravo, vous avez appliqué votre premier filtre...\n");
    return src;
  }

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "null_filter",
		    "Exemple de filtre inutile",
		    null_filter);
  }
};
