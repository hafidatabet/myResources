#include <stdio.h>
#include <opencv/highgui.h>

typedef struct ParamClick
{
  IplImage * Img;
  IplImage * Clone;
  char * WindowName;
  CvFont* Font;
}
ParamClick;

void PrintRGB(int event, int x, int y, int flags, void* param)
{
  ParamClick * paramTmp;
  CvScalar BGRval;
  char text[100];
  paramTmp=(ParamClick *)param;
  if (event == CV_EVENT_MOUSEMOVE){
    cvCopy(paramTmp->Img, paramTmp->Clone, NULL);
    BGRval=cvGet2D(paramTmp->Img, y, x);
    sprintf(text,"r=%.0f g=%.0f b=%.0f",BGRval.val[2],BGRval.val[1], BGRval.val[0]);
    cvPutText(paramTmp->Clone, text, cvPoint(x,y),paramTmp->Font, cvScalar(0,0,255,0));
    cvShowImage(paramTmp->WindowName,paramTmp->Clone);
  }
}

int main(int argc, char** argv)
{
  ParamClick param;
  char WindowName[100];
  IplImage* clone, *img;
  CvFont font;

  img=cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
  if (img==NULL){
    printf("Caramba, pas vu pas pris!\n");
    return(1);
  }
  sprintf(WindowName,"Image");
  cvNamedWindow(WindowName, CV_WINDOW_AUTOSIZE);

  cvSetMouseCallback(WindowName, PrintRGB, 
  (void*)&param);
  
  cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX_SMALL, 
  1.,1., 0, 1, 8);

  clone = cvCloneImage(img);
  param.Img=img;
  param.Clone=clone;
  param.WindowName=WindowName;
  param.Font=&font;

  cvShowImage(WindowName,img);
  cvWaitKey(0);

  cvReleaseImage(&img);
  cvDestroyWindow("Exemple image");
  return(0);
}
