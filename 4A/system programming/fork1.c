// Affiche toutes les secondes a l'ecran la derniere chaine saisie
// par l'utilisateur
// Stoppe tout quand la chaine saisie est "quit"

#include "stdio.h"
#include "string.h"

main(int argc, char * argv[])
{
	int ret_fork;
	char msg[80] = "Hello";
	ret_fork = fork();  // clone processus

	if (ret_fork >= 0)
	{
		if (ret_fork > 0)  // code du pere
		{
			do
			{
				scanf("%s", msg);
				kill(ret_fork, 15); // arret du fils en cours
				ret_fork = fork(); // lancement d'un nouveau fils
				if (ret_fork == 0)  // code du fils
				{
					do
					{
						printf("%s\n", msg);
						sleep(1);
					} while (1);
				}
			} while (strcmp(msg, "quit") != 0);
			kill(ret_fork, 15);
		}
		else  // code du fils
		{
			do
			{
				printf("%s\n", msg);
				sleep(1);
			} while (1);
		}
	}
	else { printf(" ERREUR fork\n"); }
}

	/*  Ne marche pas....
	
	do
	{ sleep(1); }
	while (scanf("%s", msg) && (strcmp(msg,"quit") != 0));

	printf(" ...Termine\n");
	*/


