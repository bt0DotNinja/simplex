#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <gmp.h>
/*
 * 
 *
 */
int baseValida(int *,int,int);
void printSal(mpq_t **,int *,int,int);
int factible(mpq_t **,int,int);
int pivoteo(mpq_t **,int,int,int,int);
void bland(mpq_t **,int,int,int*,int*);
int selEntrada(mpq_t **,int,int);
int selSalida(mpq_t **,int,int,int);

int main(int argc,char **argv){

	int i,j,m,n,entra,sale;
	char tmp[4098],flag=0;

	scanf("%d %d",&m,&n);
	if(m>=n){
		printf("M >= N");
		return 1;
	}
	mpq_t **Tableau;
	int base[m];

	// generar tableau
	Tableau = (mpq_t **) malloc((m+1)*sizeof(mpq_t *));
	for(i=0;i<=m;i++){
		Tableau[i]= (mpq_t *)malloc((n+1)*sizeof(mpq_t));
		for(j=0;j<=n;j++)
			mpq_init(Tableau[i][j]);
	}

	//Leer Problema
	for(i=0;i<n;i++){
		scanf("%s",&tmp);
		mpq_set_str(Tableau[0][i],tmp,0);
		mpq_canonicalize(Tableau[0][i]);
	}

	for(i=1;i<=m;i++){
		scanf("%s",&tmp);
		mpq_set_str(Tableau[i][n],tmp,0);
		mpq_canonicalize(Tableau[i][n]);
	}

	for(i=0;i<m;i++){
		scanf("%d",&base[i]);
		printf("%d ",base[i]);
	}
	printf("\n");
	if(!baseValida(base,m,n)){
		printf("Base inicial no valida\n");
		return 2;
	}

	for(i=1;i<=m;i++){
		for(j=0;j<n;j++){
			scanf("%s",&tmp);
			mpq_set_str(Tableau[i][j],tmp,0);
			mpq_canonicalize(Tableau[i][j]);
		}
	}
	//revisar base
	
	for(i=1;i<=m;i++){
		if(pivoteo(Tableau,m,n,i,base[i-1]-1)==-1){
			flag=1;
			break;
		}
	}
	printSal(Tableau,base,m,n);
		
	if(!factible(Tableau,m,n) || flag){
		printf("Base inicial infactible\n");
		return 4;
	}
	
	while(1){
		entra=selEntrada(Tableau, m,n);
		if(entra==-1){
			printSal(Tableau,base,m,n);
			printf("Base final optima\n");
			break;
		}
		sale=selSalida(Tableau,m,n,entra);
		if(sale==-1){
			printSal(Tableau,base,m,n);
			printf("No acotamiento\n");
			break;
		}
		if(mpq_sgn(Tableau[sale][n]) == 0)
			bland(Tableau,m,n,&sale,&entra);
		base[sale - 1]=entra;
		pivoteo(Tableau,m,n,sale,entra);
		printSal(Tableau,base,m,n);
		
	}
	//limpiar variables
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++)
			mpq_clear(Tableau[i][j]);
		free(Tableau[i]);
	}
	free(Tableau);
return 0;
}

int factible(mpq_t **A,int m, int n){//done
	int i; 
	for(i=1;i<=m;i++)
		if(mpq_sgn(A[i][n]) == -1) return 0;
	return 1;
}

void printSal(mpq_t **A,int *base,int m,int n){// modificar
	int i,j;
	for(i=0;i<m;i++)
		printf("%d ", base[i]);	
	for(i=1;i<=m;i++)
		gmp_printf("%Qd ",A[base[i-1]][n]);
	gmp_printf("%Qd\n\n",A[0][n]);
			
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++)
			gmp_printf("%Qd ",A[i][j]);
		printf("\n");
	}
	printf("\n");
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
	mpq_inits(factor,tmp,NULL);
	if(mpq_cmp(A[vSale][vEntra],factor) != 0){
		mpq_inv(factor, A[vSale][vEntra]);
	}
	else{ 
		mpq_clears(factor,tmp,NULL);
		return -1;
	}
	for(i=0;i<=n;i++)
		mpq_mul(A[vSale][i],factor,A[vSale][i]);
	for(i=0;i<=m;i++){
		if(vSale == i) continue;
		mpq_set(factor,A[i][vEntra]);
		for(j=0;j<=n;j++){
			mpq_mul(tmp,factor,A[vSale][j]);
			mpq_sub(A[i][j],A[i][j],tmp);		
		}
	}
	mpq_clears(factor,tmp,NULL);
	return 0;
}
void bland(mpq_t **A,int m,int n,int *vSale,int *vEntra){
	int i,j;
	for(i=0;i<n;i++)
		if(mpq_sgn(A[0][i]) < 0){
			*vEntra=i;
			break;
		}
	for(j=1;j<=m;j++)
		if(mpq_sgn(A[j][i]) > 0){
			*vSale=j;
			break;
		}
}
int selEntrada(mpq_t **A,int m,int n){
	int i, ind=0;
	mpq_t minimo;
	mpq_init(minimo);
	mpq_set(minimo,A[0][0]);
	for(i=1;i<n;i++){
		if(mpq_cmp(minimo,A[0][i])>0){
			mpq_set(minimo,A[0][i]);
			ind=i;
		}
	}
	if(mpq_sgn(minimo) >= 0)
		ind=-1; //optimo
	mpq_clear(minimo);
	return ind;
}
int selSalida(mpq_t **A,int m, int n, int vEntra){
	int i,ind=-1; //no acotado
	for(i=1;i<=m;i++)
		if(mpq_sgn(A[i][vEntra]) > 0){
			ind=i;
			break;
		}
	return ind;
}
