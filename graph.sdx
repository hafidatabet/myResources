// pour compiler : gcc -Wall -g -lm fenetre.c -lcsfml-graphics  -o fenetre
//
/* Vfinale = Vinitiale + A * DeltaT;
 * Xfinale = Xinitiale + t / (2 * (Vinitiale + Vfinale));
 */
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <string.h>
#include <math.h>

#define masse 10
#define raideur 1000
#define DeltaT 0.1
#define l_vide 70
#define MAX(x,y) x>y ? x : y

typedef struct noeud {
	float posx;
	float posy;
	float vitx;
	float vity;
	float accx;
	float accy;
	float disx;
	float forx;
	float fory;
	float repx;
	float repy;
	char name[3];
};

typedef struct link {
	unsigned char depart[3];
	unsigned char  fin[3];
};


void simulation_ressort(struct noeud *pt1, struct noeud *pt2)
{

  float pt1pt2 = sqrt (pow((pt1->posx)-(pt2->posx),2)+pow((pt1->posy)-(pt2->posy),2));
  float Fpt1 = - raideur *( 1 - (l_vide / pt1pt2)) ;

  pt1->forx = Fpt1 * (pt1->posx - pt2->posx);
  pt1->fory = Fpt1 * (pt1->posy - pt2->posy);

  pt2->forx = Fpt1 * (pt2->posx - pt1->posx);
  pt2->fory = Fpt1 * (pt2->posy - pt1->posy);

}

int sont_lies(struct link *liens, int nbre_liens, struct noeud pt1, struct noeud *pt2)
{
	unsigned index_liens = 0;
	for (index_liens = 0 ; index_liens < nbre_liens ; index_liens++)
		{
			if(
					(!strcmp(liens[index_liens].depart,pt1.name)&&!strcmp(liens[index_liens].fin,pt2->name))
					||
					(!strcmp(liens[index_liens].fin,pt1.name)&&!strcmp(liens[index_liens].depart,pt2->name))
				)

				return 1;
		}
	return 0;
}

void simulation_repulsion(struct noeud *N, int nbre_points, struct link *liens, int nbre_liens, struct noeud *pt)
{
	unsigned int index_points = 0;
	float distanceX = 0;
	float distanceY = 0;
	for(index_points = 0; index_points < nbre_points ; index_points++)
	{
		if(!sont_lies(liens	,nbre_liens,N[index_points],pt)&&strcmp(N[index_points].name,pt->name))
		{
			distanceX = pt->posx-N[index_points].posx;
			distanceY = pt->posy-N[index_points].posy;

			if(distanceX > 0)
				pt->repx += 5/pow(distanceX,2);
			else
				pt->repx -= 5/pow(distanceX,2);

			if(distanceY >0)
				pt->repy += 5/pow(distanceY,2);
			else
				pt->repy -= 5/pow(distanceY,2);

			/*pt->accx = pt->repx / masse;
			pt->accy = pt->repy / masse;

			pt->vitx = pt->accx * DeltaT;
			pt->vity = pt->accy * DeltaT;

			pt->posx += pt->vitx * DeltaT;
			pt->posy += pt->vity * DeltaT;
			*/
		}
	}
}

void translation(struct noeud *N,int nbre_points)
{
	unsigned int index_points = 0;
	float baryX = 0;
	float baryY = 0;
	for(index_points = 0; index_points < nbre_points ; index_points++)
	{
		baryX += N[index_points].posx;
		baryY += N[index_points].posy;
	}

		baryX /= nbre_points;
		baryY /= nbre_points;

	if(baryX > 300)
	{
		for (index_points = 0 ; index_points < nbre_points ; index_points++)
			N[index_points].posx -= 1;
	}
	if(baryY > 200)
	{
		for (index_points = 0 ; index_points < nbre_points ; index_points++)
			N[index_points].posx -= 1;
	}
	if(baryX < 100)
	{
		for (index_points = 0 ; index_points < nbre_points ; index_points++)
			N[index_points].posx += 1;
	}
	if(baryY < 100)
	{
		for (index_points = 0 ; index_points < nbre_points ; index_points++)
			N[index_points].posx += 1;
	}

}

