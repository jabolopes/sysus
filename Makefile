all: main intercept.so

run: main intercept.so
	LD_PRELOAD="./intercept.so" ./main

clean:
	rm -f main
	rm -f intercept.o
	rm -f intercept.so

intercept.o: intercept.c
	gcc -fPIC -c -o $@ $<

intercept.so: intercept.o
	gcc -shared -o $@ $< -ldl

main: main.c
	gcc -o $@ $<
