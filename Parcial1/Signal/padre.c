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
	
	//inicio las señales, deben enviarse una por una
	//cambiar la señal según sea necesario
	//signal(SIGUSR1, sg); 
	//signal(SIGUSR2, sg);
	signal(SIGFPE, sg);  
    
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
		printf("Soy el proceso hijo. Mi PID = %d\n", getpid());		
		
		
		//mata las señales, matar 1 a la vez. Cambiar la señal según sea necesario
		//kill(pid,SIGUSR1);
		//kill(pid,SIGUSR2);
		kill(pid,SIGFPE);
				
		wait(NULL);	
		return 0;
	}
}
