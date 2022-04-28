/*
 * Ejercicio 11 de TP Procesos
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
			printf ("Soy el proceso hijo, pid: %d , x = %d\n", getpid(), --x);
			break;

		default:  //proceso padre
			while(1);
			printf ("Soy el proceso padre, pid: %d , x = %d\n", getpid(), ++x);
	}
    exit(0);

}

//El padre se queda  esperando siempre y no termina, se puede finalizar con un ctrl+c desde el bash.
//El proceso hijo 5429 permanece como zombie hasta que termina. 
