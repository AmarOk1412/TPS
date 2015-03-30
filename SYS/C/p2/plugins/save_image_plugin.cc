#include <cv.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	/**
   * Sauvegarder une image
   * @param src : une matrice de points
   * @return une matrice de points
   */
	cv::Mat save_filter (cv::Mat src)
	{
		printf("Entrez le nom du fichier pour enregistrer l'image :"); 
		char *word;
		char buf[100]; /*buffer*/
		scanf("%s", buf); /*read string in buffer*/
		word = (char*) malloc(strlen(buf) + 1);
		if (word == NULL) {
			printf("Error: out of memory ...\n");
			exit(1);
		}
		strcpy(word, buf);
		printf("Image enregistrée sous le nom %s\n", word);
		cv::imwrite(word, src); //enregistrer l'image sur le dd
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
