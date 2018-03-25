#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <gmp.h>
/*
 * 
 *
 */
int baseValida(int *,int,int);
void printSal(mpq_t **,int *,mpq_t,int,int);
int factible(mpq_t *,int);
int pivoteo(mpq_t **,int,int,int,int);

int main(int argc,char **argv){

	int i,j,m,n,flag=0;
	char tmp[4098];

	scanf("%d %d",&m,&n);
	if(m>=n){
		printf("M >= N");
		return 1;
	}
	mpq_t **Tableau, C[n], b[m], z;
	int base[m];

	Tableau = (mpq_t **) malloc(m*sizeof(mpq_t *));
	mpq_init(z);
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
	}

	for(i=0;i<m;i++)
		scanf("%d",&base[i]);

	if(!baseValida(base,m,n)){
		printf("Base inicial no valida\n");
		return 2;
	}

	for(i=0;i<m;i++){
		Tableau[i]= (mpq_t *)malloc(n*sizeof(mpq_t));
		for(j=0;j<n;j++){
			mpq_init(Tableau[i][j]);
			scanf("%s",&tmp);
			mpq_set_str(Tableau[i][j],tmp,0);
			mpq_canonicalize(Tableau[i][j]);
		}
	}

	//revisar base
	
	for(i=0;i<m;i++)
		if(pivoteo(Tableau,m,n,i,base[i])==-1){
			printf("Base linealmente dependiente\n");
			return 3;
		}
			
	
	printSal(Tableau,base,z,m,n);

	if(!factible(b,m)){
		printf("Base inicial infactible\n");
		return 4;
	}


	





	
























	//limpiar variables
	for(i=0;i<n;i++) 
		mpq_clear(C[i]);
	for(i=0;i<m;i++) 
		mpq_clear(b[i]);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			mpq_clear(Tableau[i][j]);
return 0;
}

int factible(mpq_t *B,int m){//done
	int i; 
	for(i=0;i<m;i++)
		if(mpq_sgn(B[i]) == -1) return 0;
	return 1;
}

void printSal(mpq_t **A,int *base,mpq_t z,int m,int n){// modificar
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			gmp_printf("%Qd ",A[i][j]);
		printf("\n");
	}
}
int baseValida(int *b, int m, int n){//done
	int i,*bin = (int *) malloc(m*sizeof(int));
	bzero(bin,m);
	for(i=0;i<m;i++){
		if(b[i] <= n && b[i]>0) //No sobrepasa el rango valido
			bin[b[i] - 1]++;
		else{
			free(bin);
			return 0;
		}
	}
	for(i=0;i<m;i++)
		if(bin[i]>1){
			free(bin);
			return 0;
		}
	free(bin);
	return 1;
}
int pivoteo(mpq_t **A,int m,int n,int vSale,int vEntra){
	int i,j;
	mpq_t factor,tmp;
	mpq_inits(factor,tmp);
	if(mpq_cmp(A[vSale][vEntra],factor) != 0)
		mpq_inv(factor, A[vSale][vEntra]);
	else{ 
		mpq_clear(factor);
		return -1;
	}
	for(i=0;i<n;i++)
		mpq_mul(A[vSale][i],A[vSale][i],factor);
	for(i=0;i<m;i++){
		if(i == vSale) continue;
		mpq_neg(factor,A[i][vEntra]);
		for(j=0;j<n;j++){
			mpq_mul(tmp,factor,A[i][j]);
			mpq_add(A[i][j],A[i][j],tmp);		
		}
	}
	mpq_clears(factor,tmp);
	return 0;
}
