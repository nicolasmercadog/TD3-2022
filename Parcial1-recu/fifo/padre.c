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

//#define MENSAJE "HOLA HIJA MIA"

int hijo (char * myfifo);

int main(void) 
{
	int fd_fifo,err;
	int pid;
	char buffer[20];
	int leido;
    char * myfifo = "/tmp/myfifo";
    
    //unlink(myfifo); 
    	 fd_fifo= open(myfifo, O_RDONLY, 0); //el hijo abre la fifo en modo lectura	O_RDONLY
/*    if (mkfifo(myfifo, 0666) == -1)*/
/*    {*/
/*        perror("fifo");*/
/*        return -1;*/
/*    }*/
    
    if ((pid = fork()) == -1)
    {
        perror("fork");
        return -1;
    }
    
// codigo que ejecuta el hijo
	if (pid==0) 
	{ 
        hijo(myfifo);

        return 0;
    }
// codigo que ejecuta el padre   
	else
	{
		printf("Proceso Padre en ejecucion... \n"); 
		
		usleep(1000);
		
		err = read(fd_fifo, buffer, strlen(buffer));
				
		// **** RESOLUCION DEL EJERCICIO *******************************
		    
		// *************************************************************
		
		printf("Padre: el resultado del ejercicio es %s\n", buffer);
		write(STDOUT_FILENO, buffer, sizeof(buffer));
		
		wait(NULL);
		return 0;
	}
}
