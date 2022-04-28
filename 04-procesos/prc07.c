/*
 * Ejercicio 7 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i=2;
	
	for(i=0; i<3;i++){
	fork();	
	printf ("Cont = %d . Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n",i, getpid(), getppid(), pid);
}
	// Ejecute pstree en otra consola	
	sleep(30); 

	exit(0);

}

//Proceso padre bash (2485) crea un hijo 3974, este crea 3 hijos(3975, 3976, 3978), 3975 crea 2 hijos más (3977 y 3979), 3977 crea  3981, luego 3976 crea  3980. En total son 7 hijos creados. 
// El contador si bien llega hasta 3, ejecuta 15 lineas porque el proceso de crear un hijo lo hace sin pasar de contador, es decir, es continuo.
