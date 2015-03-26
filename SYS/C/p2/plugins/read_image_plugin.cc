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
		
		cv::Mat image;
		image = cv::imread(word, CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
        printf("Could not open or find the image");
		return image;
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
