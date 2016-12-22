//-f -i
#include <stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include<string.h>
#include <unistd.h>
#include <getopt.h>

typedef enum{ false, true}bool;


bool base(char source_file[20], char dest_file[20]);
bool f(char source_file[20], char dest_file[20]);
bool i(char source_file[20], char dest_file[20]);
bool i_opt (char source_file[20], char dest_file[20]);

int main(int argc, char *argv[])
{
	int iflag=0 , fflag=0 ,opterr = 0;
	char * cvalue = NULL ;
	int index , c ;
	char source[20]={0}, dest[20] = {0};
	
	 struct option options[] = 
    {
        {"force", no_argument, NULL, 'f'},
        {"interactive", no_argument, NULL, 'i'},
        {0, 0, 0, 0}
	};
	
	
	while (( c = getopt_long( argc , argv , "if",options,NULL)) != -1)
	{	
		switch ( c ) 
		{
			case 'i':
				iflag = 1; 
				break ;
				
			case 'f':
				fflag = 1; 
				break ;
				
			case '?':
				break;
				
				
			default :
			abort ();
		}
	}
	
	
	if (argc - optind == 0)
	{       
		printf("Veuillez donner un ficher source et de destination\n");
        return -1;
		
	}
	else
	{
		int i ;
		int j = 0;
	
		for( i = optind; i < argc; i++)
		{
			if(j == 0)
			{
				strcat(source,argv[i]);
			}
			else if(j == 1)
			{
				strcat(dest,argv[i]);
			}
			j++;
		}
	}
	
	if( iflag == 0 && fflag == 0 )
	{
		if(base(source,dest) == false)
		{
			printf("error\n");
			return -1;
		}
		else
		{
			printf("Done\n");
		}
		
	}
	else if( iflag == 0 && fflag == 1 )
	{
		if(f(source,dest) == false)
		{
			printf("error\n");
			return -1;
		}
		else
		{
			printf("Done\n");
		}
	}
	else if( iflag == 1 && fflag == 0 )
	{
		if(i(source,dest) == false)
		{
			printf("error\n");
			return -1;
		}
		else
		{
			printf("Done\n");
		}
	}
	else if( iflag == 1 && fflag == 1)
	{
		if(i_opt(source,dest) == true)
		{
			if(f(source,dest) == false)
			{ 
				printf("error\n");
				return -1;
			}
			else
			{
				printf("Done\n");
			}
		}
		else
		{
			printf("copy aborted");
		}
	}
	
	return 0;
}

// validé

bool base(char source_file[20], char dest_file[20])
{
	FILE *source , *target;
	
	source = fopen(source_file,"r");
	if(source == NULL)
	{
		return false;
	}
	
	target = fopen(dest_file,"w");
	if(target == NULL)
	{
		fclose(source);
		return false;
	}
	
	int data;
	while(1)
   {
      data = fgetc(source);
      if( feof(source) )
      {
         break ;
      }
     fputc(data,target);
   }
	
	fclose(source);
	fclose(target);
	//printf("base ok \n");
	
	return true;
}

// à valider
bool f(char source_file[20], char dest_file[20])
{
	FILE *source , *target;
	bool result = false;
	
	source = fopen(source_file,"r");
	if(source == NULL)
	{
		
		return false;
	}
	
	target = fopen(dest_file,"r");
	if(target == NULL)
	{		
		target = fopen(dest_file,"w");
		if(target != NULL)
		{
			result = base(source_file,dest_file);
		}
		else
		{
			result = false;
		}
		return result;
	}
	else
	{
		fclose(target);
		result = base(source_file,dest_file);
		if(result == false)
		{
			int del = 0;
			//target = fopen(dest_file,"w");
			
			del = remove(dest_file);
			if(del == 0)
			{
				result = base(source_file,dest_file);
			}
			else
			{
				result = false;
			}
			
		}
		return result;
	}
	
	
	
}

bool i_opt (char source_file[20], char dest_file[20])
{
	FILE *source , *target;
	
	target = fopen(dest_file,"r");
	if(target == NULL)
	{
		
		bool result= false ;
		
		//printf("target null \n");
		
		//result = base(source_file,dest_file);
		
		return true;
		
	}
	else
	{
		char ans[3]={0};
		fclose(target);
		printf("Voulez-vous ecraser le fichier existant? \n y/n ");
		scanf("%s", ans);
		int state = 0;
		
		while((ans[0] != 'y') && (ans[0] != 'n'))
		{
			printf("Veuillez rentrer y ou n.\n");
			scanf("%s", ans);
		}
			
		if(ans[0] == 'y')
		{		
			
			bool result;
			
			//result = base(source_file,dest_file);
			
			return true; 
						
		}
		else
		{
			fclose(source);
			return false;
		}
		
	}
}


//validé
bool i(char source_file[20], char dest_file[20])
{
	
	FILE *source , *target;
	
	source = fopen(source_file,"r");
	if(source == NULL)
	{
		return false;
	}
	
	
	target = fopen(dest_file,"r");
	if(target == NULL)
	{
		
		bool result= false ;
		
		//printf("target null \n");
		
		result = base(source_file,dest_file);
		
		return result;
		
	}
	else
	{
		char ans[3]={0};
		fclose(target);
		printf("Voulez-vous ecraser le fichier existant? \n y/n ");
		scanf("%s", ans);
		int state = 0;
		
		while((ans[0] != 'y') && (ans[0] != 'n'))
		{
			printf("Veuillez rentrer y ou n.\n");
			scanf("%s", ans);
		}
			
		if(ans[0] == 'y')
		{		
			
			bool result;
			
			result = base(source_file,dest_file);
			
			return result; 
						
		}
		else
		{
			fclose(source);
			return true;
		}
		
	}
	
}
