tp2: main.o auxfunc.o cities.o graph.o
	gcc main.o auxfunc.o cities.o graph.o -o tp2 -lm

auxfunc.o: src/auxfunc.c include/auxfunc.h 
	gcc -c src/auxfunc.c -lm

cities.o: src/cities.c include/cities.h
	gcc -c src/cities.c -lm

graph.o: src/graph.c include/graph.h
	gcc -c src/graph.c -lm

main.o: main.c
	gcc -c main.c -lm

.PHONY: clean

clean:
	rm main.o auxfunc.o graph.o cities.o
