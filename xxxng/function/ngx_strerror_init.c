#include <stdio.h>
#include <string.h>

typedef struct {
	size_t len;
	char *data;
} ngx_str_t;

static ngx_str_t *error_list;

int ngx_strerror_init(void)
{
	int i=0;
	char *p,*q;
	error_list=malloc(135*sizeof(ngx_str_t));
	for(i=0;i<135;i++)
	{
		p=strerror(i);
		q=malloc(strlen(p));
		error_list[i].data=p;
		error_list[i].len=strlen(p);
	}
	return 1;
}

int main()
{	
	int i=0;
	ngx_strerror_init();
	for(i=0;i<135;i++)
	{
		printf("%3d--%s\n",i,error_list[i].data);
	}
	return 0;
}
