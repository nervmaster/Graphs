grafo: main.o grafo.o vertice.o
	g++ -o grafo main.o grafo.o vertice.o
	
main.o: main.cpp grafo.o
	g++ -c  main.cpp
	
grafo.o: grafo.cpp grafo.h vertice.o
	g++ -c  grafo.cpp
	
vertice.o: vertice.cpp vertice.h
	g++ -c  vertice.cpp
	
clean:
	rm *.o
