#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @file ordenacao.c
 * @brief Ordenação de nomes utilizando shell_sort.
 *
 * Esse script ordena os nomes por ordem alfabética em uma lista
 * utilizando o algoritmo shell_sort.
 *
 * @author erikgabriel07
 * @date 17 de Abril de 2025
 */

void shell_sort(char *vet[], int size) {
	char *value;
	
	int h = 1, i, j;
	while (h < size) {
		h = (3 * h) + 1;
	}
	
	while (h > 0) {
		for (i = h; i < size; i++) {
			value = vet[i];
			j = i;
			
			while (j >= h && strcmp(vet[j - h], value) > 0) {
				vet[j] = vet[j - h];
				j = j - h;
			}
			
			vet[j] = value;
		}
		h /= 3;
	}
}

int main() {
	
	char *nomes[] = {
		"Jonas Cavalcanti", "Ronaldo Canto", "Luciana Almeida", "Maria Aguiar",
		"Diogo Miranda", "Breno Ruiz", "Norberto Magalhaes", "Maria Vidal",
		"Ana Barroso", "Jessica Dias"
	};
	
	int tamanho = (int)sizeof(nomes) / sizeof(nomes[0]);
	
	printf("DESORDENADA:\n");
	for (int i = 0; i < tamanho; i++) {
		printf("%s\n", nomes[i]);
	}
	printf("\n");
	
	shell_sort(nomes, tamanho);
	
	printf("ORDENADA:\n");
	for (int i = 0; i < tamanho; i++) {
		printf("%s\n", nomes[i]);
	}
	
	return 0;
}