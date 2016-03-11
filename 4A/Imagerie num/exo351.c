
#include <opencv/highgui.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0


int main(int argc, char ** argv)
{
  IplImage * Frame;
  char StopKey;
  int Position, // NbFrames;
 // CvCapture * Video;

  cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
  Video = cvCreateFileCapture(argv[1]);
  if (Video == NULL){
    printf("Caramba, pas de fichier video!\n");
    return(0);
  }
  //NbFrames =(int) cvGetCaptureProperty(Video,CV_CAP_PROP_FRAME_COUNT);
  //cvCreateTrackbar( "Position","Video",&Position,NbFrames,NULL);
  cvSetTrackbarPos("Position", "Video", 0);
  while(1){
   // Position = (int)cvGetCaptureProperty(Video, CV_CAP_PROP_POS_FRAMES);
   // cvSetTrackbarPos("Position", "Video", Position);
    Frame = cvQueryFrame(Video); 
    if ( Frame == NULL)
      break;
    
    cvShowImage("Video",Frame);
    StopKey = (char) cvWaitKey(33);
    if (StopKey == 27)
        break;    
  }
  cvDestroyWindow("Video");
  cvReleaseCapture(&Video);
  return(0);
}