void affichage(sfRenderWindow *fenetre,struct noeud *graphe,int nbre_points,struct link *liens,int nbre_liens) {
  // préparation des couleurs
	unsigned int index_points = 0;
	unsigned int index_liens = 0;
	unsigned int temp_depart = 0 , temp_fin = 0;
	sfColor noir = {0,0,0,0}, blanc = {255,255,255,255}, gris = {128,128,128,128};
	sfShape **cercle = malloc(nbre_points*sizeof(sfShape*));
	sfShape **ligne = malloc (nbre_liens*sizeof(sfShape*));

	sfRenderWindow_Clear(fenetre,noir);
	// draw circles
	for (index_points = 0 ; index_points < nbre_points ; index_points ++)
		{
			cercle[index_points] = sfShape_CreateCircle(graphe[index_points].posx,graphe[index_points].posy,10,blanc,1,gris);
			sfRenderWindow_DrawShape(fenetre,cercle[index_points]);  // tracer le cercle1
			sfString *texte = sfString_Create();
			  sfString_SetText(texte,graphe[index_points].name);
			  sfString_SetPosition(texte,(graphe[index_points].posx)+ 5, (graphe[index_points].posy)+ 5);
			  sfRenderWindow_DrawString(fenetre,texte);
		}
	// draw lines
	for (index_liens = 0 ; index_liens < nbre_liens ; index_liens++)
		{
		 	sscanf(liens[index_liens].depart,"%d",&temp_depart);
		 	sscanf(liens[index_liens].fin,"%d",&temp_fin);

		 	ligne[index_liens] = sfShape_CreateLine(graphe[temp_depart].posx,graphe[temp_depart].posy,
													graphe[temp_fin].posx,graphe[temp_fin].posy,
													1,blanc,1,gris);
			sfRenderWindow_DrawShape(fenetre,ligne[index_liens]);
		}
	sfRenderWindow_Display(fenetre); // visualiser le contenu de la fenetre

	// faire le ménage en mémoire
}

void initGraphe(struct noeud *N,int nbre_points, struct link *liens, int nbre_liens)
{
	FILE *fp = NULL;
	char s[10];
	unsigned int depart;
	unsigned int fin;
	unsigned int index = 0;
	unsigned int index_liens = 0;
	fp = fopen("file.txt","r");
	fgets(s,10,fp);

	for(index = 0 ; index < nbre_points ; index++)
		{
			N[index].posx = (rand() % 600)+50;
			N[index].posy = (rand() % 400)+50;
			N[index].accx = 0;
			N[index].accy = 0;
			N[index].forx = 0;
			N[index].fory = 0;
			N[index].vitx = 0;
			N[index].vity = 0;
			sprintf(N[index].name,"%d",index);
		}
	while (fgets(s,10,fp)!=NULL)
		{
			sscanf(s,"%d-%d",&depart,&fin);

			sprintf(liens[index_liens].depart,"%d",depart);
			sprintf(liens[index_liens].fin,"%d",fin);
			index_liens++;
		}
}

