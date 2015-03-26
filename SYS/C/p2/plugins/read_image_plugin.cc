#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	cv::Mat read_filter(cv::Mat src)
	{
		printf("Entrez le nom du fichier qui contient l'image :"); 
		char *word;
		char buf[100]; /*buffer*/
		scanf("%s", buf); /*read string in buffer*/
		word = (char*) malloc(strlen(buf) + 1);
		if (word == NULL) {
			printf("Error: out of memory ...\n");
			exit(1);
		}
		strcpy(word, buf);
		
		src = cv::imread(word, CV_LOAD_IMAGE_COLOR);

    if(!src.data)
    	printf("Fichier non trouvé !\n");
    else
    	printf("Image chargée !\n");

		return src;
	}

  // enregistrer le plugin
  void
  init_(plugin_manager * pm)
  {
    register_plugin(pm,
		    "read_filter",
		    "Lire une image",
		    read_filter);
  }
};
