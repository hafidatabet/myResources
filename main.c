#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gram_limit{
	int nbr;
	char gram[10][10];
};

void ShiftG(char tmp[10])
{
	int i = 0;
	for(;i<10;i++)
		tmp[i] = tmp[i+1];
	tmp[i] = 0;
}

void ShiftD(char tmp[10], char c)
{
	int i = 10;
	for(;i>0;i--)
		tmp[i] = tmp[i-1];
	tmp[0] = c;
}


void main()
{

	FILE* fp = fopen("file.txt","r");
	if(fp == NULL)
	{
		printf("Cannot open file\n");
		exit (0);
	}
	struct gram_limit GL[10];
	char tete[10];
	int itete = 0;
	char Atete = 0;
	char gram[10][10][10];
	char tmp[10];
	rewind(fp);
	int inst = 0;
	int instruction = 0;
	printf("Fichier Input ouvert avec succes\n");
	printf("Analyse du fichier en cours\n");
	while(fgets(tmp,10,fp)!=NULL)
	{
		instruction ++;
		Atete = tmp[0];
		ShiftG(&tmp);
		if (tete[itete] != Atete)
		{

			itete ++;
			tete[itete] = Atete;
			GL[itete].nbr = 0;
			inst = 0;
			int ii = 0;

		}
		else
		{
			GL[itete].nbr++;
		}

		strcpy(GL[itete].gram[inst],tmp);
		inst ++ ;
	}
	fclose(fp);
	printf("Fichier Input fermé\n");
	FILE* fpout = fopen("output.txt","w");
	if (fpout == NULL)
	{
		printf("ERROR opening output file\n");
		exit (0);
	}
	printf("Fichier Output ouvert avec succes\n");
	printf("Traitement en cours\n");
	int indexTmp = 0;
	int tmpCar = 0;
	char bigTmp[10];
	int instR = 0;
	int rec = 0;
	for(;indexTmp<=itete;indexTmp++,instR=0,rec=0)
	{
		for (instR=0;instR<=GL[itete-1].nbr;instR++)
		{
			strcpy(bigTmp,GL[indexTmp].gram[instR]);
			if(bigTmp[tmpCar] == tete[indexTmp])
			{
				int len =  strlen(bigTmp);
				bigTmp[len-1]=tete[indexTmp];
				bigTmp[len]='`';
				bigTmp[len+1]=0;
				ShiftG(&bigTmp);
				ShiftD(&bigTmp,'`');
				ShiftD(&bigTmp,tete[indexTmp]);
				fputs(bigTmp,fpout);
				fputc('\n',fpout);
				fputc(tete[indexTmp],fpout);
				fputs("`£\n",fpout);
				rec = 1;
			}
			else
			{
				if (rec==1)
				{
					int len = strlen(bigTmp);
					bigTmp[len-1]=tete[indexTmp];
					bigTmp[len]='`';
					bigTmp[len+1]=0;
				}
				ShiftD(&bigTmp,tete[indexTmp]);
				fputs(bigTmp,fpout);
				if(rec==1)
					fputc('\n',fpout);
			}
		}
	}

	printf("Traitement terminé\n");
	printf("Résultat imprimé dans le fichier output.txt\n");
	fclose(fpout);
	printf("Fermeture du fichier output.txt\n");

}
