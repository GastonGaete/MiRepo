#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

void handler(int code){
	printf("\nSe envio SIGTERM :(\n");	
	exit(0);
}

int main(){
	int i;
	int x;
	i = 0;
	char prompt[100];
	strcpy(prompt,"Introduzca un comando");
	signal(SIGINT, handler);
	int paralelo;
	int back;
	int y;
	while(i==0){
		char * dir;
		char com[100];
		char *comando[10];
		char * path;		
		dir = "";
		path = "";
		printf("%s ", prompt);
		fgets(com, 50, stdin);
		fflush(stdin);
		back=0;
		paralelo=1;
		char * pch;
		x=0;
		pch = strtok (com," \n");
		while (pch != NULL)		
		{
		  comando[x] = pch;
		  pch = strtok (NULL, " \n");
		  x++;
		}
		x--;
		if(strcmp(comando[x], "&")==0){
			back=1;
		}
		else if(strchr(comando[x], '&')!=NULL){
			paralelo=3;
			back=1;
		}
		else{
		x++;}
		comando[x]=NULL;
		//dir = path;
		//strcat(dir, comando[0]);
		//comando[0]=dir;
		printf("%s",comando[0]); 
		if(strcmp(comando[0], "setPath")==0){			
			strcpy(path, comando[1]);
		}
		else if(strcmp(comando[0], "setPrompt")==0){
			strcpy(prompt, comando[1]);
		}
		else if(strcmp(comando[0], "exit")==0){
			i++;
		}		
		else{	
			for(y=0;y<paralelo;y++){			
				pid_t pid = fork();
						
				if(pid == 0){
					if(execvp(comando[0],comando)==-1){
						perror("exec");
					}
				}
				if (back == 0){			
					if(pid > 0){
						if(wait(0) == -1){
							perror("wait");
						}
					}
				}
			}
		}		
	}
	return 0;
}
