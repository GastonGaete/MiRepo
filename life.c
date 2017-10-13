#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	sysconf(_SC_NPROCESSORS_ONLN);
}
