/*
 * PARCIAL 1: programa para ser ejecutado en el proceso padre.
 * 
 * Comando para compilar:
 * 
 * 	gcc -m32 -c padre.c && gcc -m32 hijo.o padre.o -o padre
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void sg (int a){
}


int hijo (void);

int main(void) 
{
	int pid;
	signal(SIGUSR1, sg); 
	//signal(SIGUSR2, sg);
	//signal(SIGFPE, sg); 
    
    if ((pid = fork()) == -1)
    {
        perror("fork");
        return -1;
    }
    
// codigo que ejecuta el hijo
	if (pid==0) 
	{ 
        hijo();

        return 0;
    }
// codigo que ejecuta el padre   
	else
	{
		printf("Proceso Padre en ejecucion... \n"); 
		
		sleep(1);
		
		kill(pid,SIGUSR1);
		//kill(pid,SIGUSR2);
		//kill(pid,SIGFPE);
				
		// **** RESOLUCION DEL EJERCICIO *******************************
    
		// *************************************************************
		
		wait(NULL);	
		return 0;
	}
}
