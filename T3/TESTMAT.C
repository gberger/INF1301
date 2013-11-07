#include <stdio.h>
#include "MATRIZ.H"

int main (void) {
	int *resultado, i=1, vetorzao[10] = { 11,22,33,44,55,66,77,88,99,100 };
	MAT_tppMatriz pMatriz;

	i=MAT_CriarMatriz(&pMatriz, 3, NULL);
	printf("%d\n", i);
	i=MAT_AtribuirValorCorrente(pMatriz, &vetorzao[0]);
	printf("%d\n", i);
	i=MAT_AndarCorrente(pMatriz, MAT_L);
	printf("%d\n", i);
	i=MAT_AndarCorrente(pMatriz, MAT_L);
	printf("%d\n", i);
	i=MAT_AtribuirValorCorrente(pMatriz, &vetorzao[1]);
	printf("%d\n", i);
	i=MAT_AndarCorrente(pMatriz, MAT_S);
	printf("%d\n", i);
	i=MAT_AndarCorrente(pMatriz, MAT_S);
	printf("%d\n", i);
	i=MAT_AndarCorrente(pMatriz, MAT_S);
	printf("espera erro: %d\n", i);
	i=MAT_AtribuirValorCorrente(pMatriz, &vetorzao[2]);
	printf("%d\n", i);
	i=MAT_DefinirCorrente(pMatriz, 0,2);
	printf("%d\n", i);
	i=MAT_ObterValorCorrente(pMatriz, (void **)&resultado);
	printf("%d\n", i);
	printf("%d == 22\n", *resultado);
	printf("%d\n", i);
	i=MAT_DefinirCorrente(pMatriz, 2,2);
	printf("%d\n", i);
	i=MAT_ObterValorCorrente(pMatriz, (void **)&resultado);
	printf("%d\n", i);
	printf("%d == 33\n", *resultado);
	printf("%d\n", i);

	return 0;
}