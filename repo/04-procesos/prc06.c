/*
 * Ejercicio 6 de TP Procesos
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
			printf ("Error. No se crea proceso hijo \n");
			break;

		case 0:   //proceso hijo
			printf ("Soy el proceso hijo, pid: %d, DirMem: %p \n\n", getpid(), &x);
			break;

		default:  //proceso padre
			printf ("Soy el proceso padre, pid: %d, DirMem: %p \n\n", getpid(), &x);
	}
    exit(0);

}
