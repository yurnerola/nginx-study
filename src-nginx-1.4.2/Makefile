
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile
	$(MAKE) -f objs/Makefile manpage

install:
	$(MAKE) -f objs/Makefile install

upgrade:
	/root/github/nginx-study/nginx//sbin/nginx -t

	kill -USR2 `cat /root/github/nginx-study/nginx//logs/nginx.pid`
	sleep 1
	test -f /root/github/nginx-study/nginx//logs/nginx.pid.oldbin

	kill -QUIT `cat /root/github/nginx-study/nginx//logs/nginx.pid.oldbin`
