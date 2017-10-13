#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct cola{
	int valores[1000];
	int largo;
	int inicio;
};

void fcfs(struct cola direcciones);
void sstf(struct cola direcciones);
void scan(struct cola direcciones);
void clook(struct cola direcciones);
int pop(int pos, struct cola *cola );

int main(char argc, char * argv[]){
	struct cola direccion;
	direccion.largo=0;
	FILE *  input = fopen(argv[1],"rb");
	fscanf(input, "%d \n",&direccion.inicio);
	int i=0;
	while (feof(input)==0){
		fscanf(input, "%d \n",&direccion.valores[i]);
		direccion.largo++;
		i++;
	} 
	if(strcmp(argv[2], "fcfs")==0){
	fcfs(direccion);}
	if(strcmp(argv[2], "sstf")==0){
	sstf(direccion);}
	if(strcmp(argv[2], "scan")==0){
	scan(direccion);}
	if(strcmp(argv[2], "clook")==0){
	clook(direccion);}
	return 0;
}

void fcfs(struct cola direcciones){
	int modo; //0=sube 1=baja
	modo = 0;
	int movimiento;
	int siguiente;
	int cambio;
	int pos;
	int diferencia;
	movimiento = 0;
	cambio = 0;
	pos=0;
	siguiente=direcciones.inicio;
	while(direcciones.largo>0){
		if((direcciones.valores[pos]>siguiente) && (modo==1)){
			cambio++;
			modo=0;	
		}
		else if((direcciones.valores[pos]<siguiente) && (modo==0)){
			cambio++;
			modo=1;
		
		}
		diferencia=siguiente-direcciones.valores[pos];
		if(diferencia<0){
			diferencia=-1*diferencia;
		}
	 	movimiento=movimiento+diferencia;
	 	siguiente=pop(pos, &direcciones);
	 	if (direcciones.largo>0){
	 		printf("%d,",siguiente);
	 	}
	 	else{
	 		printf("%d\n",siguiente);
		}
	}
	printf("%d\n",movimiento);
	printf("%dT+%dD msec\n",movimiento,cambio);
}

 void sstf(struct cola direcciones){
 	int diferencia;
 	int minimo;
 	int pos;
	int siguiente;
	int movimiento;
	int cambio;
	int modo;
	bool primero;
	modo=0;
	cambio=0;
	movimiento=0;
	diferencia=0;
	primero=true;
 	while(direcciones.largo>0){
 		minimo=256;
 		for(int i=0;i<direcciones.largo;i++){
 			if (primero){
				diferencia = direcciones.inicio-direcciones.valores[i];
			}
 			else{
				diferencia = direcciones.valores[i]-siguiente;
			}
 			if(diferencia<0){
 				diferencia=-1*diferencia;
			}
			if(diferencia<minimo){
			  pos=i;
			  minimo=diferencia;
			}
	 	}
	 	if(primero){
	 		if(direcciones.inicio>direcciones.valores[pos]){
	 			cambio++;
			 }
		 }
		else{
			if((direcciones.valores[pos]>siguiente) && (modo==1)){
				cambio++;
				modo=0;	
			}
			else if((direcciones.valores[pos]<siguiente) && (modo==0)){
				cambio++;
				modo=1;
			}
		}
	 	movimiento=movimiento+minimo;
	 	siguiente=pop(pos, &direcciones);
	 	if (direcciones.largo>0){
	 		printf("%d,",siguiente);
	 	}
	 	else{
	 		printf("%d\n",siguiente);
		}
	 	primero=false;
	}
	printf("%d\n",movimiento);
	printf("%dT+%dD msec\n",movimiento,cambio);
	
 }

void scan(struct cola direcciones){
	int diferencia;
 	int minimo;
 	int pos;
	int siguiente;
	int movimiento;
	int cambio;
	int modo;
	bool primero;
	int nada;
	modo=0;
	cambio=0;
	movimiento=0;
	diferencia=0;
	siguiente=direcciones.inicio;
 	while(direcciones.largo>0){
 		minimo=256;
 		nada=0;
 		for(int i=0;i<direcciones.largo;i++){
 			if(modo==0 && (direcciones.valores[i]>=siguiente)){
				diferencia = direcciones.valores[i]-siguiente;
	 			if(diferencia<0){
	 				diferencia=-1*diferencia;
				}
				if(diferencia<minimo){
				  pos=i;
				  minimo=diferencia;
				}
			}
			else if(modo==1 && (direcciones.valores[i]<=siguiente)){
				diferencia = direcciones.valores[i]-siguiente;
	 			if(diferencia<0){
	 				diferencia=-1*diferencia;
				}
				if(diferencia<minimo){
				  pos=i;
				  minimo=diferencia;
				}
			}
			else{
				nada++;
			}
	 	}
	 	//cuando cambio de direccion de movimiento
	 	if(nada==direcciones.largo){
	 		cambio++;
	 		modo=1;
	 		movimiento=movimiento+(255-siguiente);
	 		siguiente=255;
		 }
		else{
		 	movimiento=movimiento+minimo;
		 	siguiente=pop(pos, &direcciones);
		 	if (direcciones.largo>0){
		 		printf("%d,",siguiente);
		 	}
		 	else{
		 		printf("%d\n",siguiente);
			}
		}
	}
	printf("%d\n",movimiento);
	printf("%dT+%dD msec\n",movimiento,cambio);
}

void clook(struct cola direcciones){
	int diferencia;
 	int minimo;
 	int pos;
	int siguiente;
	int movimiento;
	int cambio;
	int modo;
	bool primero;
	int nada;
	int final;
	bool reinicio;
	reinicio=false;
	modo=0;
	cambio=0;
	movimiento=0;
	diferencia=0;
	siguiente=direcciones.inicio;
 	while(direcciones.largo>0){
 		minimo=256;
 		nada=0;
 		for(int i=0;i<direcciones.largo;i++){
 			if(modo==0 && (direcciones.valores[i]>=siguiente)){
				diferencia = direcciones.valores[i]-siguiente;
	 			if(diferencia<0){
	 				diferencia=-1*diferencia;
				}
				if(diferencia<minimo){
				  pos=i;
				  minimo=diferencia;
				}
			}
			else{
				nada++;
			}
	 	}
	 	//cuando cambio de direccion de movimiento
	 	if(nada==direcciones.largo){
	 		cambio++;
	 		cambio++;
	 		final=siguiente;
	 		siguiente=0;
	 		reinicio=true;
		 }
		else if(reinicio){
		 	siguiente=pop(pos, &direcciones);
		 	movimiento=movimiento+(final-siguiente);
		 	if (direcciones.largo>0){
		 		printf("%d,",siguiente);
		 	}
		 	else{
		 		printf("%d\n",siguiente);
			}
			reinicio=false;
		}
		else{
		 	movimiento=movimiento+minimo;
		 	siguiente=pop(pos, &direcciones);
		 	if (direcciones.largo>0){
		 		printf("%d,",siguiente);
		 	}
		 	else{
		 		printf("%d\n",siguiente);
			}
		}
	}
	printf("%d\n",movimiento);
	printf("%dT+%dD msec\n",movimiento,cambio);
}

//funcion pra obtener el elemento en la posicion x de una cola
int pop(int pos, struct cola *cola ){
	int sacado;
	sacado = cola->valores[pos];
	for(int i = pos; i < cola->largo; i++) {
		cola->valores[i]=cola->valores[i+1];
	}
	cola->largo--;
	return sacado;
}
