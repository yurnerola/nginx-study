#include "crs_setproctitle.h"

extern char **environ;
extern char **crs_os_argv;

int main(int argc,char** argv)
{
	crs_os_argv=argv;
	crs_init_setproctitle();
	crs_setproctitle("crs_setproctitle test......");
	int i=0;
	for(i=0;environ[i];i++)
	{
		printf("environ[%d]:%s\n",i,environ[i]);
	}
	getchar();
	return 0;
}
