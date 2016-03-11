#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>

int main (int argc, char **argv)
{
  CvCapture* capture=cvCaptureFromFile(argv[1]);
  
  IplImage * frame;
  IplImage * frameNB;
  char c;
  cvNamedWindow("Exemple video", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("Exemple video NB", CV_WINDOW_AUTOSIZE);
  while(1){
    frame = cvQueryFrame(capture);
    if(frame==NULL){ 
      break;
      printf("Caramba, pas vu pas pris!\n");
    }
    frameNB = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
    cvCvtColor(frame, frameNB, CV_BGR2GRAY);
    cvShowImage("Exemple video", frame);
    cvShowImage("Exemple video NB", frameNB);
    c=cvWaitKey(33);/*attente de 33ms*/
    
      if(c==27) break;/* touche esc*/
    cvReleaseImage(&frameNB);
  }
    
  cvReleaseCapture(&capture);
  cvDestroyWindow("Exemple video");
  return(0);
}
