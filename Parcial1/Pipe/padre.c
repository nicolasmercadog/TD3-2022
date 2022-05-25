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

#define MENSAJE "HOLA HIJA MIA"

int hijo (int fd[2]);

int main(void) 
{
	int fd[2];
	int pid;
	char tx_buffer[20] = MENSAJE;
	
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return -1;
    }
    
    if ((pid = fork()) == -1)
    {
        perror("fork");
        return -1;
    }
    
// codigo que ejecuta el hijo
	if (pid==0) 
	{ 
        hijo(fd);

        return 0;
    }
// codigo que ejecuta el padre   
	else
	{
		printf("Proceso Padre en ejecucion... \n"); 
		
		sleep(1);
		
		close(fd[0]);
		//write(fd[1], tx_buffer, sizeof(tx_buffer));// funciona ambos para enviar
		write(fd[1], tx_buffer, strlen(tx_buffer));
		close(fd[1]);		
		
		wait(NULL);  
		exit(0);
	}
}
