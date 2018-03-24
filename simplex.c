#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>

void printMat(mpq_t **,int,int);

int main(int argc,char **argv){

	int i,j,m,n;
	char tmp[2048];

	scanf("%d %d",&m,&n);
	assert(m < n);


	mpq_t **Tableu;
	mpq_t C[n];
	mpq_t b[m];
	int base[m];

	Tableu = (mpq_t **) malloc(m*sizeof(mpq_t *));

	//Leer Problema
	for(i=0;i<n;i++){
		mpq_init(C[i]);
		scanf("%s",&tmp);
		mpq_set_str(C[i],tmp,0);
		mpq_canonicalize(C[i]);
	}

	for(i=0;i<m;i++){
		mpq_init(b[i]);
		scanf("%s",&tmp);
		mpq_set_str(b[i],tmp,0);
		mpq_canonicalize(b[i]);
		gmp_printf("%Qd ",b[i]);
	}


	for(i=0;i<m;i++)
		scanf("%d ",&base[i]);


	for(i=0;i<m;i++){
		Tableu[i]= (mpq_t *)malloc(n*sizeof(mpq_t));
		for(j=0;j<n;j++){
			mpq_init(Tableu[i][j]);
			scanf("%s",&tmp);
			mpq_set_str(Tableu[i][j],tmp,0);
			mpq_canonicalize(Tableu[i][j]);
		}
	}

	//
	printMat(Tableu,m,n);






































	//limpiar variables
	for(i=0;i<n;i++) 
		mpq_clear(C[i]);

	for(i=0;i<m;i++) 
		mpq_clear(b[i]);
	
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			mpq_clear(Tableu[i][j]);

return 0;
}


void printMat(mpq_t **A,int m,int n){
	int i,j;
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			gmp_printf("%Qd ",A[i][j]);
		printf("\n");
	}
}
