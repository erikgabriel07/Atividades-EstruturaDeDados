#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct _Aluno {
	int matricula;
	char nome[100];
	char curso[100];
	char endereco[100];
	bool ativo;
	struct _Aluno *proximo;
	struct _Aluno *anterior;
} Aluno;

typedef struct _Registro {
	Aluno *inicio;
	Aluno *fim;
	int qtd_alunos;
} Registro;

void liberar(Registro **registro) {
	if (!(*registro)) return;
	
	Aluno *current = (*registro)->inicio;
	Aluno *temp;
	
	while (current) {
		temp = current->proximo;
		free(current);
		current = temp;
	}
	free(*registro);
	*registro = NULL;
}

void relatorio(Registro *registro) {
	if (!registro || !registro->inicio) return;
	
	Aluno *current = registro->inicio;
	
	printf("\n============== RELATORIO ==============\n");
	while (current && current->ativo) {
		printf("MATRICULA: %d\n", current->matricula);
		printf("NOME     : %s\n", current->nome);
		printf("CURSO    : %s\n", current->curso);
		printf("ENDERECO : %s\n", current->endereco);
		printf("=======================================\n");
		current = current->proximo;
	}
	printf("QUANTIDADE DE REGISTROS: %d", registro->qtd_alunos);
}

void cadastrar_aluno(int matricula, const char *nome, const char *curso, const char *endereco, Registro **registro) {
	if (!(*registro)) {
		*registro = (Registro *)malloc(sizeof(Registro));
		(*registro)->inicio = NULL;
		(*registro)->fim = NULL;
		(*registro)->qtd_alunos = 0;
	}
	
	Aluno *novo_aluno = (Aluno *)malloc(sizeof(Aluno));
	novo_aluno->matricula = matricula;
	strcpy(novo_aluno->nome, nome);
	strcpy(novo_aluno->curso, curso);
	strcpy(novo_aluno->endereco, endereco);
	novo_aluno->ativo = true;
	novo_aluno->proximo = NULL;
	novo_aluno->anterior = NULL;
	
	if (!(*registro)->fim) {
		(*registro)->inicio = novo_aluno;
		(*registro)->fim = novo_aluno;
	} else {
		novo_aluno->proximo = (*registro)->inicio;
		(*registro)->inicio->anterior = novo_aluno;
		(*registro)->inicio = novo_aluno;
	}
	(*registro)->qtd_alunos++;
	
	printf("Aluno cadastrado com sucesso!\n");
}

void remover_aluno(int matricula, Registro **registro) {
	if (!(*registro) || !(*registro)->inicio) return;
	
	Aluno *current = (*registro)->inicio;
	
	for (current; current && current->matricula != matricula; current = current->proximo);
	
	if (!current) {
		printf("Aluno nao encontrado no registro!\n");
		return;
	}
	
	// Marcando como F e jogando para o fim da lista para otimizar outros processos como relatório de alunos e outras funções
	current->ativo = false;
	
	if ((*registro)->fim != current) {
		if ((*registro)->inicio != current) {
			current->anterior->proximo = current->proximo;
			current->proximo->anterior = current->anterior;
			current->proximo = NULL;	
		} else {
			(*registro)->inicio = current->proximo;
			current->proximo->anterior = NULL;
			current->proximo = NULL;
		}
		
		current->anterior = (*registro)->fim;
		(*registro)->fim->proximo = current;
		(*registro)->fim = current;
	}
	
	(*registro)->qtd_alunos--;
	printf("Aluno com matricula '%d' removido com sucesso!\n", matricula);
}

void alterar_curso(int matricula, const char *novo_curso, Registro *registro) {
	if (!registro || !registro->inicio) return;
	
	Aluno *current = registro->inicio;
	
	for (current; current && current->matricula != matricula && current->ativo; current = current->proximo);
	
	if (!current) {
		printf("Aluno nao encontrado no registro!\n");
		return;
	}
	
	strcpy(current->curso, novo_curso);
	
	printf("Curso do aluno alterado com sucesso!\n");
}

void alterar_endereco(int matricula, const char *novo_endereco, Registro *registro) {
	if (!registro || !registro->inicio) return;
	
	Aluno *current = registro->inicio;
	
	for (current; current && current->matricula != matricula && current->ativo; current = current->proximo);
	
	if (!current) {
		printf("Aluno nao encontrado no registro!\n");
		return;
	}
	
	strcpy(current->endereco, novo_endereco);
	
	printf("Endereco do aluno alterado com sucesso!\n");
}

int main() {
	
	Registro *registro = NULL;
	
	cadastrar_aluno(1000, "Erik", "ADS", "Rua 1", &registro);
	cadastrar_aluno(1001, "Jonas", "Educacao Fisica", "Rua 2", &registro);
	cadastrar_aluno(1002, "Ana", "Psicologia", "Rua 3", &registro);
	cadastrar_aluno(1003, "Paula", "Pedagogia", "Rua 4", &registro);
	
	int opcao = -1;
	
	int matricula = 0;
	char nome[100] = {};
	char curso[100] = {};
	char endereco[100] = {};
	
	while (opcao != 0) {
		printf("\n========== MENU ==========\n");
		printf("[1] Cadastrar \n");
		printf("[2] Remover\n");
		printf("[3] Relatorio\n");
		printf("[4] Alterar curso\n");
		printf("[5] Alterar endereco\n");
		printf("[0] Sair\n");
		printf("opcao: ");
		scanf(" %d", &opcao);
		
		while (getchar() != '\n');
		
		switch (opcao) {
			case 1:
				printf("MATRICULA: ");
				scanf(" %d", &matricula);
				while (getchar() != '\n');
				
				printf("NOME     : ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome, "\n")] = '\0';
				
				printf("CURSO    : ");
				fgets(curso, sizeof(curso), stdin);
				curso[strcspn(curso, "\n")] = '\0';
				
				printf("ENDERECO : ");
				fgets(endereco, sizeof(endereco), stdin);
				endereco[strcspn(endereco, "\n")] = '\0';
				
				cadastrar_aluno(matricula, nome, curso, endereco, &registro);
				
				break;
			case 2:
				printf("MATRICULA: ");
				scanf(" %d", &matricula);
				while (getchar() != '\n');
				
				remover_aluno(matricula, &registro);
				
				break;
			case 3:
				relatorio(registro);
				break;
			case 4:
				printf("MATRICULA: ");
				scanf(" %d", &matricula);
				while (getchar() != '\n');
				
				printf("CURSO    : ");
				fgets(curso, sizeof(curso), stdin);
				curso[strcspn(curso, "\n")] = '\0';
				
				alterar_curso(matricula, curso, registro);
				
				break;
			case 5:
				printf("MATRICULA: ");
				scanf(" %d", &matricula);
				while (getchar() != '\n');
				
				printf("ENDERECO : ");
				fgets(endereco, sizeof(endereco), stdin);
				endereco[strcspn(endereco, "\n")] = '\0';
				
				alterar_endereco(matricula, endereco, registro);
				
				break;
			case 0:
				printf("Saindo do programa...\n");
				break;
			default:
				printf("Opcao invalida!\n");
				break;
		}
	}
	
	liberar(&registro);
	
	return 0;
}