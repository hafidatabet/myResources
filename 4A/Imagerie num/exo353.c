#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>


#define TRUE 1
#define FALSE 0
typedef struct ParamClick
{
  IplImage * Img;
  IplImage * Clone;
  CvRect * box;
  char draw_box;
  char * WindowName;
}
  ParamClick;
/*****************************/
void Trace(int event, int x, int y, int flags, void* param)
{
  IplImage *imgTmp;
  ParamClick *Param;
  Param = (ParamClick *)param;
   // On definit les cas possibles d'utilisation de la souris
  switch (event){
  //Au cas ou on déplace la souris
  case CV_EVENT_MOUSEMOVE:{
    if(Param->draw_box == TRUE){
      Param->box->width = x-Param->box->x;
      Param->box->height = y-Param->box->y;
    }
    break;
  }
  //Au cas ou on clique sur un bouton de la souris
  case CV_EVENT_LBUTTONDOWN:{
    Param->draw_box = TRUE;
    Param->box->x = x;
    Param->box->y = y;
    Param->box->width = 0;
    Param->box->height = 0;
    break;
  }
  //Au cas ou on enleve la main de la souris

  case CV_EVENT_LBUTTONUP:{
    Param->draw_box = FALSE;
    /* on s'assure que (X,Y) sont bien en haut a gauche */
    if (Param->box->width < 0){
      Param->box->width = -1 * Param->box->width;
      Param->box->x = Param->box->x - Param->box->width;
    }
    if (Param->box->height < 0){
      Param->box->height = -1 * Param->box->height;
      Param->box->y = Param->box->y - Param->box->height;
    }
    cvCopy( Param->Img, Param->Clone, NULL );
     //Definir une region d'interet dans l'image
    cvSetImageROI(Param->Clone, cvRect(Param->box->x ,Param->box->y,Param->box->width, Param->box->height));
    imgTmp=cvCreateImage(cvSize(Param->box->width, Param->box->height),IPL_DEPTH_8U, 1);
    cvCvtColor(Param->Clone, imgTmp, CV_BGR2GRAY);
    cvCvtColor(imgTmp, Param->Clone, CV_GRAY2BGR);
    cvReleaseImage(&imgTmp);
    cvResetImageROI(Param->Clone);
    break;
  }
  case CV_EVENT_RBUTTONDOWN:{
    cvCopy( Param->Img, Param->Clone, NULL );
    break;
  }
  }/* fin switch*/
}
/*****************************/
int main(int argc, char** argv)
{
  IplImage * Img, *Clone;
  char ExitKey;
  ParamClick Param;
  CvRect Box;
    
    
    //on renomme la fenetre et on lui attribue une taille standard
  cvNamedWindow("Image",CV_WINDOW_AUTOSIZE);
    //on charge l'image et on la sauvegarde dans la structure CV_LOAD_IMAGE
  Img = cvLoadImage( argv[1], CV_LOAD_IMAGE_COLOR);
    //si l'image n'a pas pu etre chargée on sort de la fonction
  if (Img==NULL){
    printf("Caramba, pas vu pas pris\n");
    return(1);
  }
  Param.Img = Img;
  Param.draw_box = FALSE;
  Box = cvRect(0,0,0,0);
  Param.box = &Box;
  Clone = cvCloneImage(Param.Img);
    // On cree
  Param.Clone = Clone; 
  cvSetMouseCallback("Image", Trace, (void*) &Param );
  while(1){
    if ( Param.draw_box ){
      cvCopy(Param.Img,Param.Clone,NULL);
    //Dessine le rectangle avec les coordonnées adéquates
      cvRectangle(Param.Clone, 
		  cvPoint(Param.box->x, Param.box->y),
		  cvPoint(Param.box->x+Param.box->width, 
			  Param.box->y+Param.box->height),
		  cvScalar(255,0,0,0),
		  1,8,0); 
    }
      //Affiche l'image Param.Clone dans la fenetre Image
    cvShowImage("Image",Param.Clone);
    ExitKey = cvWaitKey(15);
    if ( ExitKey == 27)
      break;
  }
    
    //Désalloue la mémoire reservée par la fenetre Image
  cvDestroyWindow("Image");
    //Désalloue la place mémoire occupée par Img
  cvReleaseImage(&Img);
  return(0);
}
