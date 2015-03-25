#include <cv.h>
#include <stdio.h>
#include "plugin.h"
#include "pluginmanager.h"

extern "C" {

	void read_filter ()
	{
	
		print("Entrez le nom du fichier qui contient l'image :"); 
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
    image = imread(word, CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        printf("Could not open or find the image") ;
    }
   
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
