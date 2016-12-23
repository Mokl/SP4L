#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


char commande[50];
char Tablesegment [5][1024];

/*
Cette fonction divise la chaine en "mot"
et les sauvegardes à chaque position Y dans le tableau à deux dimension.
Toute cette commande peut être simplifié par l'utilisation de strtok,
cette a été évité pour l'originalité et montrer la compréhension de la
commande.
*/
void hacheur()
{
	int compteur = 0;
	int seg = 0;
	int efface = 0;
	int taille = 0;
	int table = 0;
	char segment [50]="";
	
	//parcours les caractère dans "commande"	
	for(compteur=0;compteur<(strlen(commande));compteur++)
	{	
		//Sauvegarde le mot dans "Tablesegment" à chaque espace et fin de ligne
		if(commande[compteur]==' ' || commande[compteur] == '\n') 
		{		
			strcpy(Tablesegment[table],segment);
			table++;
			seg = 0;
			taille = strlen(segment);
				
			for(efface = 0; efface <= taille;efface++)
			{
				strcpy(segment,"");
			}
		}
		//copie du caractère
		else
		{		
			segment[seg] = commande[compteur];
			seg++;
		}
	}
		
}

/*
Cette créé un processus et execute la commande
*/
void process()
{
	char path [20];
	pid_t process=fork();
		
  			
	
	sprintf(path, "./%s", Tablesegment[0]);
	
	//si on se trouuve dans le fils
	if (process==0)
	{
		//on execute la commande dans "Tablesegment", il y a maximum 2 option par commande
		int check = execlp(path, Tablesegment[0], Tablesegment[1], Tablesegment[2], NULL);
		if (check==-1) printf("Erreur syntaxe? Ou Path incorect cfr Ligne 69\n");
		exit(0);
	}
	
	else
	{
		wait(&process);
	}
}

int main(int argc, char **argv)
{
	
	while(1)
	{
		//Lecture de la ligne de commande et sauvegarde de celle-ci
		printf("Commande:");
		fgets(commande,50,stdin);
		
		
		if (strcmp("exit\n",commande)==0)
		{
			exit(0);
		}

		
		
		//Si le nom du fichier est spécifié lors de l'execution du shell
		if (argc > 1)
		{
			//on ouvre un fichier en read only
			int fichier = open(argv[optind],O_RDONLY); 
			char *pos, *string;
		
			//On sauvegarde le contenue du fichier
			while((read(fichier, Tablesegment[0], 1024)) > 0);
			 
			//pos contien la position sauvegardé par strtok_r lors du decoupage
			string = strtok_r(Tablesegment[0], "\n", &pos);

			//Tant que string n'est pas vide, on execute les commandes qu'il contient
			while (string != NULL)
			{
				printf("\n Execution: %s \n", string);

				strcpy(commande,string);

				hacheur();
				process();
				
				//Ligne suivante mise dans string
				string = strtok_r(NULL, "\n", &pos);
			}
			//fermeture du fichier
			close(fichier);
		}
		
		
		//Simple execution de commande
		else
		{
			
			hacheur();
			process();
		}
    }
}