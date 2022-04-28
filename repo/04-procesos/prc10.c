/*
 * Ejercicio 10 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main ()
{
	int x = 100;
	
	printf("Soy el proceso: %d \n ",getpid());
	
	switch (fork())
	{
		case -1:   // No pudo crear el proceso
			printf ("Error. No se crea proceso hijo");
			break;

		case 0:   //proceso hijo
			while(1)
			printf ("Soy el proceso hijo, pid: %d , x = %d\n", getpid(), --x);
			break;

		default:  //proceso padre
			printf ("Soy el proceso padre, pid: %d , x = %d\n", getpid(), ++x);
	}
    exit(0);

}

//Como es un bucle infinito el bash no responde a las llamadas de finalización, sólo podemos matar desde otra consola al proceso con un  kill <pid del proceso hijo> y despues otro kill <pid proceso padre>. Sino se cierra el bash completo. 
