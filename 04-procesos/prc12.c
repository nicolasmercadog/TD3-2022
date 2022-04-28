/*
 * Ejercicio 12 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main ()
{
	fprintf(stdout, "Aqui va un texto stdout\n");
	fprintf(stderr, "Aquí  va un texto stderr\n");
    exit(0);

}


//El flujo está direccionado hacia la pantalla con fprintf.

