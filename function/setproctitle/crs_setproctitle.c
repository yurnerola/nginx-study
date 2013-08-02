#include "crs_setproctitle.h"

extern char **environ;
char **crs_os_argv;
char *crs_os_argv_last;

void crs_init_setproctitle()
{
 	char *p;
	int size=0;
	int i;
	for(i=0;environ[i];i++){
		size=strlen(environ[i])+size+1;
	}
	p=malloc(size);
	crs_os_argv_last=crs_os_argv[0];
	for(i=0;crs_os_argv[i];i++)
	{
		if(crs_os_argv[i]==crs_os_argv_last)
		{
			crs_os_argv_last+=strlen(crs_os_argv[i])+1;
		}
	}
	crs_os_argv_last+=size;
	crs_os_argv_last--;
	for(i=0;environ[i];i++)
	{
		memcpy(p,environ[i],strlen(environ[i])+1);
		environ[i]=p;
		p=p+strlen(environ[i])+1;
	}
}
		
void  crs_setproctitle(char *title)
{	
	int memcount=crs_os_argv_last-crs_os_argv[0];
	int titlelen=strlen(title)+1;
	if(memcount>=titlelen)
	{
		memcpy(crs_os_argv[0],title,titlelen);
		memset(crs_os_argv[0]+titlelen,' ',memcount-titlelen);
	}
	else
	{
		memcpy(crs_os_argv[0],title,memcount);
	}
}



