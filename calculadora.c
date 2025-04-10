#include <stdio.h>

void calculadora(int v1, int v2, char operador) {
    switch (operador) {
        case '+':
            printf("\n%d + %d = %d\n", v1, v2, v1 + v2);
            break;
        case '-':
            printf("\n%d - %d = %d\n", v1, v2, v1 - v2);
            break;
        case '*':
            printf("\n%d * %d = %d\n", v1, v2, v1 * v2);
            break;
        case '/':
            printf("\n%d / %d = %.2f\n", v1, v2, (double)v1 / v2);
            break;
    }
}

int main()
{
    char opcao = {};
    
    while (opcao != 's') {
        printf("\n[p] Somar\n");
        printf("[d] Dividir\n");
        printf("[m] Subtrair\n");
        printf("[x] Multiplicar\n");
        printf("[s] Sair\n");
        printf("opcao: ");
        opcao = getchar();
        
        while (getchar() != '\n');
        int v1, v2;
        
        if (opcao != 's') {
            printf("Valor 1: ");
            scanf("%d", &v1);
            
            while (getchar() != '\n');
            
            printf("Valor 2: ");
            scanf("%d", &v2);
            
            while (getchar() != '\n');
        }
        switch (opcao) {
            case 'p':
                calculadora(v1, v2, '+');
                break;
            case 'm':
                calculadora(v1, v2, '-');
                break;
            case 'd':
                if (v2 == 0) {
                    printf("Nao e possivel dividir por zero.\n");
                } else {
                    calculadora(v1, v2, '/');
                }
                break;
            case 'x':
                calculadora(v1, v2, '*');
                break;
            case 's':
                printf("Saindo...\n");
                break;
            default:
                printf("Essa opcao nao existe...\n");
                break;
        }
    }
    return 0;
}