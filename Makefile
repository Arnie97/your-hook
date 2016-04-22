yuge: myhook.c
	gcc -O3 -std=c99 myhook.c -lwinmm -s -o yuge

myhook.c: myhook.c.k
	milky myhook.c.k
