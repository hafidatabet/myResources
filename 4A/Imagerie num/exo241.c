#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

int main(int argc, char **argv)
{
  IplImage *ImageCouleur; 
  IplImage *ImageNB;

  ImageCouleur = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
  if (ImageCouleur == NULL){
    printf("Caramba, pas vu pas pris!\n");
    return(1);
  }
  
  ImageNB = cvCreateImage(cvGetSize(ImageCouleur),IPL_DEPTH_8U,1);
  cvCvtColor(ImageCouleur, ImageNB, CV_BGR2GRAY);
  cvNamedWindow("Couleur",CV_WINDOW_AUTOSIZE);
  cvNamedWindow("NB",CV_WINDOW_AUTOSIZE);
  cvShowImage("Couleur",ImageCouleur);
  cvShowImage("NB",ImageNB);
  cvWaitKey(0);
  
  cvReleaseImage(&ImageCouleur);
  cvReleaseImage(&ImageNB);
  cvDestroyWindow("Couleur");
  cvDestroyWindow("NB");
  
  return(0);
}