void simulation(struct noeud *N, int nbre_points, struct link *liens, int nbre_liens)
{
	unsigned int index_liens = 0;
	unsigned int index_points1 = 0 , index_points2 = 0;
	unsigned int depart = 0;
	unsigned int fin = 0;
	unsigned int k = 200;
	unsigned int dist_repos = 60;
	float dist = 0;
	float Fress = 0;
	float Frep = 0;
	float deltaX = 0, deltaY = 0;


	for (index_liens = 0; index_liens < nbre_liens ; index_liens++)
	      {
	    	 sscanf(liens[index_liens].depart,"%d",&depart);
	    	 sscanf(liens[index_liens].fin,"%d",&fin);

	    	 dist = sqrt (pow((N[depart].posx)-(N[fin].posx),2)+pow((N[depart].posy)-(N[fin].posy),2));
	    	 Fress = - raideur *( 1 - (l_vide / dist)) ;

	    	 N[depart].forx = Fress * (N[depart].posx - N[fin].posx);
	    	 N[depart].fory = Fress * (N[depart].posy - N[fin].posy);

	    	 N[depart].accx = (N[depart].forx + N[depart].repx) / masse;
	    	 N[depart].accy = (N[depart].fory + N[depart].repy) / masse;

	    	 N[depart].vitx = N[depart].accx * DeltaT ;
	    	 N[depart].vity = N[depart].accy * DeltaT ;

	    	 N[depart].vitx *= 0.2;
	    	 N[depart].vity *= 0.2;

	    	 N[depart].posx += N[depart].vitx * DeltaT;
	    	 N[depart].posy += N[depart].vity * DeltaT;

	    	 N[fin].forx = Fress * (N[fin].posx - N[depart].posx);
	    	 N[fin].fory = Fress * (N[fin].posy - N[depart].posy);

	    	 N[fin].accx = (N[fin].forx + N[fin].repx) / masse;
			 N[fin].accy = (N[fin].fory + N[fin].repy) / masse;

			 N[fin].vitx = N[fin].accx * DeltaT ;
			 N[fin].vity = N[fin].accy * DeltaT ;

			 N[fin].vitx *= 0.2;
			 N[fin].vity *= 0.2;

			 N[fin].posx += N[fin].vitx * DeltaT;
			 N[fin].posy += N[fin].vity * DeltaT;

	    	 dist = sqrt (pow((N[depart].posx)-(N[fin].posx),2)+pow((N[depart].posy)-(N[fin].posy),2));

	    	 printf("distance liees (%s<->%s) = %f\n",N[depart].name,N[fin].name,dist);

	      }


	for (index_points1 = 0; index_points1 < nbre_points ; index_points1++)
	{
		for (index_points2 = 0; index_points2 < nbre_points ; index_points2++)
		{
			if ((index_points1 != index_points2)&&(!sont_lies(liens,nbre_liens,N[index_points1],&N[index_points2])))
			{
				dist = sqrt (pow((N[index_points1].posx)-(N[index_points2].posx),2)+pow((N[index_points1].posy)-(N[index_points2].posy),2));
				deltaX = N[index_points1].posx - N[index_points2].posx;
				deltaY = N[index_points1].posy - N[index_points2].posy;

				Frep = 10000 / (pow(dist,2));

				N[index_points1].repx = Frep * deltaX ;

				N[index_points1].repy = Frep * deltaY ;

				N[index_points1].accx = (N[index_points1].forx + N[index_points1].repx) / masse;
				N[index_points1].accy = (N[index_points1].fory + N[index_points1].repy) / masse;

				N[index_points1].vitx = N[index_points1].accx * DeltaT ;
				N[index_points1].vity = N[index_points1].accy * DeltaT ;

				N[index_points1].vitx *= 0.2;
				N[index_points1].vity *= 0.2;

				N[index_points1].posx += N[index_points1].vitx * DeltaT;
				N[index_points1].posy += N[index_points1].vity * DeltaT;

				dist = sqrt (pow((N[index_points1].posx)-(N[index_points2].posx),2)+pow((N[index_points1].posy)-(N[index_points2].posy),2));

				printf("distance non liees (%s<->%s)= %d \n",N[index_points1].name,N[index_points2].name,dist);
				printf("force rep = %f\n",Frep);

			}
		}

	}


}


int main() {

	//CHarger le graphe du fichier
	FILE * fp = NULL;
	unsigned int nbre_points = 0,x=0;
	unsigned int index_points = 0;
	unsigned int nbre_liens = 0;
	unsigned int index_liens = 0;
	unsigned int depart=0,fin=0;
	char s[3];
	fp = fopen("file.txt","r");
	if(fp==NULL)
			return 0;
	fgets(s,5,fp);
	sscanf(s,"%d",&x);
	nbre_points = x;
	while (fgets(s,10,fp)!=NULL)
		nbre_liens ++;
	struct noeud *N = (struct noeud*)malloc(sizeof(struct noeud)*nbre_points);
	struct link *liens =  (struct link*)malloc(sizeof(struct link)*nbre_liens);
	initGraphe(N,nbre_points,liens,nbre_liens);

    sfRenderWindow *fenetre;
    sfVideoMode mode = {800, 600, 32};
    sfWindowSettings settings = {24, 8, 0};
    fenetre = sfRenderWindow_Create(mode, "Ma fenetre",  sfResize | sfClose, settings);
    sfEvent evenement;

    	// Boucle principale
   while (sfRenderWindow_IsOpened(fenetre)) {
      // gestion des evenements
      sfRenderWindow_GetEvent(fenetre, &evenement);
      if (evenement.Type == sfEvtClosed) { // sortie de boucle d'animation
        sfRenderWindow_Close(fenetre);
      }

	  simulation(N,nbre_points,liens,nbre_liens);

      affichage(fenetre,N,nbre_points,liens,nbre_liens);
    }
    sfRenderWindow_Destroy(fenetre);

    return EXIT_SUCCESS;
}
