dfb: dfb.o
	g++ -o dfb dfb.o  -L/usr/lib/i386-linux-gnu -ldirectfb

dfb.o: dfb.c
	g++ -c dfb.c -I/usr/include -I/usr/include/directfb 

clean:
	rm dfb *.o

