#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	int i;
	int x;
	i = 0;
	char prompt[100];
	strcpy(prompt,"Introduzca un comando");
	char comando[20];
	FILE *archivo;
	archivo = stdin;
	while(i==0){
		printf("%s ", prompt);
		fscanf(archivo, "%s", &comando);
		printf("%s\n", comando);
		if(strcmp(comando, "setPrompt")==0){
			strcpy(prompt, "Nuevo prompt");
		}
		if(strcmp(comando, "exit")==0){
			i++;
		}
	}
	return 0;
}
