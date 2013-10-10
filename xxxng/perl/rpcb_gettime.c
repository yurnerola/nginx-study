#include <stdlib.h>
#include <rpc/rpc.h>

int main()
{
	char hostname[255] ; /* The Remote host */
	time_t        time_p = 0;

	if( rpcb_gettime(hostname, &time_p)== FALSE ) {
		fprintf(stderr,"rpcb_gettime failed");
		exit(1);          
	}
	return 0;
}
