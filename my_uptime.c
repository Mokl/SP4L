//-p -s
#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utmp.h>
#include <sched.h>
#include <getopt.h>

#define HOUR 3600
#define MIN 60

void base();
int nb_user();
void s();
void p();

int main(int argc, char *argv[])
{
	int pflag=0 , sflag=0, opterr = 0;
	char * cvalue = NULL ;
	int index , c ;
	
	 struct option options[] = 
    {
        {"since", no_argument, NULL, 's'},
		{"pretty", no_argument, NULL, 'p'},
        {0, 0, 0, 0}
	};
	
	while (( c = getopt_long ( argc , argv , "sp",options,NULL )) != -1)
	{	
		switch ( c ) 
		{
			case 's':
				sflag = 1; 
				break ;
				
			case 'p':
				pflag = 1; 
				break ;
				
			case '?':
				break;
				
			default :
			abort ();
		}
	}
	if( sflag == 0 && pflag == 0)
	{
		base();
	}
	else if( sflag == 0 && pflag == 1)
	{
		p();
	}
	else if( sflag == 1 && pflag == 0)
	{
		s();
	}
	return 0;
}

void base()
{
	struct sysinfo info;
	int h =0 ,m =0, s=0,time_s;
	time_t curr_time;
	struct tm *y2k;
	double load[3];
	//int nb_usr;
	
	
	//current time
	curr_time = time(NULL);
	y2k = localtime(&curr_time);
	mktime(y2k);
	printf(" %.2d:%.2d:%.2d ", y2k->tm_hour , y2k->tm_min, y2k->tm_sec);

	// up time
	sysinfo(&info);
	time_s =info.uptime;	
	h = time_s/HOUR;
	s = time_s%HOUR;
	m = s/MIN;
	s %= MIN;
	printf(" up %.2d:%.2d:%.2d, ", h ,m,s);
	
	//number of user
	printf("%d user, ",nb_user());
	
	// load average
	if (getloadavg(load, 3) != -1)    
	{     
 		printf("load average : %.2f , %.2f , %.2f\n", load[0],load[1],load[2]);  
  	}	
}
//p option
void p()
{
	struct sysinfo info;
	int h =0 ,m =0, s=0,time_s;
	
	sysinfo(&info);
	time_s =info.uptime;	
	h = time_s/HOUR;
	s = time_s%HOUR;
	m = s/MIN;
	s %= MIN;
	
	printf("up %d hours, %d minutes and %d secondes\n", h,m,s);
}

// s option
void s()
{
	struct sysinfo info;
	int h =0 ,m =0, s=0,time_s;
	time_t curr_time, start_time;
	struct tm *y2k;
	char date[20];
	
	sysinfo(&info);
	
	
	curr_time = time(NULL);
	
	start_time = curr_time - info.uptime;
	
	y2k = localtime(&start_time);
	
	strftime(date,20 , "%F %T",y2k);
	
	printf("%s \n",date);	
}

int nb_user()
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
			user_cmp++;
        }
        n=getutent();
    }
	endutent();
	
	return user_cmp;
}