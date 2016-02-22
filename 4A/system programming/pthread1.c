// Affiche toutes les secondes a l'ecran la derniere chaine saisie
// par l'utilisateur
// Stoppe tout quand la chaine saisie est "quit"

#include "stdio.h"
#include "string.h"
#include "pthread.h"

void * affiche(void * param)  // Thread d'affichage
{
	while (1) {
		printf("%s\n", (char*)param);
		sleep(1);
	}
}

int main()  // Thread principal
{
	char commande[80];
	pthread_t MyTh;

	strcpy(commande, "Hello");
	pthread_create(&MyTh,NULL,affiche, commande);

	do
	{
		scanf("%s", commande);
	} while (strcmp(commande, "quit") != 0);

	printf("fin ....\n"); 
	return 0;
}
