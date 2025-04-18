#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @file estacionamento.c
 * @brief Gerenciamento de estacionamento com duas fileiras 
 *
 * Esse código é a resolução para o desafio proposto para a
 * atividade de pilhas e filas da matéria Estrutura de Dados.
 * 
 * O código implementado nesse arquivo implementa os conceitos
 * de Pilhas e/ou Filas onde requisita-se que duas longas vagas
 * de um estacionamento onde os carros as ocupam na ordem em que
 * chegam. Ou seja, o primeiro carro a entrar é o primeiro a sair.
 *
 * Para esse cenário em questão é preferível usar uma lista encadeada
 * juntamente com uma fila. Pois isso facilita a codificação para 
 * o problema de modo que, ao usar filas para organizar os carros
 * do mais antigo ao mais recente, garante-se que a ordem de chegada
 * seja respeitada onde o carro mais próximo do início da lista é o que
 * chegou primeiro dos que estão mais para o final da lista. Para isso a
 * lista é composta por ponteiros que apontam para o início e para o final
 * da lista, onde o início é o carro que está há mais tempo e o primeiro a
 * chegar, e o final é o último a chegar, logo o mais recente.
 *
 * Com as listas encadeadas, elas garantem que a própria fila tenha seus
 * elementos ligados entre si, as vagas dos carros ligam umas as outras.
 * Cada carro pode ocupar uma vaga e cada vaga aponta para a próxima vaga
 * livre, que será ocupada pelo carro que virá logo depois.
 *
 * É verdade que, isso poderia ter sido feito apenas com duas estruturas
 * definidas: Carro e Estacionamento. Onde cada carro apontaria para o
 * próximo carro na fila de carros. O esquema usado nesse exercício é
 * apenas para tornar o código o mais próximo possível do cenário real.
 *
 * @author erikgabriel07
 * @date 17 de Abril de 2025
 */

typedef struct _Carro {
	long long int cpf;
	char nome[100];
	char marca[50];
	char modelo[50];
	char placa[50];
} Carro;

typedef struct _Vaga {
	Carro carro;
	struct _Vaga *proximo;
} Vaga;

typedef struct _Estacionamento {
	Vaga *inicio_01;
	Vaga *fim_01;
	Vaga *inicio_02;
	Vaga *fim_02;
} Estacionamento;

void liberar(Estacionamento **estacionamento) {
	if (!(*estacionamento)) return;
	
	Vaga *temp01, *temp02;
	Vaga *p1 = (*estacionamento)->inicio_01,
	*p2 = (*estacionamento)->inicio_02;
	
	while (p1) {
		temp01 = p1->proximo;
		free(p1);
		p1 = temp01;
	}
	
	while (p2) {
		temp02 = p2->proximo;
		free(p2);
		p2 = temp02;
	}
	
	p1 = NULL;
	p2 = NULL;
	(*estacionamento)->fim_01 = NULL;
	(*estacionamento)->fim_02 = NULL;
	
	free(*estacionamento);
	*estacionamento = NULL;
}

Estacionamento *initialize(void) {
	Estacionamento *p = malloc(sizeof(Estacionamento));
	p->inicio_01 = NULL;
	p->fim_01 = NULL;
	p->inicio_02 = NULL;
	p->fim_02 = NULL;
	
	return p;
}

void listar_carros(Vaga *inicio) {
	if (!inicio) {
		printf("\nNao ha carros nesta fileira!\n");
		return;
	};
	
	printf("\n========== LISTAGEM ==========\n");
	while (inicio) {
		printf("CPF         : %lld\n", inicio->carro.cpf);
		printf("PROPRIETARIO: %s\n", inicio->carro.nome);
		printf("MARCA       : %s\n", inicio->carro.marca);
		printf("MODELO      : %s\n", inicio->carro.modelo);
		printf("PLACA       : %s\n", inicio->carro.placa);
		printf("==============================\n");
		inicio = inicio->proximo;
	}
}

int adicionar_carro(long long int cpf, const char *nome, const char *marca, const char *modelo, const char *placa, Vaga **inicio, Vaga **fim) {
	Vaga *nova_vaga = malloc(sizeof(Vaga));
	nova_vaga->carro.cpf = cpf;
	strcpy(nova_vaga->carro.nome, nome);
	strcpy(nova_vaga->carro.marca, marca);
	strcpy(nova_vaga->carro.modelo, modelo);
	strcpy(nova_vaga->carro.placa, placa);
	nova_vaga->proximo = NULL;
	
	if (!(*fim)) {
		*inicio = nova_vaga;
		*fim = nova_vaga;
	} else {
		(*fim)->proximo = nova_vaga;
		*fim = nova_vaga;
	}
	
	printf("\nCarro inserido com sucesso na nova vaga!\n");
	
	return 1;
}

