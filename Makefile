uname_m := $(shell uname -m)
ifeq ($(uname_m),x86_64)
all:mavx2.c
	gcc -o mavx2 mavx2.c -mavx2 
else
all:NEON.c
	gcc -o neon NEON.c

endif
