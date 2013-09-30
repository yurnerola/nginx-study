#include <stdio.h>

int ngx_get_option(int argc,char *const *argv)
{
	char *t;
	int i;
	for(i=1;i<argc;i++)
	{
		t=argv[i];
		if(*t++!='-')
		{
			printf("Wrong Argument\n");
			return 0;
		}
		while(*t)
		{	
			printf("%c",*t);
			*t++;
		}
	}
	return 1;
}

int main(int argc ,char **argv)
{	
	printf("%d\n",argc);
	printf("%s\n",argv[0]);
	ngx_get_option(argc,argv);
	return 0;
}
