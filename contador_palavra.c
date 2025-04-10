#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int contar(const char *texto, const char *palavra) {
	char temp[100] = {};
	int counter = 0;
	int len_texto = strlen(texto);
	
	for (int i = 0; i < len_texto + 1; i++) {
		if (strcmp(temp, palavra) == 0) {
			temp[0] = '\0';
			counter++;
		} else if (texto[i] == ' ') {
			strcpy(temp, "");
		} else {
			char c_temp[2] = {texto[i], '\0'};
			strcat(temp, c_temp);
		}
	}
	return counter;
}

int main() {
	
	char texto[25] = "cara caramba, cara carao";
	
	char palavra[5] = "cara";
	
	printf("TEXTO: %s\nPALAVRA: %s\n", texto, palavra);
	
	printf("CONTAGEM de '%s': %d\n", palavra, contar(texto, palavra));
	
	return 0;
}