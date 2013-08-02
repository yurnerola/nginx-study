all:crs

crs:crs_setproctitle.o crs.o
	gcc -g -o crs crs_setproctitle.o crs.o

crs.o:crs.c
	gcc -c -g -I. -o crs.o crs.c
	
setproctitle.o:setproctitle.c
	gcc -c -g -I. -o crs_setproctitle.o crs_setproctitle.c

.PHONY:clean
clean:
	rm -rf *.o crs
