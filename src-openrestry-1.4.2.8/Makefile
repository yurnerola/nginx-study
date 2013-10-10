.PHONY: all install clean

all:
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-5.1.5 && $(MAKE) linux
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-cjson-1.0.3 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-root/usr/local/openresty/lua/include LUA_LIB_DIR=/usr/local/openresty/lualib CC=gcc
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-redis-parser-0.10 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-root/usr/local/openresty/lua/include LUA_LIB_DIR=/usr/local/openresty/lualib CC=gcc
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-rds-parser-0.05 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-root/usr/local/openresty/lua/include LUA_LIB_DIR=/usr/local/openresty/lualib CC=gcc
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/nginx-1.4.2 && $(MAKE)

install: all
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-5.1.5 && $(MAKE) install INSTALL_TOP=$(DESTDIR)/usr/local/openresty/lua
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-cjson-1.0.3 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-root/usr/local/openresty/lua/include LUA_LIB_DIR=/usr/local/openresty/lualib CC=gcc
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-redis-parser-0.10 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-root/usr/local/openresty/lua/include LUA_LIB_DIR=/usr/local/openresty/lualib CC=gcc
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-rds-parser-0.05 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-root/usr/local/openresty/lua/include LUA_LIB_DIR=/usr/local/openresty/lualib CC=gcc
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-resty-dns-0.10 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=/usr/local/openresty/lualib INSTALL=/root/github/nginx-study/src-openrestry-1.4.2.8/build/install
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-resty-memcached-0.11 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=/usr/local/openresty/lualib INSTALL=/root/github/nginx-study/src-openrestry-1.4.2.8/build/install
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-resty-redis-0.15 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=/usr/local/openresty/lualib INSTALL=/root/github/nginx-study/src-openrestry-1.4.2.8/build/install
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-resty-mysql-0.13 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=/usr/local/openresty/lualib INSTALL=/root/github/nginx-study/src-openrestry-1.4.2.8/build/install
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-resty-string-0.08 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=/usr/local/openresty/lualib INSTALL=/root/github/nginx-study/src-openrestry-1.4.2.8/build/install
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/lua-resty-upload-0.08 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=/usr/local/openresty/lualib INSTALL=/root/github/nginx-study/src-openrestry-1.4.2.8/build/install
	cd /root/github/nginx-study/src-openrestry-1.4.2.8/build/nginx-1.4.2 && $(MAKE) install DESTDIR=$(DESTDIR)

clean:
	rm -rf build
