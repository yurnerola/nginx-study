all:crs

crs:crs_setproctitle.o crs.o
	echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -g -o crs crs_setproctitle.o crs.o
	@echo 'Finished building target: $@'
	@echo ' '
	
crs.o:crs.c
	gcc -c -g -I. -o crs.o crs.c
	
setproctitle.o:setproctitle.c
	gcc -c -g -I. -o crs_setproctitle.o crs_setproctitle.c

.PHONY:clean
clean:
	rm -rf *.o crs
