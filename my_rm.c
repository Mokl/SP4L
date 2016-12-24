#include <stdio.h>
#include <stdlib.h>
#include<dirent.h>
#include<string.h>
#include <unistd.h>
#include <getopt.h>

int base(char file[]);
int R(char file[]);

int main(int argc, char *argv[])
{
	int Rflag=0, rflag =0;
	int c ;
	char file[20]={0};
	
	 struct option options[] = 
    {
        {"recursive", no_argument, NULL, 'R'},
        {"recursive", no_argument, NULL, 'r'},
        {0, 0, 0, 0}
	};
	
	
	while (( c = getopt_long( argc , argv , "Rr",options,NULL)) != -1)
	{	
		switch ( c ) 
		{
			case 'R':
				Rflag = 1; 
				break ;
				
			case 'r':
				rflag = 1; 
				break ;				
				
			default :
			abort ();
		}
	}
	
	
	if (argc - optind == 0)
	{       
		printf("Veuillez donner un ficher\n");
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
				strcat(file,argv[i]);
			}
			j++;
			
			if(j>0)
			{
				break;
			}			
		}
	}
	
	if( Rflag == 0 && rflag == 0)
	{
		if(base(file) == 0)
		{
			printf("done\n");
		}
		else
		{
			printf("error\n");
		}
	}
	else 
	{
		if(R(file) == 0)
		{
			printf("done\n");
		}
		else
		{
			printf("error\n");
		}
	}
	
	
	return 0;
}

/*
	basic rm command
*/
int base(char file[])
{
	FILE *fd ;
	
	fd = fopen(file,"r");
	if(fd != NULL)
	{
		int ret;
		fclose(fd);
		ret = unlink(file);	
		if(ret == -1)
		{
			DIR *dirp = opendir(file);
			if(dirp != NULL)
			{
				closedir(dirp);
				printf("c'est un repertoire, veuillez utiliser la command rmdir.\n");
				return -1;
			}
		}
		return 	ret;
	}
	else
	{		
		printf("le fichier n'existe pas ou est utilisé dans un autre processus\n");
		return -1;		
	}
}

/*
	recursive option
*/
int R(char file[20])
{
	struct dirent *dp;
	DIR *dirp = opendir(file);
	
	if(dirp != NULL)//checking if it's a directory
	{
		while(dirp)
		{
			//deleting file and sub-directory
			if((dp = readdir(dirp)) != NULL)
			{
				//record of names
				if(dp->d_name[0]!= '.')
				{
					if(dp->d_type == DT_DIR)// checking if it's a directory
					{
						char route[50]={0};
						//creating path
						strcat(route,file);
						strcat(route,"/");
						strcat(route,dp->d_name);
						
						if(R(route) < 0)// recursive call
						{
							return -1;
						}
					}
					else
					{
						char route[50]={0};
						strcat(route,file);
						strcat(route,"/");
						strcat(route,dp->d_name);
						
						if(base(route) < 0)
						{
							return -1;
						}
					}
				}				
			}
			else
			{
				break;
			}
		}
		closedir(dirp);
		return rmdir(file);//deleting the directory
	}
	else
	{
		int ret ;
		closedir(dirp);
		
		if(base(file) < 0)
		{
			ret = rmdir(file);
		}
		else
		{
			ret = -1;
		}
		return ret ;
	}
}
