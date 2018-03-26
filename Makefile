all: simplex

simplex: simplex.c
	gcc simplex.c -O3 -lgmp -o simplex
debug:
	gcc simplex.c -g -O3 -lgmp -o simplex.dbg
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./simplex.dbg < Instancias/LLN1.txt
clean:
	rm simplex
