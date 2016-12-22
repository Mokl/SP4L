// -b -q
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include <unistd.h>
#include <utmp.h>
#include <sys/utsname.h>
#include <time.h>
#include <getopt.h>
#include <sys/sysinfo.h>



void base();
void b();
void q();
void my_uptime();

#define HOUR 3600
#define MIN 60


int main(int argc, char *argv[])
{
	int qflag=0 , bflag=0, opterr = 0;
	char * cvalue = NULL ;
	int index , c ;
	
	 struct option options[] = 
    {
        {"count", no_argument, NULL, 'q'},
        {0, 0, 0, 0}
	};
	
	while (( c = getopt_long ( argc , argv , "bq",options,NULL )) != -1)
	{	
		switch ( c ) 
		{
			case 'b':
				bflag = 1; 
				break ;
				
			case 'q':
				qflag = 1; 
				break ;
				
			case '?':
				break;
				
			default :
			abort ();
		}
	}
	if( bflag == 0 && qflag == 0)
	{
		base();
	}
	else if( bflag == 0 && qflag == 1)
	{
		q();
	}
	else if( bflag == 1 && qflag == 0)
	{
		b();
	}
	return 0;
}

void base()
{
	struct utmp *n;
    char a[256];
    int i;
	time_t  curr_time, start_time;
	struct tm *y2k;
	char date[20];
	
    setutent();
    n=getutent();
    while(n!=NULL)
    {
        if(n->ut_type==7)
        {
            printf("%-9s",n->ut_user);//user name
            printf("%-12s",n->ut_line);//
			
			//computation of the logging date and hour
			curr_time = time(NULL);
			start_time =n->ut_tv.tv_sec;
			y2k=localtime(&start_time);
			strftime(date, 20, "%F %R", y2k);
			printf("%s ",date);
			
            printf(" (");
            printf("%s",n->ut_host);
            printf(")\n");
        }
        n=getutent();
    }
	endutent();
}

void q()
{
	struct utmp *n;
    char a[256];
    int i;
    setutent();
    n=getutent();
	int user_cmp = 0;
	//printf("test\n");
    while(n!=NULL)
    {
        if(n->ut_type==7)
        {
            printf("%-9s \n",n->ut_user);
			user_cmp++;
            
        }
        n=getutent();
    }
	printf("nombre d'utilisateurs : %d\n",user_cmp);
	endutent();
}

// b option
void b()
{
	struct utmp *n;
	time_t  curr_time ,start_time;
	struct tm *y2k;
	char date[20];
	
	setutent();
    n=getutent();
    while(n!=NULL)
    {
        if(n->ut_type==7)
		{	
			//computation of the loging date and hour
			curr_time = time(NULL);
			start_time =n->ut_tv.tv_sec;
			y2k=localtime(&start_time);
			strftime(date, 20, "%F %R", y2k);
			
			printf("   démarrage du système ");


			printf("%s\n",date);
        }
        n=getutent();
    }
	endutent();
}
