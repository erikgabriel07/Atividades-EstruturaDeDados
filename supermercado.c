#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMANHO_MAXIMO 10

typedef struct _Produto {
	char nome[100];
	char segmento[100];
	double preco_compra;
	double preco_venda;
	char unidade_comercial[10];
	int quantidade_estoque;
	struct _Produto *proximo;
	struct _Produto *anterior;
} Produto;

typedef struct _Supermercado {
	Produto *inicio;
	Produto *fim;
	int tamanho;
} Supermercado;

void liberar(Supermercado **supermercado) {
	if (!(*supermercado)) return;
	
	Produto *temp;
	Produto *current = (*supermercado)->inicio;
	
	while (current) {
		temp = current->proximo;
		free(current);
		current = temp;
	}
	free(*supermercado);
	*supermercado = NULL;
}

void relatorio(Supermercado *supermercado) {
	if (!supermercado || !supermercado->inicio) return;
	
	Produto *current = supermercado->inicio; // ou "supermercado->fim" para começar a listagem do último ao primeiro elemento
	
	printf("\n============== RELATORIO ==============\n");
	while (current) {
		printf("NOME         : %s\n", current->nome);
		printf("SEGMENTO     : %s\n", current->segmento);
		printf("PRECO COMPRA : R$%.2f\n", current->preco_compra);
		printf("PRECO VENDA  : R$%.2f\n", current->preco_venda);
		printf("UN. COMERCIAL: %s\n", current->unidade_comercial);
		printf("QUANTIDADE   : %d\n", current->quantidade_estoque);
		printf("=======================================\n");
		current = current->proximo; // ou "supermercado->anterior" para listar na ordem em que os elementos foram inseridos
	}
}

void inserir_produto(const char *nome, const char *segmento, double preco_compra,
					double preco_venda, const char *unidade_comercial,
					int quantidade_estoque, Supermercado **supermercado) {
	if (!(*supermercado)) {
		*supermercado = (Supermercado *)malloc(sizeof(Supermercado));
		(*supermercado)->inicio = NULL;
		(*supermercado)->fim = NULL;
		(*supermercado)->tamanho = 0;
	}
	
	if ((*supermercado)->tamanho == TAMANHO_MAXIMO) {
		printf("Nao e possivel adicionar mais itens!\n");
		return;
	}
	
	Produto *novo_produto = (Produto *)malloc(sizeof(Produto));
	strcpy(novo_produto->nome, nome);
	strcpy(novo_produto->segmento, segmento);
	novo_produto->preco_compra = preco_compra;
	novo_produto->preco_venda = preco_venda;
	strcpy(novo_produto->unidade_comercial, unidade_comercial);
	novo_produto->quantidade_estoque = quantidade_estoque;
	novo_produto->proximo = NULL;
	novo_produto->anterior = NULL;
	
	if (!(*supermercado)->fim) {
		(*supermercado)->inicio = novo_produto;
		(*supermercado)->fim = novo_produto;
	} else {
		novo_produto->proximo = (*supermercado)->inicio;
		(*supermercado)->inicio->anterior = novo_produto;
		(*supermercado)->inicio = novo_produto;
	}
	(*supermercado)->tamanho++;
	
	printf("Novo produto inserido com sucesso!\n");
}

int main() {
	
	Supermercado *supermercado = NULL;

	// Produtos previamente inseridos a fim de facilitar os testes do programa
	inserir_produto("Detergente Neutro", "Limpeza", 1.50, 3.20, "L", 120, &supermercado);
	inserir_produto("Carrinho de Controle Remoto", "Brinquedo", 55.00, 99.90, "un", 15, &supermercado);
	inserir_produto("Arroz Integral", "Alimento", 4.80, 7.50, "kg", 80, &supermercado);
	inserir_produto("Shampoo Anticaspa", "Higiene", 6.90, 12.00, "L", 45, &supermercado);
	inserir_produto("Papel A4 Sulfite", "Papelaria", 9.00, 16.50, "un", 200, &supermercado);
	inserir_produto("Cafe Torrado e Moido", "Alimento", 8.75, 14.00, "kg", 60, &supermercado);
	
	// Adicionando os 4 produtos restantes para concluir o programa e o exercício
	printf("\nBEM-VINDO! INSIRA OS NOVOS PRODUTOS!\n\n");
	while (supermercado->tamanho < TAMANHO_MAXIMO) {
		char nome[100] = {};
		char segmento[100] = {};
		double preco_compra = 0;
		double preco_venda = 0;
		char unidade_comercial[10] = {};
		int quantidade_estoque = 0;
		
		printf("\nNOME             : ");
		fgets(nome, sizeof(nome), stdin);
		nome[strcspn(nome, "\n")] = '\0';
		
		printf("SEGMENTO         : ");
		fgets(segmento, sizeof(segmento), stdin);
		segmento[strcspn(segmento, "\n")] = '\0';
		
		printf("PRECO COMPRA     : ");
		scanf("%lf", &preco_compra);
		while (getchar() != '\n');
		
		printf("PRECO VENDA      : ");
		scanf("%lf", &preco_venda);
		while (getchar() != '\n');
		
		printf("UNIDADE COMERCIAL: ");
		fgets(unidade_comercial, sizeof(unidade_comercial), stdin);
		unidade_comercial[strcspn(unidade_comercial, "\n")] = '\0';
		
		printf("QUANTIDADE       : ");
		scanf("%d", &quantidade_estoque);
		while (getchar() != '\n');
		
		inserir_produto(nome, segmento, preco_compra, preco_venda, unidade_comercial, quantidade_estoque, &supermercado);
	}
	
	relatorio(supermercado);
	
	liberar(&supermercado);
	
	return 0;
}