#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include <unistd.h>
#include <getopt.h>

typedef struct{
	 char name[1000][256];
	 int  index;
	 char opt[2];
	 int set;
 }Data;


Data base(char route[],char opt[]);
Data a(char route[], char opt[]);
void display(Data info);
Data R(char route[], char opt[]);


int main(int argc, char *argv[])
{
	int aflag=0 , lflag=0 , Rflag=0, opterr = 0;
	char * cvalue = NULL ;
	int index , c ;
	char route[256]={0};
	Data data;
	
	 struct option options[] = 
    {
        {"all", no_argument, NULL, 'a'},
        {"recursive", no_argument, NULL, 'R'},
        {0, 0, 0, 0}
	};
	
	while (( c = getopt_long ( argc , argv , " alR ",options,NULL )) != -1)
	{	
		switch ( c ) 
		{
			case 'a':
				aflag = 1; 
				break ;
				
			case 'l':
				lflag = 1; 
				break ;
				
			case 'R':
				Rflag = 1;
				break ;
				
			case '?':
				
				break;
				
			default :
			abort ();
		}
	}
	
	if (argc - optind == 0)
	{       
         strcpy(route,".");
		
	}
	else
	{
		int i ;
		
	
		for( i = optind; i < argc; i++)
		{
			strcat(route,argv[i]);		
		}
	}
	
	if( aflag == 0 && lflag == 0 && Rflag == 0)
	{
		data = base(route,"");
		display(data);
	}
	else if( aflag == 0 && lflag == 0 && Rflag == 1)
	{
		data = R(route,"");
		display(data);
	}
	else if( aflag == 0 && lflag == 1 && Rflag == 0)
	{
		data = base(route,"l");
		display(data);
	}
	else if( aflag == 0 && lflag == 1 && Rflag == 1)
	{
	
		data = R(route,"l");
		display(data);
	}
	else if( aflag == 1 && lflag == 0 && Rflag == 0)
	{
		data = a(route,"");
		display(data);
	}
	else if( aflag == 1 && lflag == 0 && Rflag == 1)
	{
		data = R(route, "a");
		display(data);
	}
	else if( aflag == 1 && lflag == 1 && Rflag == 0)
	{
		data = a(route,"l");
		display(data);
	}
	else if( aflag == 1 && lflag == 1 && Rflag == 1)
	{
		data = R(route,"al");
		display(data);
	}	
}

void display(Data info)
{
	
	int j;
	//printf("%d\n", info.set);
	if(info.set != 0)
	{
		if(info.opt[0] == 'l')
		{
			
			for(j = 0 ; j < info.index+1 ; j++)
			{
				if(info.name[j] != "" )
				{
					printf("%s\n", info.name[j]);
				}
			}
		}
		else
		{
			for(j = 0 ; j < info.index+1 ; j++)
			{
				if(info.name[j] != "" && j < info.index)
				{
					printf(" %s ", info.name[j]);
				}
				else
				{
					printf(" %s\n ", info.name[j]);
				}
			}	
		}
	}
	else
	{
		printf("no file or directory\n");
	}
	
}

Data base(char route[256], char opt[])
{

	struct dirent *dp;
	DIR *dirp = opendir(route);
	Data info;
	info.index = 0;
	//info.set = 0;
	info.opt[0] = opt[0];
	
	int i;
	for(i = 0; i< 1001;i++)
	{
	 	strcpy(info.name[i],"");
	}
	while(dirp)
	{
		if((dp = readdir(dirp)) != NULL)
		{
			//record of names
			if(dp->d_name[0]!= '.')
			{
				strcpy(info.name[info.index],dp->d_name);
				info.index++;
			}				
			if(info.set == 0)
			{
				info.set = 1;
			}
			
		}
		else
		{ 	
			break;		
		}
			
	}
	closedir(dirp);	
	return info;
}

Data a(char route[], char opt[])
{
	struct dirent *dp;
	DIR *dirp = opendir(route);
	Data info;
	info.index = 0;
	info.opt[0] = opt[0];
	info.set = 0;
	char data[1000];	
	
	int i;
	for(i = 0; i< 1001;i++)
	{
	 	strcpy(info.name[i],"");
	}

	while(dirp)
	{
		
		if((dp = readdir(dirp)) != NULL)
		{
			strcpy(info.name[info.index],dp->d_name);
			info.set = 1;
			info.index++;
		}
		else
		{ 	
			break;		
		}
			
	}
	closedir(dirp);
	return info;
}

Data R(char route[], char opt[])
{
	struct dirent *dp;
	DIR *dirp = opendir(route);
	Data info;
	info.index = 0;
	info.set = 0;
	char data[1000];	
	info.opt[0] = opt[0];

	while(dirp)
	{
		if((dp = readdir(dirp)) != NULL)
		{
			//record of names
			if(opt[0]== 'a')
			{
				strcpy(info.name[info.index],dp->d_name);
				info.index++;
				if(dp->d_type == DT_DIR)
				{
					Data info_subdir= {.index=0, .set=0 ,.opt={0} };
					int i;
					
					
					char route_subdir[260]={0};
					
					
					strcat(route_subdir,route);
					
					strcat(route_subdir,dp->d_name);
					
					strcat(route_subdir,"/");					
					info_subdir = base(route_subdir,"");
					int j;
					
					
					 for(j = info_subdir.index ; j> -1 ; j--)
					 {	
						 if(info_subdir.name[j][0] != '\0')
						 {
							char sub_item[5];
							strcpy(sub_item,"--->");
						 	strcat(sub_item,info_subdir.name[j]);
						 	strcpy(info.name[info.index],sub_item);
						 	info.index++;
						 }
						
					 }					
				}
				else
				{
					;
				}
			}
			else
			{
				if(dp->d_name[0]!= '.')
				{
					strcpy(info.name[info.index],dp->d_name);
					info.index++;
					if(dp->d_type == DT_DIR)
					{
						Data info_subdir= {.index=0, .set=0 ,.opt={0} };
						int i;


						char route_subdir[260]={0};

						strcat(route_subdir,route);
						strcat(route_subdir,dp->d_name);
						strcat(route_subdir,"/");
						info_subdir = base(route_subdir,"");
						int j;


						 for(j = info_subdir.index ; j> -1 ; j--)
						 {	
							 if(info_subdir.name[j][0] != '\0')
							 {
								char sub_item[5];
								strcpy(sub_item,"--->");
								strcat(sub_item,info_subdir.name[j]);
								strcpy(info.name[info.index],sub_item);
								info.index++;
							 }

						 }					
					}
					else
					{
						;
					}
				}
			}			
			if(info.set == 0)
			{
				info.set = 1;
			}
			
		}
		else
		{ 	
			break;		
		}
			
	}	
	if(opt[0] != '\0' && opt[1] != '\0')
	{
		info.opt[0] = opt[1];
	}
	closedir(dirp);
	return info;
}