int remover_carro(Vaga **inicio, Vaga **fim) {
	if (!(*inicio)) {
		printf("\nA fileira de carros esta vazia!\n");
		return 0;
	}
	
	Vaga *delete = *inicio;
	
	*inicio = delete->proximo;
	
	if (delete == *fim) *fim = NULL;
	
	printf("\nRemovendo carro do estacionamento...\n");
	printf("CARRO: %s %s (PLACA: %s)\n", delete->carro.marca, delete->carro.modelo, delete->carro.placa);
	printf("Proprietario: %s\n", delete->carro.nome);
	
	free(delete);
	delete = NULL;
	
	return 1;
}

int main () {
	
	Estacionamento *estacionamento = initialize();
	
	/* Para fins de teste */
	adicionar_carro(12345678901, "Joao da Silva", "Civic", "Honda", "ABC1A23", &estacionamento->inicio_01, &estacionamento->fim_01);
	adicionar_carro(23456789012, "Maria Oliveira", "Onix", "Chevrolet", "DEF4B56", &estacionamento->inicio_01, &estacionamento->fim_01);
	adicionar_carro(34567890123, "Carlos Pereira", "Corolla", "Toyota", "GHI7C89", &estacionamento->inicio_01, &estacionamento->fim_01);
	adicionar_carro(45678901234, "Ana Souza", "HB20", "Hyundai", "JKL0D12", &estacionamento->inicio_01, &estacionamento->fim_01);
	adicionar_carro(56789012345, "Lucas Lima", "Fiesta", "Ford", "MNO3E45", &estacionamento->inicio_01, &estacionamento->fim_01);
	adicionar_carro(67890123456, "Fernanda Costa", "Argo", "Fiat", "PQR6F78", &estacionamento->inicio_01, &estacionamento->fim_01);
	
	int opcao = -1;
	long long int cpf;
	unsigned int fila_vagas;
	char nome[100], marca[50], modelo[50], placa[50];
	
	while (opcao != 0) {
		opcao = -1, cpf = 0, fila_vagas = 0;
		nome[0] = '\0', marca[0] = '\0', modelo[0] = '\0', placa[0] = '\0';
		
		printf("\n---------- MENU ----------\n");
		printf("[1] Adicionar carro\n");
		printf("[2] Remover carro\n");
		printf("[3] Listar carros\n");
		printf("[0] Sair\n");
		printf("\nSUA ESCOLHA: ");
		scanf("%d", &opcao);
		
		while (getchar() != '\n');
		
		if (opcao > 0 && opcao < 4) {
			printf("Escolha a fila de vagas (1 ou 2): ");
			
			scanf("%u", &fila_vagas);
			while (fila_vagas > 2) {
				printf("Digite 1 ou 2: ");
				scanf("%u", &fila_vagas);
			}
			
			while (getchar() != '\n');
		}
		
		switch (opcao) {
			case 1:
				printf("CPF: ");
				scanf("%lld", &cpf);
				
				while (getchar() != '\n');
				
				printf("Proprietario (nome): ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome, "\n")] = '\0';
				
				printf("Marca: ");
				fgets(marca, sizeof(marca), stdin);
				marca[strcspn(marca, "\n")] = '\0';
				
				printf("Modelo: ");
				fgets(modelo, sizeof(modelo), stdin);
				modelo[strcspn(modelo, "\n")] = '\0';
				
				printf("Placa: ");
				fgets(placa, sizeof(placa), stdin);
				placa[strcspn(placa, "\n")] = '\0';
				
				if (fila_vagas == 1) {
					adicionar_carro(cpf, nome, marca, modelo, placa, &estacionamento->inicio_01, &estacionamento->fim_01);
				} else {
					adicionar_carro(cpf, nome, marca, modelo, placa, &estacionamento->inicio_02, &estacionamento->fim_02);
				}
				
				break;
			case 2:
				if (fila_vagas == 1) {
					remover_carro(&estacionamento->inicio_01, &estacionamento->fim_01);
				} else {
					remover_carro(&estacionamento->inicio_02, &estacionamento->fim_02);
				}
				
				break;
			case 3:
				if (fila_vagas == 1) {
					listar_carros(estacionamento->inicio_01);
				} else {
					listar_carros(estacionamento->inicio_02);
				}
				
				break;
			case 0:
				printf("Saindo do programa...\n");
				break;
			default:
				printf("Opcao invalida!\n");
				break;
		}
	}
	
	liberar(&estacionamento);
	
	return 0;
}