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

int hijo (char * myfifo);

int main(void) 
{
	int fd_fifo,valor;
	int pid;
	char tx_buffer[20] = MENSAJE;
	
	//dirección donde va a estar el archivo fifo, siempre tiene que coincidir con el unlink y con el mkfifo sino no funciona
    char * myfifo = "/tmp/myfifo"; 
    
    unlink(myfifo); //borra cualquier fifo con ese nombre creada anteriormente
    
    
    if (mkfifo(myfifo, 0666) == -1) //se crea la fifo con nombre myfifo
    {
        perror("fifo");
        return -1;
    }
      fd_fifo = open(myfifo, O_RDWR , 0); //esta es la forma en que se abre la fifo, coincidiendo siempre con el nombre y,en este caso, modo lectura//escritura
    
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
		
		sleep(1);
		printf("PADRE: Enviando mensaje al hijo.. \n");
		valor = write(fd_fifo, tx_buffer, strlen(tx_buffer));
		if(valor<0){
		printf("\nPADRE: Error al enviar \n");}
		else{
		printf("\nPADRE: Mensaje enviado \n");}
		wait(NULL);
		return 0;
	}
}
