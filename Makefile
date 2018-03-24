all: simplex

simplex: simplex.c
	gcc simplex.c -fopenmp -O3 -lgmp -o simplex
clean:
	rm simplex
