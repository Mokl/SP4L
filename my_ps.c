//-i -d
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include <unistd.h>
#include <sys/procfs.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void base();


int main(int argc, char *argv[])
{
	base();
	return 0;
}

void base()
{
	int fdproc;
	DIR* dir , *process;
	struct dirent *dp, *dp2,*dp3;
	char procbuf[256];	
	//struct prpsinfo pinfo; 
	
	if ((dir = opendir("/proc")) == (DIR *)NULL)
	{
   		perror("/proc");
  		exit(1);
  	} 
	
	while(dp = readdir(dir))
	{
		char pid[10]={0};
		char cmd[256]={0};
		
   		if (dp->d_name[0] != '.')
		{
			if(dp->d_type == DT_DIR)
			{
				strcpy(procbuf, "/proc/");
      			strcat(procbuf, dp->d_name);
				strcpy(pid,dp->d_name);
				strcat(procbuf,"/");
				printf("\n%s\n", procbuf);
				if ((process= opendir(procbuf)) == (DIR *)NULL)
				{
					perror(procbuf);
					exit(1);
				} 
				//printf("if ok\n");
				while(dp2 = readdir(process))
				{
					if(dp2->d_name[0] != '.')
					{
						//printf("%s\n", dp2->d_name);
						if(strcmp(dp2->d_name,"comm")!= 0)
						{
							//printf("strcop ok\n");
							FILE *buff;
							int data;
							char file[20];
							//strcpy(file,"cmdline");
							//printf("srtcpy ok\n");
							buff= fopen("comm","r");
							//printf("fopen ok\n");
							int i =0;
							if(buff)
							{
								while(1)
						   		{
							//		printf("while ok \n");
							  		data = getc(buff);
									putchar(data);
							  		if( feof(buff) )
							  		{
								 		break ;
							  		}
									i++;
									strcat(cmd,(char) data);
						   	}
							fclose(buff);
							if(strcmp(cmd,"")!= 0)
							{
								printf("\n%s\n",cmd);
							}

							}
							
							
							
						}
							
					}
				}
				
				//printf("%s \n",dp->d_name);
			}
		}
		
     	if ((fdproc = open(procbuf, O_RDONLY)) < 0)
		{
         	continue;
        } 
		
	/*	if (ioctl(fdproc, PIOCPSINFO, &pinfo) < 0) 
		{
         	close(fdproc);
        	continue;
		}*/
          
			
     }
	 close(fdproc);
	
}