/*
 * Ejercicios 3 y 4 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void manejador_senial(int a){
   	write(STDOUT_FILENO,"\n Me rehuso a terminar\n", sizeof("\n Me rehuso a terminar\n"));
}

int main ()
{
 	
	
	signal(SIGKILL, &manejador_senial);
	//signal(SIGUSR1, &manejador_senial);  //Ctrl + z


   printf("Proceso PID = %d\n", getpid());

   while(1);

   exit(0);
}
